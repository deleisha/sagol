#include "http_server.h"
#include "http_parser.h"
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
    free(h->data);
    h->data = 0;
}

void alloc_cb(uv_handle_t *handle, size_t size, uv_buf_t *buf)
{
    buf->base = (char*)malloc(size);
    memset(buf->base, 0, size);
    buf->len = size;
    assert(buf->base != NULL && "Memory allocation failed");
}

static void get_method(connection *conn)
{
    conn->reqst.requested_method = conn->parser.method;
}

static
int handle_request(const request *rqst, response *rslt)
{
    switch(rqst->requested_method) {
        case HTTP_GET:
            rslt->status = 200;
            rslt->msg_body = "{\"name\":\"Faizan\"}";
        default:
            break;
    }
    return 0;
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

    connection *conn = clnt->data;
    http_parser_init(&conn->parser, HTTP_REQUEST);
    settings.on_url = on_url;

    size_t cnt = http_parser_execute(
                     &conn->parser, &settings, dcrypted->base, nread
                 );

    if ( cnt < nread ) {
        //there are some unparsed data like JSON
        //need to handled manually
    }

    //request is ready for downstream processing
    get_method(conn);

    handle_request( &conn->reqst, &conn->reply);

    //write callback is nullified as writer will be
    //free on connection close
    
    char big_blob[20*1040] = {0};
    if( conn->reply.status == 200) {
        strcpy(big_blob, "HTTP/1.1 200 OK\r\n Content-Type: text/plain\r\n" \
                "Content-Length: 12\r\n \r\n {\"name\": \"faizan\"}\n" );
        dcrypted->base = big_blob;
        dcrypted->len = sizeof(big_blob);
    }
    uv_tls_write(&conn->writer, clnt, dcrypted, NULL);

    //free(dcrypted->base);
    //dcrypted->base = NULL;
}

int setup_server(http_server *svc, char *ip_addr, int port)
{
    svc->loop = uv_default_loop();

    if(uv_tls_init(svc->loop, &svc->server_socket) < 0) {
        fprintf( stderr, "TLS setup error\n");
        return  -1;
    }

    struct sockaddr_in bind_addr;
    int r = uv_ip4_addr(ip_addr, port, &bind_addr);
    assert(!r);

    r = uv_tcp_bind(&svc->server_socket.socket_,(struct sockaddr*)&bind_addr,0);
    if( r ) {
        fprintf( stderr, "bind: %s\n", uv_strerror(r));
        return  r;
    }

    return 0;
}

int run(http_server *svc, uv_connection_cb handle_connection)
{
    int rv = uv_tls_listen(&svc->server_socket, 128, handle_connection);
    if( rv ) {
        fprintf( stderr, "listen: %s\n", uv_strerror(rv));
        return rv;
    }

    //always return 0 for UV_RUN_DEFAULT
    uv_run(svc->loop, UV_RUN_DEFAULT);
    return 0;
}
