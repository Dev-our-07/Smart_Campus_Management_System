#ifndef PERSON_H
#define PERSON_H
#include<iostream>
#include<string>
using namespace std;
/**
 * @brief person
 * @brief Base class for all the other clases  in the system
 * store  name and email
 * define virtual fn printprofile
 */

class Person{
    protected:
    string name; /** Name of the person */
    string email; /** Email of the person */
    public:
  
    /** @brief  constructor for person
     * param n Name of the person 
     * param eml email of the email
     */ 

    Person(string n,string eml);

    /**
     * @brief pure virtual function to show profile information
     * this function must be implemented by all the derived classes
     */
    virtual void printProfile()=0;
    /**
     * @brief virtual destructor
     */
    virtual ~Person();






};
#endif

