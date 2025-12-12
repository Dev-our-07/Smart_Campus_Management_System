#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include "Person.h"
using namespace std;

    /**
     * @class User
     * @brief Derived class from Person to represent system users
     *
     * Each user has a role: "admin", "teacher", or "student".
     */
    class User : public Person{

    protected:
    string role; /** Role of the user: "admin", "teacher", "student" */


        public :
    /**
     * @brief Constructor for User
     * @param n Name of the user
     * @param e Email of the user
     * @param r Role of the user ("admin", "teacher", "student")
     */
    User(string n, string e, string r);

    /**
     * @brief Get the role of the user
     * @return Role string
     */
    string getRole() ;

    /**
     * @brief Print user profile information
     */
    void printProfile() override;
};

#endif