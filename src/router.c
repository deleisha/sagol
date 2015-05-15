#include <stdlib.h>
#include <string.h>
#include "router.h"
#include "route.h"

void addroute(router *router_, char *path, callback func)
{
    if( !router_ ) {
        return;
    }

    if( !(router_->is_inited)) {
        QUEUE_INIT(&router_->rq);
        router_->is_inited = true;
    }

    route *rt = malloc(sizeof(*rt));
    rt->path = path;
    rt->path_len = strlen(path);
    rt->fptr = func;
    add_route(&router_->rq, rt);
}
