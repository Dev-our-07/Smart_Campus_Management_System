#ifndef STUDENT_H
#define STUDENT_H
#include "person.h"
#include<string>
using namespace std;

/**
 * @ class Student
 * @brief Derived class from Person representing a student
 * inherit from person. store attribute like roll no
 * implement printprofile function to display studenet details
 */
class Student :public Person{
    private: 
    string rollno; /** roll no of student */

    public:
    /** @brief constructor for student
     * @paran n  Name of the student
     * @param eml emaiil of the student
     * @param rno roll no of the student
     */
    Student(string n,string eml ,   string rno);
    /**
     * @brief print the profile of the student
     * override the pure virtual function from person class
     */
    void virtual printProfile() override;
    /**
     * @brief destructor for student
     */
    ~Student();

};
#endif