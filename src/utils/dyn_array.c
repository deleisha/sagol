#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <assert.h>

#define D_ARRAY(TYPE) struct {  \
  size_t free_at;               \
  size_t capacity;              \
  TYPE really[];                \
}

#define CONTAINER_OF(ptr, type, member)    \
  (type *) ((char *)ptr - offsetof(type, member))

typedef D_ARRAY(char) ngn_str_t;

#define GET_INIT_MEM(NAME, SZ, TYPE)  malloc(sizeof(NAME) + SZ * sizeof(TYPE))

size_t ngn_strlen(ngn_str_t *str)
{
    return str->free_at - 1;
}
append(ngn_str_t *str, char *t)
{
}
size_t get_max_size(ngn_str_t *self)
{
    return  self->capacity;
}

ngn_str_t *new_string(char *t, size_t len)
{
    ngn_str_t *rv = GET_INIT_MEM(ngn_str_t, 256, char);
    rv->capacity = 256;
    memcpy(rv->really, t, len);
    rv->really[len] = '\0';
    rv->free_at = len + 1;
    return  rv;
}

int main()
{
    ngn_str_t *string = new_string("Hello World", 11 );
    assert(11 == ngn_strlen(string));
    assert(256 == get_max_size(string));
    char *ptr = string->really;
    ngn_str_t *tst = CONTAINER_OF(ptr, ngn_str_t, really);
    assert(tst == string);

    printf( "String = %s\n",  string->really);
}
