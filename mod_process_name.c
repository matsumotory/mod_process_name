/* 
**  mod_process_name.c -- Apache sample process_name module
**  [Autogenerated via ``apxs -n process_name -g'']
**
**  To play with this sample module first compile it into a
**  DSO file and install it into Apache's modules directory 
**  by running:
**
**    $ apxs -c -i mod_process_name.c
**
**  Then activate it in Apache's httpd.conf file for instance
**  for the URL /process_name in as follows:
**
**    #   httpd.conf
**    LoadModule process_name_module modules/mod_process_name.so
**    <Location /process_name>
**    SetHandler process_name
**    </Location>
**
**  Then after restarting Apache via
**
**    $ apachectl restart
**
**  you immediately can request the URL /process_name and watch for the
**  output of this module. This can be achieved for instance via:
**
**    $ lynx -mime_header http://localhost/process_name 
**
**  The output should be similar to the following one:
**
**    HTTP/1.1 200 OK
**    Date: Tue, 31 Mar 1998 14:42:22 GMT
**    Server: Apache/1.3.4 (Unix)
**    Connection: close
**    Content-Type: text/html
**  
**    The sample page from mod_process_name.c
*/ 

#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "http_log.h"
#include "http_request.h"
#include "ap_config.h"
#include "apr_strings.h"
#include <sys/prctl.h>
#include <string.h>

#define MODULE_NAME "mod_process_name"
#define MODULE_VERSION "0.0.1"

#define CORE_PRIVATE


/* The sample content handler */
static int process_name_handler(request_rec *r)
{
    //if (strcmp(r->handler, "process_name")) {
    //    return DECLINED;
    //}

    //if (prctl(PR_SET_NAME, r->filename) =! 0)
    char bprog_name[16];
    char aprog_name[16];

    prctl(PR_GET_NAME, bprog_name);
    int ret = prctl(PR_SET_NAME, r->filename);

    ap_log_error(APLOG_MARK
        , APLOG_NOTICE
        , 0
        , NULL
        , "%s %s: %s / %s mechanism enabled. ret: %d before: %s argv: %s"
        , MODULE_NAME
        , __func__
        , MODULE_NAME
        , MODULE_VERSION
        , ret
        , bprog_name
        , r->server->process->argv[0]
    );

    //r->server->process->argv = apr_pstrdup(r->pool, "hoge");
    r->server->process->argv = apr_pstrdup(r->pool, "hoge");

    ap_log_error(APLOG_MARK
        , APLOG_NOTICE
        , 0
        , NULL
        , "%s %s: %s / %s mechanism enabled. ret: %d before: %s argv: %s"
        , MODULE_NAME
        , __func__
        , MODULE_NAME
        , MODULE_VERSION
        , ret
        , bprog_name
        , r->server->process->argv[0]
    );
    ret = prctl(PR_GET_NAME, aprog_name);

    ap_log_error(APLOG_MARK
        , APLOG_NOTICE
        , 0
        , NULL
        , "%s %s: %s / %s mechanism enabled. ret: %d after: %s"
        , MODULE_NAME
        , __func__
        , MODULE_NAME
        , MODULE_VERSION
        , ret
        , aprog_name
    );
    //if (!r->header_only)
    //    ap_rputs("The sample page from mod_process_name.c\n", r);

    return DECLINED;
}

static void process_name_register_hooks(apr_pool_t *p)
{
    ap_hook_access_checker(process_name_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

/* Dispatch list for API hooks */
module AP_MODULE_DECLARE_DATA process_name_module = {
    STANDARD20_MODULE_STUFF, 
    NULL,                  /* create per-dir    config structures */
    NULL,                  /* merge  per-dir    config structures */
    NULL,                  /* create per-server config structures */
    NULL,                  /* merge  per-server config structures */
    NULL,                  /* table of config file commands       */
    process_name_register_hooks  /* register hooks                      */
};

