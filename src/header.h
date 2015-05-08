#ifndef __HEADER_H__
#define __HEADER_H__

#ifdef __cplusplus
extern "C" {
#endif



struct header {
    char *field;
    char *value;
};

typedef struct header header;

int set_header(char *field, char* value);
void get_header(char *field);

#ifdef __cplusplus
}
#endif

#endif 
