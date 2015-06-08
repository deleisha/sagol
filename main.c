#include "http_server.h"

void write_res( const request *rqst, response *reply)
{
   char *str = "{ \"v1\": \"redfish/v1\" }";
   set_status(reply, HTTP_STATUS_OK);
   set_hdr(reply, "Content-Type",  "application/json");
   reply->msg_len = strlen(str);
   reply->msg_body = str;
}

int main() {
    const int port = 8000;
    http_server svc;

    //bring up tls machine, this need to be done before server setup
    int ng = tls_engine_inhale("server-cert.pem", "server-key.pem", 0);
    assert(ng == 0);

    setup_server(&svc, "0.0.0.0", port);

    //the length of path passed explicitly to stop strlen calling
    router *rtr = get_router(&svc);
    addroute(rtr, "/redfish", 8, write_res);

    printf("Listening on %d\n", port);

    //run forever
    run(&svc);

    tls_engine_stop();
    return 0;
}
