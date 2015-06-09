#ifndef __HTTP_STATUS_H__
#define __HTTP_STATUS_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct dummy {
    size_t sz;
    char *msg;
}http_status_info;

#define  CRLF    "\r\n"

#define HTTP_STATUS_MAP(XX)                                                   \
    XX(OK, {9,  " 200 OK\r\n"} )                                              \
   ,XX(CREATED, {14, " 201 Created\r\n"} )                                    \
   ,XX(ACCEPTED, {16, " 202 Accepted\r\n"} )                                  \
   ,XX(NO_CONTENT,{20, " 204 No Content\r\n"} )                               \
   ,XX(MOVED_PERMANENTLY, {24, " 301 Moved Permanently\r\n"} )                \
   ,XX(FOUND, {12, " 302 Found\r\n"} )                                        \
   ,XX(NOT_MODIFIED, {19, " 304 Not Modified\r\n"} )                          \
   ,XX(BAD_REQUEST, {18, " 400 Bad Request\r\n"} )                            \
   ,XX(UNAUTHORIZED, {19, " 401 Unauthorized\r\n"} )                          \
   ,XX(FORBIDDEN, {16, " 403 Forbidden\r\n"} )                                \
   ,XX(NOT_FOUND, {16, " 404 Not Found\r\n"} )                                \
   ,XX(MET_NOT_ALLOWED, {25, " 405 Method Not Allowed\r\n"} )                 \
   ,XX(NOT_ACCEPTABLE, {21, " 406 Not Acceptable\r\n"} )                      \
   ,XX(GONE, {11, " 410 Gone\r\n"} )                                          \
   ,XX(LEN_REQD, {22, " 411 Length Required\r\n"} )                           \
   ,XX(PRECOND_FAILED, {26, " 412 Precondition Failed\r\n"} )                 \
   ,XX(UNSUPPORTED_MIME_TYPE, {29, " 415 Unsupported Media Type\r\n"} )       \
   ,XX(INTERNAL_ERROR, {26, " 500 Internal Server Error\r\n"} )               \
   ,XX(NOT_IMPLEMENTED, {22, " 501 Not Implemented\r\n"} )                    \
   ,XX(SVC_UNAVAILABLE, {26, " 503 Service Unavailable\r\n"} )                \





/* http_status_info array[] = {
    {9, "200 Ok\r\n"},
    {14, "201 Created\r\n"},
    {}
}; */

static http_status_info array[] = {
#define XX(code, len, wrd) len, wrd
    HTTP_STATUS_MAP(XX)
#undef XX
};


#define ARRAY_SIZE(arr)   sizeof(arr)/sizeof(arr[0])



#define GET_HTTP_STATUS_STR(code, len)    (len = array[code].sz, array[code].msg)



/* enum http_status {
    HTTP_STATUS_OK,
    HTTP_STATUS_CREATED
}; */

enum http_status {
#define XX(code, l, word) HTTP_STATUS_##code
    HTTP_STATUS_MAP(XX)
#undef XX
   ,MAX_VALUE
};



#ifdef __cplusplus
}
#endif

#endif
