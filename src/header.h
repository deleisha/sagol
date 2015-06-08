#ifndef __HEADER_H__
#define __HEADER_H__

#ifdef __cplusplus
extern "C" {
#endif

#define HEADER(type)                            \
    struct header_tag  {                        \
        type field;                             \
	char *value;                            \
    }


typedef HEADER(char*) header;

#ifdef __cplusplus
}
#endif

#endif 
