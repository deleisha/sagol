#include <stdlib.h>
#include <string.h>
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
