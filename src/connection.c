#include "connection.h"




connection *create_connection(void)
{
    connection *conn = malloc(sizeof(connection));
    conn->parser.data = conn;
    return  conn;
}

int on_url(http_parser *parser, const char *url, size_t length)
{
    connection *conn = parser->data;

    //extract the request path from url
    struct http_parser_url u;
    int result = http_parser_parse_url(url, length, 0, &u);
    assert( result == 0);

    if ( u.field_set & (1 << UF_PATH ) ) {
           strcpy( conn->reqst.resource_path, url + u.field_data[UF_PATH].off,
               u.field_data[UF_PATH].len
           );
    }

    if ( u.field_set & (1 << UF_QUERY) ) {
           //test later for the validity of querry string
           strcpy( conn->reqst.resource_path, url + u.field_data[UF_QUERY].off,
               u.field_data[UF_QUERY].len
           );
    }

    return 0;
}

 


settings.on_url = on_url;
