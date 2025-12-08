#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>

class Logger
{
private:
    std::ofstream file;

public:
    Logger(const std::string &filename);
    void log(const std::string &message);
    ~Logger();
};

#endif