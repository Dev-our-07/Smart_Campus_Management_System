#include "Admin.h"
#include <iostream>
using namespace std;

/** @brief implementation of admin class */

/** @brief constructor of admin class */
Admin::Admin(string n,string eml,string uname,string pwd):Person(n,eml){
    username=uname;
    password=pwd;
}

/** @brief print the profile of the admin */
void Admin::printProfile(){
    cout<<"-------Admin Profile-------"<<endl;
    cout<<"Name: "<<name<<endl;
    cout<<"Email: "<<email<<endl;
    cout<<"Username: "<<username<<endl;

}
/** @brief destructor for admin class */    
Admin::~Admin(){}

