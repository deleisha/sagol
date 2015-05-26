#ifndef __PLGN_API_H__
#define __PLGN_API_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct schema_ver
{
    int major;
    int minor;
    int fix;
} schema_ver;


struct main_svc;
typedef struct svc_hook
{
    const char *resource;
    const struct main_svc *platformServices;
} svc_hook;

/*
* Used by plugin manager to create and destroy the 
* plugins register this functions with PM
*/
typedef void * (*plgn_ctor)(svc_hook *);
typedef int (*plgn_dtor)(void *);


//parameters being used by plugins for registrations.
//implementation langue of the plugin
typedef enum coded_lang
{
    C   = 0x01,
    //CPP,
    PYTHON = 0x02
} coded_lang;


typedef struct plgn_info
{
    schema_ver vrsn;
    plgn_ctor createFunc;
    plgn_dtor destroyFunc;
    coded_lang lang;
} plgn_info;


//implemented by PM for registering the plugins
typedef int (*register_plgn)(const char *nodeType, const plgn_info *info);
//handle to main app , used for error reporting and logging
typedef int (*do_upcall)(const char *svc_name, void *svc_params);

//encapsulation of main application
typedef struct main_svc
{
    schema_ver vrsn;
    register_plgn registerObject;
    do_upcall invokeService;
} main_svc;






typedef int (*plgn_exit)();
typedef plgn_exit (*plgn_init)(const main_svc *);


plgn_exit entry_pt(const main_svc *svc);

#ifdef  __cplusplus
}
#endif
#endif /* __PLGN_API_H__ */
