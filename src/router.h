#ifndef __ROUTER_H__
#define __ROUTER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "queue.h"
#include "route.h"
#include "request_handler.h"

typedef struct router router;


struct router {
    QUEUE route; //head of the queue holding the route info
    bool is_inited;
};

void addroute(router *router, char *path, int path_len, callback func);


request_handler* enroute(router *rtr, request *req);


#ifdef __cplusplus 
}
#endif
#endif
