#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "uv_tls.h"
#include "http_parser.h"
#include "request.h"
#include "request_handler.h"
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

    //write request for writing back the response, it is here to
    //reduce multiple malloc
    uv_write_t writer;

} connection;

//create a new connection, this is called for every connection
connection *create_connection(void);

/*
 * Read from the connection @conn
*/
int read_from(const connection *conn);

/*
 * write to client connection @conn
*/
int write_to(const connection *conn);

/*
 * A new connection is instantiated, this happens for every new connection
*/
int new_client(const uv_stream_t *server, connection *conn );



///should be moved to request
int on_url(http_parser *parser, const char *url, size_t length);


#ifdef __cplusplus
}
#endif
#endif
