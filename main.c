#include "http_server.h"
extern void on_connected( uv_stream_t *t, int);
int main()
{
    const int port = 8000;
    http_server svc;
    setup_server( &svc, "0.0.0.0", port);



    printf("Listening on %d\n", port);
    run(&svc, on_connected);


    tls_engine_stop();
    
    return 0;
}
