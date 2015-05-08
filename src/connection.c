#include <stdlib.h>
#include <string.h>
#include "connection.h"

/// Caller need to free
connection *create_connection(void)
{
    connection *conn = malloc(sizeof(connection));
    conn->parser.data = conn;
    return  conn;
}

int on_url(http_parser *parser, const char *url, size_t length)
{
    connection *conn = parser->data;

    struct http_parser_url u;
    int result = http_parser_parse_url(url, length, 0, &u);
    assert( result == 0);

    //extract the request path from url
    if ( u.field_set & (1 << UF_PATH) ) {
        strncpy( conn->reqst.resource_path, url + u.field_data[UF_PATH].off,
                u.field_data[UF_PATH].len);

        conn->reqst.resource_path[u.field_data[UF_PATH].len] = '\0';
        fprintf( stderr, "PATH = %s\n", conn->reqst.resource_path);
    }

    //extract the querry component from URL
    if ( u.field_set & (1 << UF_QUERY) ) {
           //test later for the validity of querry string
           //strcpy( conn->reqst.resource_path, url + u.field_data[UF_QUERY].off,
          //     u.field_data[UF_QUERY].len
          // );
    }
    return 0;
}

//connection need not be initiliased but space need to be allocated
int new_client(const uv_stream_t *server, connection *conn )
{
    uv_tls_t *s_srvr = CONTAINER_OF(server, uv_tls_t, socket_);
    conn->handle.data = conn;
    conn->parser.data = conn;

    if( uv_tls_init(server->loop, &conn->handle) < 0 ) {
        //hate this till better error handling in libuv-tls
        fprintf( stderr, "TLS setup error\n");
        return -1;
    }

    return uv_tls_accept(s_srvr, &conn->handle);
}
