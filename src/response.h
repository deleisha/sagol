#ifndef __RESPONSE_H__
#define __RESPONSE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "header.h"

typedef struct response {
    //make this enum
    int status;

    //change this accordingly
    header hdr[32];
    char *msg_body;
} response;

int set_status();

#ifdef __cplusplus
}
#endif

#endif 
