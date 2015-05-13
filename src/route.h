#ifndef __ROUTE_H__
#define __ROUTE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "queue.h"

typedef struct route route;


struct route {
    char *path;
    int path_len;

    //method that are being served by this route
    //enum HTTP_method mthd[];
    int no_mthd;

    char *lib_name;
    char *name_len;

    //Schema version that this lib serves
    
    QUEUE node;
};

#ifdef __cplusplus 
}
#endif
#endif




