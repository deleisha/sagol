#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "uv_tls.h"
#include "http_parser.h"
#include "http_server.h"
#include "request.h"
#include "request_handler.h"
#include "response.h"

#define NONGIN_API 

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
    request_handler *rqst_hdlr;

    //write request for writing back the response, it is here to
    //reduce multiple malloc
    uv_write_t writer;

    //hook to the server where this connection is running
    http_server *svc;

} connection;

//create a new connection, this is called for every connection
connection NONGIN_API *create_connection(void);

/*
 * A new connection is instantiated, this happens for every new connection
*/
int NONGIN_API new_client(const uv_stream_t *server, connection *conn);

/*
 * Read from the connection @conn
*/
int NONGIN_API read_from(connection *conn);

/*
 * write to client connection @conn
*/
int NONGIN_API write_to(const connection *conn);

/*
 * close connection @c
*/
int NONGIN_API close_con(connection *c);

int NONGIN_API handle_req(connection *c);


///should be moved to request
int on_url(http_parser *parser, const char *url, size_t length);


#ifdef __cplusplus
}
#endif
#endif //__CONNECTION_H__
