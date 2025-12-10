#include "../include/course.h"
#include <iostream>
using namespace std;

// Default constructor
Course::Course()
{
    title = "";
    courseId = "";
    capacity = 0;
    credits = 0;
    enrolledStudents = 0;
}

// Parameterized constructor
Course::Course(string t, string cId, int cap, int cred, int ErS)
{
    title = t;
    courseId = cId;
    capacity = cap;
    credits = cred;
    enrolledStudents = ErS;
}

// Getters
string Course::getTitle() const { return title; }
string Course::getCourseId() const { return courseId; }
int Course::getCapacity() const { return capacity; }
int Course::getCredits() const { return credits; }
int Course::getEnrolledStudents() const { return enrolledStudents; }

// Setters
void Course::setTitle(const string &t) { title = t; }
void Course::setCourseId(const string &cId) { courseId = cId; }
void Course::setCapacity(int c) { capacity = c; }
void Course::setCredits(int cred) { credits = cred; }
void Course::setEnrolledStudents(int enrolled) { enrolledStudents = enrolled; }

// Enrollment methods
bool Course::enrollStudent()
{
    if (enrolledStudents < capacity)
    {
        enrolledStudents++;
        return true;
    }
    else
    {
        cout << "Cannot enroll: course is full!\n";
        return false;
    }
}

bool Course::dropStudent()
{
    if (enrolledStudents > 0)
    {
        enrolledStudents--;
        return true;
    }
    else
    {
        cout << "Cannot drop: no students enrolled!\n";
        return false;
    }
}

// Print course info
void Course::printCourse() const
{
    cout << "Course ID: " << courseId << endl;
    cout << "Title: " << title << endl;
    cout << "Credits: " << credits << endl;
    cout << "Capacity: " << capacity << endl;
    cout << "Enrolled Students: " << enrolledStudents << endl;
    cout << "------------------------\n";
}
