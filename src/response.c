#include <stdio.h>
#include "uv_tls.h"
#include "response.h"
#include "http_status.h"

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


static void set_content_len(response *slf, ngn_str_t *str)
{
    assert(slf != NULL && slf->msg_body != NULL);
    assert( str != NULL);

    str = append_char_len(str, "Content-Length:", 15);
    char t[256];
    memset(t, 0, sizeof(t));
    sprintf(t, "%d", slf->msg_len);
    str = append_char_len(str, t, slf->msg_len);
    str = append_char_len(str, "\r\n\r\n", 4);
}

uv_buf_t form_http_reply(response *self)
{
    assert(self != NULL);
    ngn_str_t *str = ngn_str_nw_len("HTTP/1.1", 8);

    size_t ln = 0;
    char *tmp = GET_HTTP_STATUS_STR(self->status, ln);
    append_char_len( str, tmp, ln);

    for( int i = 0; i < self->hdr_cnt; ++i) {
	str = append_char(str, self->hdr[i].field);
	str = append_char_len(str, ":", 1);
	str = append_char(str, self->hdr[i].value);
	str = append_char_len(str, "\r\n", 2);
    }

    set_content_len(self, str);

    str = append_char_len(str, self->msg_body, self->msg_len);
    uv_buf_t buffer;
    buffer.base = get_cstr(str);
    buffer.len = ngn_strlen(str); 

    
    return buffer;
}
