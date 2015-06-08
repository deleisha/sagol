#ifndef __JSON_JSON_H__
#define __JSON_JSON_H__


#ifdef __cplusplus {
extern "C"
#endif


enum json_val_type {
    JSON_NULL
   ,JSON_FALSE
   ,JSON_TRUE
   ,JSON_OBJECT
   ,JSON_ARRAY
   ,JSON_INTEGER
   ,JSON_REAL
   ,JSON_STRING
   ,JSON_N_TYPES
};

#ifdef __cplusplus
}
#endif
#endif
