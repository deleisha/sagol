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

}

int set_hdr(response *self, const char *field, const char *val)
{
    self->hdr_cnt++;
}
