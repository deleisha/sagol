#ifndef __REQUEST_H__
#define __REQUEST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "header.h"

struct request {
    int requested_method;
    char *resource_path;
    int http_v_major;
    int http_v_minor;

    //querry string if present, redfish allows only skip and top
    //other values should be rejected
    char *query;

    //fragment, ignored in redfish
    char *fragment;

    //message body e.g. in POST
    char *body;
    header rqst_hdr[32];
};

#ifdef __cplusplus
}
#endif

#endif 
