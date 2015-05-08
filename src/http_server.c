#include "http_server.h"
#include "http-parser/http_parser.h"
#include "connection.h"

void on_write(uv_write_t *req, int status)
{
    if(!status && req) {
        free(req);
        req = 0;
    }
}

void on_close(uv_tls_t* h)
{
    free(h);
    h = 0;
}


//Callback for testing
void on_read(uv_tls_t* clnt, int nread, uv_buf_t* dcrypted)
{
    if( nread <= 0 ) {
        if( nread == UV_EOF) {
            uv_tls_close(clnt, on_close);
        }
        return;
    }
    http_parser *rqst_hdl = malloc(sizeof(http_parser));
    http_parser_init(rqst_hdl, HTTP_REQUEST);

    size_t cnt = http_parser_execute(
                     rqst_hdl,
                     &settings,
                     dcrypted->base, nread
                 );

    uv_write_t *rq = (uv_write_t*)malloc(sizeof(*rq));
    assert(rq != 0);
    uv_tls_write(rq, clnt, dcrypted, on_write);
    free(dcrypted->base);
    dcrypted->base = NULL;
}

void alloc_cb(uv_handle_t *handle, size_t size, uv_buf_t *buf)
{
    buf->base = (char*)malloc(size);
    memset(buf->base, 0, size);
    buf->len = size;
    assert(buf->base != NULL && "Memory allocation failed");
}



void on_connected(uv_stream_t *server, int status)
{
    if( status ) {
        return;
    }
    uv_tls_t *s_srvr = CONTAINER_OF(server, uv_tls_t, socket_);

    //memory being freed at on_close
    uv_tls_t *sclient = (uv_tls_t*) malloc(sizeof(*sclient));
    if( uv_tls_init(server->loop, sclient) < 0 ) {
        fprintf( stderr, "TLS setup error\n");
        return;
    }

    int r = uv_tls_accept(s_srvr, sclient);
    if(!r) {
        uv_tls_read(sclient, alloc_cb , on_read);
    }
}

int setup_server(http_server *svc, char *ip_addr, int port)
{
    //bring up tls machine
    int ng = tls_engine_inhale( "server-cert.pem", "server-key.pem", 0);
    assert(ng == 0);


    svc->loop = uv_default_loop();

    if(uv_tls_init(svc->loop, &svc->server_socket) < 0) {
        fprintf( stderr, "TLS setup error\n");
        return  -1;
    }


    struct sockaddr_in bind_addr;
    int r = uv_ip4_addr(ip_addr, port, &bind_addr);
    assert(!r);


    r = uv_tcp_bind(&svc->server_socket.socket_, (struct sockaddr*)&bind_addr, 0);
    if( r ) {
        fprintf( stderr, "bind: %s\n", uv_strerror(r));
        return  r;
    }

    return 0;
}

int run(http_server *svc, uv_connection_cb on_connected)
{
   int rv = uv_tls_listen(&svc->server_socket, 128, on_connected);
    if( rv ) {
        fprintf( stderr, "listen: %s\n", uv_strerror(rv));
        return  rv;
    }


    uv_run(svc->loop, UV_RUN_DEFAULT);
    return 0;
}
