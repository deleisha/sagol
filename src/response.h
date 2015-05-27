#ifndef __RESPONSE_H__
#define __RESPONSE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "header.h"

typedef struct response {
    //make this enum
    int status;

    //change this accordingly
    header hdr[32];
    int hdr_cnt;
    char *msg_body;

    //functional API
    void (*init)( struct response *self);


} response;

/*
"HTTP/1.1 200 OK\r\n" \
  "Content-Type: text/plain\r\n" \
  "Content-Length: 12\r\n" \
  "\r\n" \
  "hello world\n"
*/

response init_fn(response *self);
int set_status(response *self, int status);
int set_cnt_type(response *self, const char *ctype);

#ifdef __cplusplus
}
#endif

#endif
