#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sys/time.h>


typedef long long i64;
typedef unsigned long long u64;

using std::string;
using std::ofstream;
using std::ios;

extern "C" {
    
string log_file="/tmp/log.txt";

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

long get_curr_time()
{
      timeval time;
      gettimeofday(&time, NULL);
      long millis = (time.tv_sec * 1000) + (time.tv_usec / 1000);
      return millis;
}


} //extern 

