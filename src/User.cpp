#include "User.h"
#include <iostream>
//constructor implementation
User::User(string n, string e, string r) : Person(n, e){
    role = r;
}
//getRole implementation
string User::getRole() {
    return role;
}
// printProfile implementation
void User::printProfile() {
   cout << "------- User Profile -------" << std::endl;
   cout << "Name: " << name << std::endl;
   cout << "Email: " << email << std::endl;
    cout << "Role: " << role << std::endl;
}