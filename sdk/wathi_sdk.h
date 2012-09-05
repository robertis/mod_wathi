#ifndef _CHECK_SDK_H
#define _CHECK_SDK_H
typedef long long i64;
typedef unsigned long long u64;

void log_num(char* msg, i64 t);
void log_request(const char* method, char* unparsed_uri, double t, bool is_millis);
const char* get_dashboard_html();
const char* get_api_json();
void log_string(char* key, char* value );

//stores the request data in the database
int store_request(request_rec *r, const char* method, char* unparsed_uri, double response_time);
const char* get_request_data(const char* method, char* unparsed_uri, double response_time);
const char* get_all_data(request_rec* r);



#endif
