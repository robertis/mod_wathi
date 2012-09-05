#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sys/time.h>
#include "html.h"
#include <sstream>

//for apr_dbd
#include <httpd.h>
#include <http_protocol.h>
#include <http_config.h>
#include "apr_dbd.h"
#include "mod_dbd.h"
#include "apr_strings.h"
#include <stdbool.h>
#include "ap_config.h"



#define MAX_HANDLER 3

typedef long long i64;
typedef unsigned long long u64;

using std::string;
using std::ofstream;
using std::ios;

//apr_dbd
static ap_dbd_t *(*authn_dbd_acquire_fn)(request_rec*) = NULL;
static void (*authn_dbd_prepare_fn)(server_rec*, const char*, const char*) = NULL;

extern "C" {
    
string log_file="/tmp/log.txt";


const char* get_dashboard_html(){
    return html.c_str();
}
const char* get_api_json(){
    return json.c_str();
}

void log_request(const char* method, char* unparsed_uri, double t, bool is_millis)
{
    ofstream myfile;
    myfile.open (log_file.c_str(), ios::app);
    myfile << method;
    myfile << "\t";
    myfile << unparsed_uri;
    myfile << "\t";
    myfile << t;
    if(is_millis){
	myfile << " milliseconds";
    }
    else{
	myfile << " seconds";
    }
    myfile << "\n";
    myfile.close();
}

void log_num(char* msg, i64 t)
{
    ofstream myfile;
    myfile.open (log_file.c_str(), ios::app);
    myfile << msg;
    myfile << t;
    myfile << "\n";
    myfile.close();

}

void log_string(char* key, char* value )
{
    ofstream myfile;
    myfile.open (log_file.c_str(), ios::app);
    myfile << key;
    myfile << "\t";
    myfile << value;
    myfile << "\n";
    myfile.close();

}

long get_curr_time()
{
      timeval time;
      gettimeofday(&time, NULL);
      long millis = (time.tv_sec * 1000) + (time.tv_usec / 1000);
      return millis;
}

const char* get_all_data(request_rec* r)
{
    ap_dbd_t* dbd = NULL;
    apr_status_t rv;
    apr_dbd_results_t* res = NULL;
    apr_dbd_row_t *row = NULL;

    authn_dbd_acquire_fn = APR_RETRIEVE_OPTIONAL_FN(ap_dbd_acquire);
    authn_dbd_prepare_fn = APR_RETRIEVE_OPTIONAL_FN(ap_dbd_prepare);

    if ((dbd = authn_dbd_acquire_fn(r)) == NULL) return "";

    const char* id;
    const char* method;
    const char* uri;
    const char* time_stamp;
    const char* response_time;

    std::string query = "SELECT * FROM requests ORDER BY id DESC LIMIT 100;";

    apr_dbd_select(dbd->driver, r->pool, dbd->handle, &res, query.c_str(), 0);

    std::ostringstream json_str;
    json_str << "{\"result\":[";

    int i =0;

    for (rv = apr_dbd_get_row(dbd->driver, r->pool, res, &row, -1);
	     rv != -1;
	     rv = apr_dbd_get_row(dbd->driver, r->pool, res, &row, -1)) 
    {

	id = apr_dbd_get_entry(dbd->driver, row, 0);
	method = apr_dbd_get_entry(dbd->driver, row, 1);
	uri = apr_dbd_get_entry(dbd->driver, row, 2);
	time_stamp = apr_dbd_get_entry(dbd->driver, row, 3);
	response_time = apr_dbd_get_entry(dbd->driver, row, 4);
	if(id == NULL) id = "null";
	if(method == NULL) method = "null";
	if(uri == NULL) uri = "null";
	if(time_stamp == NULL) time_stamp = "null";
	if(response_time == NULL) response_time = "null";

	if(i > 0){
	    json_str << " ,";
	}
	i++;

	json_str << "{ \"id\" : \"";
	json_str << id;
	json_str << "\" , \"method\" : \"";
	json_str << method;
	json_str << "\" , \"uri\" : \"";
	json_str << uri;
	json_str << "\" , \"time_stamp\" : \"";
	json_str << time_stamp;
	json_str << "\" , \"response_time\" : \"";
	json_str << response_time;
	json_str << "\" }";
    }
    json_str << " ]}";

    return json_str.str().c_str();

}

int store_request(request_rec *r, const char* method, char* unparsed_uri, 
	double response_time){

    ap_dbd_t* dbd = NULL;
    apr_status_t rv;
    apr_dbd_results_t* res = NULL;
    apr_dbd_row_t *row = NULL;
    int i = 0;
    int n = 0;
    int nrows=0;
    char* time_str=(char*)malloc(APR_CTIME_LEN + 1);
    apr_ctime(time_str, r->request_time);

    authn_dbd_acquire_fn = APR_RETRIEVE_OPTIONAL_FN(ap_dbd_acquire);
    authn_dbd_prepare_fn = APR_RETRIEVE_OPTIONAL_FN(ap_dbd_prepare);

    if ((dbd = authn_dbd_acquire_fn(r)) == NULL)
        return 0;

    const char* id;
    const char* name;

    std::ostringstream strs;
    strs << response_time;
    std::string response_time_str = strs.str();

    string insert_query ="insert into requests (method,uri,time_stamp,response_time)  values ('";
    std::ostringstream query_str;
    query_str << insert_query << method << "','" << unparsed_uri ;
    query_str << "','" << time_str ;
    query_str << "'," << response_time_str << ")";


    log_string("query",(char*) query_str.str().c_str());
    apr_dbd_query(dbd->driver,dbd->handle, &nrows,query_str.str().c_str());
    log_num("num rows inserted = ",nrows);

    //old school free/malloc
    if(time_str !=NULL){
	free(time_str);
	time_str= NULL;
    }

    return 1;

}

const char* get_request_data(const char* method, char* unparsed_uri, double response_time)
{
}

} //extern 

