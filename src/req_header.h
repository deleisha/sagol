#include "header.h"

// the middle term is required field, 2- Yes, 1- Conditional and 0 - No
#define REDFISH_REQ_HDRS(FN)  \
    FN(ACCEPT, 2, Accept)   \
   ,FN(ACCEPT_ENCODING, 2, Accept-Encoding)   \
   ,FN(ACCEPT-LANGUAGE, 0, Accept-Language)   \
   ,FN(CONTENT-TYPE, 1, Content-Type)   \
   ,FN(CONTENT-LENGTH, 0, Content-Length)   \


#define FN(HDR, REQD, HDR_STR)       REQ_HDR_##HDR
// make a enum of header name
enum req_hdr_name {
    REDFISH_REQ_HDRS(FN)
#undef FN
};

enum req_hdr_name req_hdr_name;

#define FN(HDR, REQD, HDR_STR)     HDR_STR
char * req_hdr_str[] = {
    REDFISH_REQ_HDRS(FN)
#undef FN
};

typedef HEADER(req_hdr_name) req_header;

#define GET_HEADER_STR(hdr)   req_hdr_str[hdr]

//#define GET_REQD_LEVEL(hdr_name) 
