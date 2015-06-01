#include "dyn_str.h"
void *ngn_realloc(void *old_ptr, size_t sz)
{
    char *ptr = realloc(old_ptr, sz);
    if( !ptr ) {
        free(old_ptr);
        return NULL;
    }
    return ptr;
}


// --------------------
//| x | a | b |  |  |  |
// --------------------
// capacity = 6
// free_at = 3
size_t ngn_strlen(ngn_str_t *self)
{
    return self->free_at;
}

ngn_str_t* append_char_len(ngn_str_t *self, char *t, size_t len)
{
    if( !self) return NULL;
    if( !t) return NULL;

    if( (self->capacity - self->free_at) <  len ) {
        self = ngn_realloc( self, (self->capacity + len) * 2);
        assert( self != NULL);
        self->capacity = (self->capacity + len) * 2;
    }
    memcpy(self->payload + self->free_at, t, len);

    self->free_at += len;

    return self;
}



ngn_str_t* append_char(ngn_str_t *self, char *t)
{
    assert( self != NULL && t != NULL);
    return append_char_len(self, t, strlen(t));
}


void ngn_str_free(ngn_str_t *self)
{
    free(self);
    self = NULL;
}


ngn_str_t* append(ngn_str_t *self, ngn_str_t *t)
{
    assert( self != NULL);
    assert( t != NULL);
    
    //realloc if there is lesser space
    size_t sz = ngn_strlen(t);
    if( (self->capacity - self->free_at) <  sz ) {
        self = ngn_realloc( self, (self->capacity + sz) * 2);
        assert( self != NULL);
        self->capacity = (self->capacity + sz) * 2;
    }
    memcpy(self->payload + self->free_at, t->payload, sz);

    self->free_at += sz;

    return self;
}

char* get_payload(ngn_str_t *self)
{
    self->payload[self->free_at] = '\0';
    return self->payload;
}


size_t get_max_size(ngn_str_t *self)
{
    return  self->capacity;
}

ngn_str_t *ngn_str_nw_len(char *t, size_t len)
{
    size_t rlen = len > 32 ? len : 32;
    ngn_str_t *rv = GET_INIT_MEM(ngn_str_t, rlen, char);
    rv->capacity = rlen;
    memcpy(rv->payload, t, len);
    rv->free_at = len; 
    return  rv;
}

ngn_str_t* ngn_str_nw( char *t)
{
    return ngn_str_nw_len(t, strlen(t));
}

/*
int main()
{
    ngn_str_t *string = ngn_str_nw_len("Hello World", 11 );
    assert( 11 == ngn_strlen(string));
    assert( 32 == get_max_size(string));

    ngn_str_t *char_str = ngn_str_nw( "Ding Dong");
    assert( 9 == ngn_strlen(char_str));
    append(string, char_str);

    ngn_str_free(char_str);
    append_char_len(string, "Hello", 5);

    assert(25  == ngn_strlen(string));

    printf( "String = %s\n",  string->payload);

    ngn_str_free(string);
}
*/
