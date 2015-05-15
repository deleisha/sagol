#ifndef __ROUTER_H__
#define __ROUTER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "queue.h"
#include "route.h"
#include "request.h"
#include "response.h"

typedef struct router router;


struct router {
    QUEUE rq;
    bool is_inited;
};

typedef void (*callback)(const request *rqst, response *reply);
void addroute(router *router, char *path, callback func);

#ifdef __cplusplus 
}
#endif
#endif
