#ifndef __DYN_STR_H__
#define __DYN_STR_H__

#ifdef __cpluplus
    extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <assert.h>

#define D_ARRAY(TYPE) struct {  \
  size_t free_at;               \
  size_t capacity;              \
  TYPE payload[];               \
}

typedef D_ARRAY(char) ngn_str_t;

#define GET_INIT_MEM(NAME, SZ, TYPE)  malloc(sizeof(NAME) + SZ * sizeof(TYPE))

// --------------------
//| x | a | b |  |  |  |
// --------------------
// capacity = 6
// free_at = 3
size_t ngn_strlen(ngn_str_t *self);
ngn_str_t* append_char_len(ngn_str_t *self, char *t, size_t len);
ngn_str_t* append_char(ngn_str_t *self, char *t);
void ngn_str_free(ngn_str_t *self);
ngn_str_t* append(ngn_str_t *self, ngn_str_t *t);
char* get_cstr(ngn_str_t *self);
size_t get_max_size(ngn_str_t *self);
ngn_str_t *ngn_str_nw_len(char *t, size_t len);
ngn_str_t* ngn_str_nw( char *t);

#ifdef __cplusplus
}
#endif

#endif

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
