#include "request_handler.h"
#include "http_parser.h"



int handle_http_req(const request *req, response *reply)
{
    if ( !(req  && reply)) {
        return -1;
    }

    enum http_method method = req->requested_method;
    char *rqsted_res = req->resource_path;

    for(int i = 0; i < route.size; ++i) {
        if( strcasecmp(rqsted_res, route[i].path) == 0) {
        }
    }

    return 0;
}
