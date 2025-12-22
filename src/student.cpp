#include "Student.h"
#include <iostream>
using namespace std;
/** @brief implementation of student class */
/**
 * @brief constructor for student
 * @paran n  Name of the student
 * @param eml emaiil of the student
 * @param rno roll no of the student
 */
Student::Student(const string n, const string eml,const string rno):Person(n,eml){
    rollno=rno;
    }

/** @brief printprofile fn to display detail of stdent */
void Student::printProfile(){
    cout<<"-------Student Profile-------"<<endl;
    cout<<"Name: "<<name<<endl;
    cout<<"Email: "<<email<<endl;
    cout<<"Roll No: "<<rollno<<endl;
}

/** @brief destructor for student */
Student::~Student(){}