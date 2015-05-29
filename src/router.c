#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "router.h"
#include "route.h"
#include "request_handler.h"
#include "connection.h"

void addroute(router *self, char *path, int path_len, callback func)
{
    if( !(self->is_inited)) {
        QUEUE_INIT(&self->route);
        self->is_inited = true;
    }

    route *rt = malloc(sizeof(*rt));
    rt->path = path;
    rt->path_len = path_len;
    rt->func = func;
    rt->info.vrsn.major = 1;
    rt->info.vrsn.minor = 0;
    rt->info.vrsn.fix = 0;

    rt->info.createFunc = 0;
    rt->info.destroyFunc = 0;

    rt->info.lang = C;
    add_route(&self->route, rt);
}

request_handler* enroute( router *self, request *req)
{
    if( !( self && req)) {
        return NULL;
    }
    assert( self->is_inited);

    connection *c = CONTAINER_OF(req, connection, reqst);
    assert(c != NULL);

    QUEUE *q = QUEUE_HEAD(&self->route);
    assert( q != NULL);

    QUEUE_FOREACH(q, &self->route) {
        //get the request from request @req
        route *tmp = QUEUE_DATA(q, route, node);
        if(tmp->path_len != req->rpath_len) {
            continue;
        }

        
        if(!strncmp(tmp->path, req->resource_path, tmp->path_len)) {
            if( tmp->func) { //Ok, callback found
                request_handler *hdlr = malloc(sizeof(*hdlr));
                hdlr->handle_ = tmp->func;
                c->rqst_hdlr = hdlr;
                break;
            }

        }
    }
    return 0;
}
