#include <stdio.h>
#include "uv_tls.h"
#include "response.h"

void init_res( response *self)
{
    if(!self) {
        return;
    }
    self->status = 0; // TODO: map this later
    self->hdr_cnt = 0;
    self->msg_body = NULL;
}

int set_status(response *self, int status)
{
    self->status = status;
    return status;
}

void set_hdr(response *self, char *field, char *value)
{
    self->hdr[self->hdr_cnt].field = field;
    self->hdr[self->hdr_cnt].value = value;
    self->hdr_cnt++;
}

uv_buf_t* form_http_reply(response *self)
{
    if( !self) {
        return NULL;
    }
    ngn_str_t *str = ngn_str_nw_len("HTTP/1.1", 8);

    return NULL;
}
