
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



static int my_log_hook(request_rec *r)
{
  double response_time; 
  apr_time_t start_time= r->request_time;
  apr_time_t current_time= apr_time_now();
  apr_time_t time_diff = current_time - start_time;
  bool is_millis = false;
  /*
  if(time_diff < 1000000){
      //log time in milliseconds
      is_millis = true;
      response_time = (double)time_diff/1000;
  }
  else{
      //log time in seconds
      response_time = (double)time_diff/1000000;
  }*/

  //log time only in millisecs
  response_time = (double)time_diff/1000;
  log_request(r->method, r->unparsed_uri, response_time, is_millis);
  store_request(r, r->method, r->unparsed_uri, response_time);

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
    //ap_set_content_type(r, "text/html;charset=ascii");
    r->content_type = "application/json";
    //const char* json = get_api_json();
    const char* json = get_all_data(r);
    ap_rputs(json, r);
    return OK;
}

static int wathi_handler(request_rec *r)
{
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


static void wathi_hooks(apr_pool_t *pool)
{
  ap_hook_log_transaction(my_log_hook, NULL, NULL, APR_HOOK_MIDDLE);
  ap_hook_handler(wathi_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

module AP_MODULE_DECLARE_DATA wathi_module = {
    STANDARD20_MODULE_STUFF,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    wathi_hooks
} ;




