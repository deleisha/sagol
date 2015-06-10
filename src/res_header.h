#include "header.h"

// the middle term is required field, 2- Yes, 1- Conditional and 0 - No
#define REDFISH_RES_HDRS(FN)                                                  \
   FN(ODATA_VER, 2, Odata-Version)                                            \
   ,FN(CONTENT_TYPE, 2, Content-Type)                                         \
   ,FN(ACCEPT_ENCODING, 0, Accept-Encoding)                                   \
   ,FN(CONTENT_LENGTH, 0, Content-Length)                                     \
   ,FN(ETAG, 1, ETag)                                                         \
   ,FN(SERVER, 1, Server)                                                     \
   ,FN(LOCATION, 1, Location)                                                 \
   ,FN(CACHE_CONTROL, 2, Cache-Control)                                       \
   ,FN(VIA, 0, Via)                                                           \
   ,FN(MAX_FORWARDS, 0, Max-Forwards)                                         \
   ,FN(LINK, 0, Link)                                                         \
   ,FN(ACC_CTRL_ALLW_ORI, 2, Access-Control-Allow-Origin)                     \
   ,FN(ALLOW, 2, Allow)                                                       \
   ,FN(WWW_AUTH, 2, WWW-Authenticate)                                         \
   ,FN(X_AUTH_TOKEN, 2, X-Auth-Token)                                         \

// make a enum of header name
enum res_hdr_name {
#define FN(HDR, REQD, HDR_STR)       RES_HDR_##HDR
    REDFISH_RES_HDRS(FN), RES_HEADER_COUNT
#undef FN
};

typedef enum res_hdr_name res_hdr_name;

static char * res_hdr_str[] = {
#define FN(HDR, REQD, HDR_STR)     #HDR_STR
    REDFISH_RES_HDRS(FN)
#undef FN
};

#define GET_HEADER_STR(hdr)   req_hdr_str[hdr]


static int res_reqd_tbl[] = {
#define FN(HDR, REQD, HDR_STR)     REQD
    REDFISH_RES_HDRS(FN)
#undef FN
};
#define GET_RES_REQD_LEVEL(hdr_name)      res_reqd_tbl[hdr_name]
