
#include "Teacher.h"
#include<iostream>
using namespace std;
/** @brief implementation of Teacher class */

/** @brief constructor for Teacher 
 * @param n Name of the Teaher
 * @param eml email of the teacher
 * @param sub subject assgned to the teacher
 
*/Teacher::Teacher(string n,string eml,string sub):Person(n,eml){
    subject = sub;
}
/** @brief print profile of the teacher */
void Teacher::printProfile(){
    cout<<"-------Teacher Profile-------"<<endl;
    cout<<"Name: "<<name<<endl;
    cout<<"Email: "<<email<<endl;
    cout<<"Subject: "<<subject<<endl;
}
/**@brief destructor for Teacher class */
Teacher::~Teacher(){}

