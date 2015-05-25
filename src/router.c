#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "router.h"
#include "route.h"

void addroute(router *router_, char *path, int path_len, callback func)
{
    if( !(router_->is_inited)) {
        QUEUE_INIT(&router_->route);
        router_->is_inited = true;
    }

    route *rt = malloc(sizeof(*rt));
    rt->path = path;
    rt->path_len = path_len;
    rt->info.vrsn.major = 1;
    rt->info.vrsn.minor = 0;
    rt->info.createFunc = 0;
    rt->info.destroyFunc = 0;
    rt->info.lang = (coded_lang) 0x1;
    add_route(&router_->route, rt);
}

QUEUE *get_route(router *rtr)
{
    return &(rtr->route);
}

int enroute( router *rtr, request *req)
{
    if( !( rtr && req)) {
        return -1;
    }

    QUEUE *d_q = get_route(rtr);
    QUEUE *q = QUEUE_HEAD(d_q);
    assert( q != NULL);
    QUEUE_FOREACH(q, d_q) {
        //get the request from request @req
        route *tmp = QUEUE_DATA(q, route, node);
        if(tmp->path_len != req->rpath_len) {
            continue;
        }
        if(!strncmp(tmp->path,req->resource_path, tmp->path_len))
            ;
            //bring up the handle
    }
    return 0;
}
