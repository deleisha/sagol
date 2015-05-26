typedef struct module {
} Module;


struct Node {
    char *path;
    enum http_method methods[10];
    int num_method;
    char *lib;
    char *interface;
};

int d__entry_point(Node *nd)
{
    nd->path = "/redfish/v1/";

    nd->methods[0] = HTTP_GET;
    nd->methods[1] = HTTP_POST;
    nd->num_method = 2;
    nd->lib = "libtest.so";
    nd->interface = "C";
}


char *GET()
{
    return "{\"name\": \"Faizan\"}";
}
