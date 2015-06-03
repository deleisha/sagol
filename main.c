#include "http_server.h"
#include "connection.h"


void write_res( const request *rqst, response *reply)
{
    char *str = "hello world\n";

   set_status(reply, 200);
   set_hdr(reply, "Content-Type",  "text/plain");

   reply->msg_len = sizeof(str);
   //set_hdr(reply, "Content-Length",  "text/plain");

   reply->msg_body = str;
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

int main()
{
    //bring up tls machine, this need to be done before server setup
    //if we are using tls
    int ng = tls_engine_inhale("server-cert.pem", "server-key.pem", 0);
    assert(ng == 0);

    const int port = 8000;
    http_server svc;
    setup_server(&svc, "0.0.0.0", port);

    router *rtr = get_router(&svc);
    //third arg is the length of path, passing this explicitly to stop
    //strlen calling
    addroute(rtr, "/home", 5, write_res);

    printf("Listening on %d\n", port);
    run(&svc, handle_connect);

    tls_engine_stop();
    return 0;
}
