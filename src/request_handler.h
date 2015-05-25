#ifndef __REQUEST_HANDLER_H__
#define __REQUEST_HANDLER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "request.h"
#include "response.h"
#include "connection.h"

typedef struct {
    //handle and incoming request and filled in the response in @reply
    int (*handle_)( const request *req, response *reply);

    //connection *conn;

    //route being handled

} request_handler;

/*
void handle_req()
{
    switch(http_req) {
        case GET:
            hdlr->get();
        case POST:
            hdlr->post();
    }
}
*/

#ifdef __cplusplus
}
#endif

#endif 
