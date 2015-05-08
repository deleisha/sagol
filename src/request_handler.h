#ifndef __REQUEST_HANDLER_H__
#define __REQUEST_HANDLER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "request.h"
#include "response.h"

typedef struct {
    //handle and incoming request and filled in the response in @reply
    int (*handle_request)( const request *req, response *reply);
} request_handler;

#ifdef __cplusplus
}
#endif

#endif 
