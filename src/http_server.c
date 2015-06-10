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


int setup_server(http_server *svc, char *ip_addr, int port)
{
    svc->loop = uv_default_loop();

    if(uv_tls_init(svc->loop, &svc->server_socket) < 0) {
        fprintf( stderr, "TLS setup error\n");
        return  -1;
    }

    if( !svc->rtr.is_inited) {
        init_router (&svc->rtr);
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


void handle_connect(uv_stream_t *server, int status)
{
    if( status ) {
	return;
    }

    //memory being freed at on_close
    connection *conn =  malloc(sizeof(*conn));
    int r = new_client(server, conn);

    if( !r ) {
        handle_req(conn);
    }
    else { //connection could not be estbalished
        free(conn);
        conn = 0;
    }
}

int run(http_server *svc)
{
    int rv = uv_tls_listen(&svc->server_socket, 128, handle_connect);
    if( rv ) {
        fprintf( stderr, "listen: %s\n", uv_strerror(rv));
        return rv;
    }

    //always return 0 for UV_RUN_DEFAULT
    uv_run(svc->loop, UV_RUN_DEFAULT);
    return 0;
}

router *get_router(http_server *self)
{
        return &self->rtr;
}

void set_router(http_server *self, router *r)
{
    self->rtr = *r;
}
