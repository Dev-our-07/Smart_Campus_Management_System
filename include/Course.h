#ifndef COURSE_H
#define COURSE_H

#include <string>
using namespace std;

class Course
{
private:
    string title;
    string courseId;
    int capacity;
    int credits;
    int enrolledStudents;

public:
    Course();
    Course(string t, string cId, int cap, int cred, int ErS = 0);

    // Getters
    string getTitle() const;
    string getCourseId() const;
    int getCapacity() const;
    int getCredits() const;
    int getEnrolledStudents() const;

    // Setters
    void setTitle(const string &t);
    void setCourseId(const string &cId);
    void setCapacity(int cap);
    void setCredits(int cred);
    void setEnrolledStudents(int enrolled);

    // Enrollment methods
    bool enrollStudent();
    bool dropStudent();

    // Print course info
    void printCourse() const;
};

#endif
