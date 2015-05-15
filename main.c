#include "http_server.h"
#include "connection.h"


router config_svc;
void write_res( const request *rqst, response *reply)
{
    //write callback is nullified as writer will be
    //free on connection close
    char *str = "Hello World";
    uv_buf_t *dcrypted  = malloc(sizeof(*str));
    memcpy(dcrypted->base, str, sizeof(*str));
    dcrypted->len = 12;

    //uv_tls_write(&conn->writer, &conn->handle, dcrypted, NULL);

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
        handle_req(conn );
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

    addroute(&config_svc, "/", write_res);

    printf("Listening on %d\n", port);
    run(&svc, handle_connect);

    tls_engine_stop();
    return 0;
}
