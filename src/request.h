#ifndef __REQUEST_H__
#define __REQUEST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "header.h"

struct request {
    int requested_method;
    char resource_path[4*1024];
    int rpath_len;


    int http_v_major;
    int http_v_minor;

    //querry string if present, redfish allows only skip and top
    //other values should be rejected
    char query[64];

    //fragment, ignored in redfish, then why is it here
    char *fragment;

    //message body e.g. in POST
    char *body;
    header rqst_hdr[32];
};

typedef struct request request;

#ifdef __cplusplus
}
#endif

#endif 
