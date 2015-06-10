#include "header.h"

// the middle term is required field, 2- Yes, 1- Conditional and 0 - No
#define REDFISH_REQ_HDRS(FN)                                                  \
    FN(ACCEPT, 2, Accept)                                                     \
   ,FN(ACCEPT_ENCODING, 2, Accept-Encoding)                                   \
   ,FN(ACCEPT_LANGUAGE, 0, Accept-Language)                                   \
   ,FN(CONTENT_TYPE, 1, Content-Type)                                         \
   ,FN(CONTENT_LENGTH, 0, Content-Length)                                     \
   ,FN(MAX_ODATA_VER, 0, Max-Odata-Version)                                   \
   ,FN(ODATA_VER, 2, Odata-Version)                                           \
   ,FN(AUTHORIZATION, 1, Authorization)                                       \
   ,FN(USER_AGENT, 2, User-Agent)                                             \
   ,FN(HOST, 2, Host)                                                         \
   ,FN(ORIGIN, 2, Origin)                                                     \
   ,FN(VIA, 0, Via)                                                           \
   ,FN(MAX_FORWARDS, 0, Max-Forwards)                                         \
   ,FN(IF_MATCH, 1, If-Match)                                                 \
   ,FN(IF_NONE_MATCH, 0, If-None-Match)                                       \
   ,FN(X_AUTH_TOKEN, 2, X-Auth-Token)                                         \

// make a enum of header name
enum req_hdr_name {
#define FN(HDR, REQD, HDR_STR)       REQ_HDR_##HDR
    REDFISH_REQ_HDRS(FN), REQ_HDR_COUNT
#undef FN
};

typedef enum req_hdr_name req_hdr_name;

static char * req_hdr_str[] = {
#define FN(HDR, REQD, HDR_STR)     #HDR_STR
    REDFISH_REQ_HDRS(FN)
#undef FN
};

#define GET_HEADER_STR(hdr)   req_hdr_str[hdr]


static int requirement_table[] = {
#define FN(HDR, REQD, HDR_STR)     REQD
    REDFISH_REQ_HDRS(FN)
#undef FN
};
#define GET_REQD_LEVEL(hdr_name)      requirement_table[hdr_name]

