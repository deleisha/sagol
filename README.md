# sagol

Sagol, the Manipuri pony, despite its smaller size but intelligent are claimed to be best horse for polo.
Like the small but fast horse, This is libuv based TLS aware http web server framework which is designed
for performance. This will be used for implementing redfish based RESTful server for system management.

## Design and Implementation

Developing a webserver should be easy with sagol.
```c
#include "http_server.h"
#include "connection.h"

void write_res( const request *rqst, response *reply)
{
   char *str = "hello world\n";
   set_status(reply, 200);
   set_hdr(reply, "Content-Type",  "text/plain");
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
    addroute(rtr, "/home", 5, write_res);

    printf("Listening on %d\n", port);

    //run forever
    run(&svc);

    tls_engine_stop();
    return 0;
}
```
## Contributions

The framework is very very much work in progress. YOU can make a difference by contributing
