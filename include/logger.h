#ifndef LOGGER_H
#define LOGGER_H
#include <string>
using namespace std;

class Logger
{
private:
    // variabl store file name in which log is saved
    string eventFile;

public:
    // constructor
    Logger(const string &filename);
    // To records events -> level + message
    void log(const string &level, const string &message);
};
#endif // LOGGER_H