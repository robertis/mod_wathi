
#include <httpd.h>
#include <http_protocol.h>
#include <http_config.h>
#include <stdbool.h>

#include "../sdk/wathi_sdk.h"


static int my_log_hook(request_rec *r)
{
  double response_time; 
  apr_time_t start_time= r->request_time;
  apr_time_t current_time= apr_time_now();
  apr_time_t time_diff = current_time - start_time;
  bool is_millis = false;
  if(time_diff < 1000000){
      //log time in milliseconds
      is_millis = true;
      response_time = (double)time_diff/1000;
  }
  else{
      //log time in seconds
      response_time = (double)time_diff/1000000;
  }
  log_request(r->method, r->unparsed_uri, response_time, is_millis);

}


static void wathi_hooks(apr_pool_t *pool)
{
  ap_hook_log_transaction(my_log_hook, NULL, NULL, APR_HOOK_MIDDLE);
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




