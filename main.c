#include "http_server.h"
#include "connection.h"


extern void alloc_cb(uv_handle_t *handle, size_t size, uv_buf_t *buf);
extern void on_read(uv_tls_t* clnt, int nread, uv_buf_t* dcrypted);

void handle_connect(uv_stream_t *server, int status)
{
    if( status ) {
        return;
    }

    //memory being freed at on_close
    connection *conn =  malloc(sizeof(*conn));
    int r = new_client(server, conn);
    if( !r ) {
        handle_req( conn );
    }
    else { //connection could not be estbalished
        free(conn);
        conn = 0;
    }
}

int main()
{
    //bring up tls machine, this need to be done before server setup
    //if we are using tls
    int ng = tls_engine_inhale( "server-cert.pem", "server-key.pem", 0);
    assert(ng == 0);

    const int port = 8000;
    http_server svc;
    setup_server(&svc, "0.0.0.0", port);

    printf("Listening on %d\n", port);
    run(&svc, handle_connect);

    tls_engine_stop();
    return 0;
}
