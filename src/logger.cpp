#include "Logger.h"
#include<fstream>
#include<ctime>
#include<cstring>
using namespace std;

Logger::Logger(const string &filename){
        eventFile=filename;
}
void Logger::log(const string &level, const string &message){

    ofstream myfile;

    // file open in append mode
    myfile.open(eventFile,ios::app);

    // open check
    if(!myfile.is_open()){
        cout<<"Error : cannot open log file!"<<endl;
        return;

    }
    
    // Time extract
    time_t currentTime= time(0);
    char* dt = ctime(&currentTime);

    // file write
    myfile << "["<<dt<<"]"<<" "<<"["<<level <<"]"<<message<<endl;

    myfile.close();
}
 