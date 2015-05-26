#include "route.h"
#include <stdio.h>
#include <assert.h>
void add_route(QUEUE *q, route *rt)
{
    if( !q ) {
        return;
    }
    QUEUE_INIT(&rt->node);

    QUEUE_INSERT_TAIL(q, &rt->node);
}

void rm_route(QUEUE *node)
{
    assert( node != NULL);
    QUEUE_REMOVE(node);
}
