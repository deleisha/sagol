#include <response.h>

void init_fn( response *self)
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
}

int set_cnt_type(response *self, const char *ctype)
{
    self->hdr[hdr_cnt].field = "content-type:";
    self->hdr[hdr_cnt].value = "application/json\r\n";
    self->hdr_cnt++;
}

int set_hdr(response *self, const char *field, const char *val)
{
    self->hdr_cnt++;
}

uv_buf_t* to_buf(response *self)
{

}
