// auth.h
#ifndef AUTH_H
#define AUTH_H

#include <string>

class Auth {
public:
    Auth();
    ~Auth();

    bool verifyPassword(const std::string& password, const std::string& hash);
    std::string generateHash(const std::string& password);
};

#endif // AUTH_H