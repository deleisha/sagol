#include "route.h"
void add_route(QUEUE *q, route *rt)
{
    QUEUE_INIT(&rt->node);

    QUEUE_INSERT_TAIL(q, &rt->node);
}
