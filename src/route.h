#ifndef __ROUTE_H__
#define __ROUTE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "queue.h"



struct route {
    char *path;
    int path_len;

    //method that are being served by this route
    //enum HTTP_method mthd[];
    int no_mthd;

    char *lib_name;
    char *name_len;

    //function pointer
    void *fptr;

    //Schema version that this lib serves
    
    QUEUE node;
};
typedef struct route route;

void add_route(QUEUE *q, route *rt);

#ifdef __cplusplus 
}
#endif
#endif
