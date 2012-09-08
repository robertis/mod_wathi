
#include <httpd.h>
#include <http_protocol.h>
#include <http_config.h>
#include <stdbool.h>
#include "ap_config.h"
#include "apr_dbd.h"

#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "ap_config.h"

#include "apr_dbd.h"
#include "mod_dbd.h"
#include "apr_strings.h"

#define MAX_HANDLER 3

#include "../sdk/wathi_sdk.h"


module AP_MODULE_DECLARE_DATA wathi_module ;

typedef struct wathi_cfg {
  int use_db ;			
  const char* data_file;
} wathi_cfg ;


static int my_log_hook(request_rec *r)
{
    double response_time; 
    apr_time_t start_time= r->request_time;
    apr_time_t current_time= apr_time_now();
    apr_time_t time_diff = current_time - start_time;
    bool is_millis = false;
    wathi_cfg* cfg =
	ap_get_module_config(r->per_dir_config, &wathi_module) ;

    //log_num("hook log :: cfg choice ",(i64)cfg->use_db);

    //log time only in millisecs
    response_time = (double)time_diff/1000;
    //log_request(r->method, r->unparsed_uri, response_time, is_millis);
    store_request(r, r->method, r->unparsed_uri, response_time);
    //old school malloc-free, use apr pools instead
}

static int html_handler(request_rec *r)
{
    ap_set_content_type(r, "text/html;charset=ascii");
    const char* msg = get_dashboard_html();
    ap_rputs(msg, r);
    return OK;
}

static int rest_handler(request_rec *r)
{
    r->content_type = "application/json";
    //const char* json = get_api_json();
    const char* json = get_all_data(r);
    ap_rputs(json, r);
    return OK;
}

static int wathi_handler(request_rec *r)
{
    wathi_cfg* cfg =
	ap_get_module_config(r->per_dir_config, &wathi_module) ;

    log_num("cfg use db ",(i64)cfg->use_db);
    log_string("cfg data_file ", (char*)cfg->data_file);
    if (!r->handler || strcmp(r->handler, "wathi")) {
	return DECLINED;
    }

    if (r->method_number != M_GET) {
	return HTTP_METHOD_NOT_ALLOWED;
    }

    if(!strcmp(r->path_info,"/rest")){
	return rest_handler(r);
    }
    else if(!strcmp(r->path_info,"/web")){
	return html_handler(r);
    }

    return DECLINED;

}

static void* wathi_cr_cfg(apr_pool_t* pool, char* x) {
  wathi_cfg* ret = apr_pcalloc(pool, sizeof(wathi_cfg)) ;
  ret->data_file = "/tmp/default-data.txt";
  return ret ;
}

static const command_rec wathi_cmds[] = {
  AP_INIT_FLAG("UseDBForStorage", ap_set_flag_slot,
	(void*)APR_OFFSETOF(wathi_cfg, use_db), ACCESS_CONF,
	"Enable data storage in DB"),
  AP_INIT_TAKE1("FilePathForStorage", ap_set_string_slot,
        (void*)APR_OFFSETOF(wathi_cfg, data_file),
        OR_OPTIONS, "File for storing data instead of DB") ,
  {NULL}
} ;


static void wathi_hooks(apr_pool_t *pool)
{
    ap_hook_log_transaction(my_log_hook, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_handler(wathi_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

module AP_MODULE_DECLARE_DATA wathi_module = {
    STANDARD20_MODULE_STUFF,
    wathi_cr_cfg ,
    NULL,
    NULL,
    NULL,
    wathi_cmds ,
    wathi_hooks
} ;




