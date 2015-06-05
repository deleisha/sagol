#ifndef __HTTP_STATUS_H__
#define __HTTP_STATUS_H__

#ifdef __cplusplus
extern "c"{
#endif

typedef struct dummy {
    size_t sz;
    char *msg;
}msg_info;

#define  CRLF    "\r\n"

#define HTTP_STATUS_MAP(XX)                                                   \
    XX(OK, {9,  " 200 OK\r\n"} )                                              \
   ,XX(CREATED, {14, " 201 Created\r\n"} )                                    \
   ,XX(ACCEPTED, {16, " 202 Accepted\r\n"} )                                  \
   ,XX(NO_CONTENT,{20, " 204 No Content\r\n"} )                               \




#define XX(code, len, wrd) len, wrd

/*
msg_info array[] = {
    {9, "200 Ok\r\n"},
    {14, "201 Created\r\n"},
    {}
};
*/
static msg_info array[] = {
    HTTP_STATUS_MAP(XX)
#undef XX
};


#define ARRAY_SIZE(arr)   sizeof(arr)/sizeof(arr[0])



#define GET_HTTP_STATUS_STR(code, len)    (len = array[code].sz, array[code].msg)


#define XX(code, l, word) HTTP_STATUS_##code

/*
enum http_status {
    HTTP_STATUS_OK,
    HTTP_STATUS_CREATED
};
*/
enum http_status {
    HTTP_STATUS_MAP(XX)
#undef XX
};
#ifdef __cplusplus
}
#endif
#endif
