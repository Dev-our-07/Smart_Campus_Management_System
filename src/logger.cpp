#include "../include/Logger.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include<cstring>
using namespace std;

Logger ::Logger(){
    logfile = "logs/events.log";
}
Logger::Logger(string filename)
{
    logfile = filename;
}

void Logger::log(string level, string module, string message)
{
    ofstream myfile(logfile, ios::app);
    if (!myfile.is_open())
    {
        cout << "Cannot open log file!" << endl;
        return;
    }

    time_t now = time(0);
    char *dt = ctime(&now);
    dt[strlen(dt)-1] = '\0';


    myfile << "[" << dt << "] [" << level << "] [" << module << "] " << message << endl;
    myfile.close();
}
