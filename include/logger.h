#ifndef LOGGER_H
#define LOGGER_H

#include <string>
using namespace std;

class Logger
{
private:
    string logfile;

public:
    Logger();
    Logger(string filename);
    void log(string level, string module, string message);
};

#endif
