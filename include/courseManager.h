#ifndef COURSEMANAGER_H
#define COURSEMANAGER_H

#include <vector>
#include <string>
#include "course.h"
#include "Logger.h"
using namespace std;

class CourseManager
{
private:
    vector<Course> courses;
    string filename;
    Logger logger;

public:
    CourseManager(string file = "courses.txt");

    void addCourse(const Course &c);
    void updateCourse(string courseId, string newTitle, int newCredits, int newCapacity);
    void deleteCourse(string courseId);
    bool enrollStudent(string courseId);
    bool dropStudent(string courseId);
    void printAllCourses() const;
    void saveCourses() const;
    void loadCourses();
};

#endif
