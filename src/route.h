#ifndef __ROUTE_H__
#define __ROUTE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "utils/queue.h"
#include "request.h"
#include "response.h"
#include "plgn_api.h"


typedef void (*callback)(const request *rqst, response *reply);

struct route {
    char *path;
    int path_len;

    callback func;
    plgn_info info;

    QUEUE node;
};
typedef struct route route;



void add_route(QUEUE *q, route *rt);
void rm_route(QUEUE *q);

#ifdef __cplusplus 
}
#endif
#endif
