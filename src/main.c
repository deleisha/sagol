#include "router.h"
#include <stdio.h>


int main()
{
    router rtr;
    addroute(&rtr, "home", 4, 0);

    QUEUE *hdr = QUEUE_HEAD(&rtr.route);

    route *rt = QUEUE_DATA(hdr, route, node);
    printf("path = %s\n", rt->path);
    printf("path_len = %d\n", rt->path_len);
    return 0;
}
