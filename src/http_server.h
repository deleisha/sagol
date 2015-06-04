#ifndef __HTTP_SERVER_H__
#define __HTTP_SERVER_H__

#include "uv_tls.h"
#include "router.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NONGIN_API 

struct NONGIN_API http_server {
    //event loop
    uv_loop_t *loop;

    //representation of server socket
    //should this be a separate abstraction
    uv_tls_t server_socket;

    //port to listen
    int port;

    router rtr;
};

typedef struct http_server http_server;

int NONGIN_API setup_server(http_server *svc, char *ip_addr, int port);

int NONGIN_API run(http_server *svc);

router NONGIN_API *get_router(http_server *svc);

///int NONGIN_API stop()

#ifdef __cplusplus
}
#endif
#endif
