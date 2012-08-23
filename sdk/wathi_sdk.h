#ifndef _CHECK_SDK_H
#define _CHECK_SDK_H
typedef long long i64;
typedef unsigned long long u64;

void log_num(char* msg, i64 t);
void log_request(const char* method, char* unparsed_uri, double t, bool is_millis);
const char* get_dashboard_html();
const char* get_api_json();
void log_string(char* key, char* value );



#endif
