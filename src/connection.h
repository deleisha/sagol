#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "uv_tls.h"
#include "http_parser.h"
#include "request.h"
#include "request_hadler.h"
#include "response.h"

http_parser_settings settings;

typedef struct connection {
    /// handle to client socket
    uv_tls_t handle;

    /// paerser to parse incoming data and create a request
    http_parser parser;

    // request used by handler
    request reqst;

    ///response to a client request, constrcuted by handle_request
    response reply;

    //Master blaster for carrying the operation of the server
    request_handler rqst_hdlr;

} connection;

//create a new connection, this is called for every connection
connection *create_connection(void);


#ifdef __cplusplus
}
#endif

#endif 
