#ifndef ADMIN_H
#define ADMIN_H

#include "Person.h"
#include <string>
using namespace std;
/** @brief represent  admin class
 * derived from person class . has full access to the system
 * implement printprofile function to display admin details
 */
class Admin:public Person{
    private :
    string username; /** username of admin */
    string password; /** password of admin */
    public:
    /** @brief constructor of admin class */
    Admin(string n,string eml,string uname,string pwd);

    /** @brief print the profile of the admin
     * override the pure virtual function from person class
     */
    void virtual printProfile() override;
    /** @brief destructor for admin class */
    ~Admin();


};
#endif