#ifndef __RESPONSE_H__
#define __RESPONSE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "header.h"
#include "uv_tls.h"
#include "http_status.h"
#include "res_header.h"
#include "utils/dyn_str.h"

typedef HEADER(char*) header;

typedef struct response {
    //make this enum
     enum http_status status;

    //change this accordingly
    header hdr[RES_HEADER_COUNT];
    int hdr_cnt;

    char *msg_body;
    int msg_len;
} response;

/*
"HTTP/1.1 200 OK\r\n" \
  "Content-Type: text/plain\r\n" \
  "Content-Length: 12\r\n" \
  "\r\n" \
  "hello world\n"
*/


void init_res(response *);
int set_status(response *self, int status);
void set_cnt_type(response *self, const char *ctype);
void set_hdr(response *self, char *field, char *val);

uv_buf_t form_http_reply(response *self);


#ifdef __cplusplus
}
#endif

#endif
