#ifndef TEACHER_H
#define TEACHER_H

#include "person.h"
#include <string>
using namespace std;
/**
 * @ class Teacher
 * @brief Derived class from Person representing a Teacher
 * inherit from person. store attribute like subject
 * implement printprofile function to display teacher details
 */
class Teacher:public Person{
    private :
    string subject; /** subject  assigned to the teacher */

    public:
    /** @brief constructor for Teacher 
     * @param n Name of the Teaher
     * @param eml email of the teacher
     * @param sub subject assgned to the teacher
     
    */
   Teacher(string n, string eml,string sub);
   
   /** @brief print the profile of the teacher
    * override the pure virtual function from person class
    * 
    */
   void virtual  printProfile() override;

   /** @brief destructor  for the teacher class */
   ~Teacher();
};
#endif