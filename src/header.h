#ifndef __HEADER_H__
#define __HEADER_H__

#ifdef __cplusplus
extern "C" {
#endif

#define HEADER(type)                                                          \
    struct {                                                      \
        type field;                                                           \
        char *value;                                                          \
    }                                                                         \



#ifdef __cplusplus
}
#endif

#endif 
