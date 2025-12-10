#include "../include/CourseManager.h"
#include <iostream>
#include <fstream>
using namespace std;

CourseManager::CourseManager(string file) {
    filename = file;
    logger = Logger("logs/events.log");
    loadCourses();
}

void CourseManager::addCourse(const Course &c) {
    courses.push_back(c);
    cout << "Course added: " << c.getTitle() << endl;
    logger.log("INFO", "CourseManager", "Course added: " + c.getCourseId());
    saveCourses();
}

void CourseManager::updateCourse(string courseId, string newTitle, int newCredits, int newCapacity) {
    for(int i=0; i<courses.size(); i++) {
        if(courses[i].getCourseId() == courseId) {
            courses[i].setTitle(newTitle);
            courses[i].setCredits(newCredits);
            courses[i].setCapacity(newCapacity);

            cout << "Course updated successfully!\n";
            logger.log("INFO", "CourseManager", "Course updated: " + courseId);
            saveCourses();
            return;
        }
    }
    cout << "Course not found: " << courseId << endl;
    logger.log("WARNING", "CourseManager", "Update failed: " + courseId);
}

void CourseManager::deleteCourse(string courseId) {
    for(int i=0; i<courses.size(); i++) {
        if(courses[i].getCourseId() == courseId) {
            courses.erase(courses.begin() + i);
            cout << "Course deleted.\n";
            logger.log("INFO", "CourseManager", "Course deleted: " + courseId);
            saveCourses();
            return;
        }
    }
    cout << "Course not found: " << courseId << endl;
    logger.log("WARNING", "CourseManager", "Delete failed: " + courseId);
}
// ----------------------------------------------------------
//      ENROLL IN  Courses
// ----------------------------------------------------------
bool CourseManager::enrollStudent(string courseId)
{
    for (int i = 0; i < courses.size(); i++)
    {
        if (courses[i].getCourseId() == courseId)
        {

            bool ok = courses[i].enrollStudent();

            if (ok)
            {
                cout << "Student enrolled successfully in " << courseId << endl;
                logger.log("INFO", "CourseManager", "Student enrolled in: " + courseId);
            
            }

              
            else
            {
                cout << "Cannot enroll: course is full!" << endl;
                logger.log("WARNING", "CourseManager", "Course full: " + courseId);
            }

            saveCourses();
            return ok;
        }
    }

    cout << "Course not found: " << courseId << endl;
    logger.log("WARNING", "CourseManager", "Enroll failed (not found): " + courseId);
    return false;
}

bool CourseManager::dropStudent(string courseId) {
    for(int i=0; i<courses.size(); i++) {
        if(courses[i].getCourseId() == courseId) {
            bool ok = courses[i].dropStudent();
            if(ok)
                logger.log("INFO", "CourseManager", "Student dropped from: " + courseId);
            else
                logger.log("WARNING", "CourseManager", "Drop failed (no students): " + courseId);
            saveCourses();
            return ok;
        }
    }
    logger.log("WARNING", "CourseManager", "Drop failed (not found): " + courseId);
    return false;
}

// ----------------------------------------------------------
//                 Print All Courses
// ----------------------------------------------------------
void CourseManager::printAllCourses() const
{
    if (courses.empty())
    {
        cout << "No courses available.\n";
        return;
    }

    cout << "\n======= ALL COURSES =======\n";
    for (int i = 0; i < courses.size(); i++)
    {
        cout << "\nCourse #" << (i + 1) << ":\n";
        cout << "Title: " << courses[i].getTitle() << endl;
        cout << "Course ID: " << courses[i].getCourseId() << endl;
        cout << "Credits: " << courses[i].getCredits() << endl;
        cout << "Capacity: " << courses[i].getCapacity() << endl;
        cout << "Enrolled Students: " << courses[i].getEnrolledStudents() << endl;
        cout << "--------------------------\n";
    }
}

void CourseManager::saveCourses() const {
    ofstream out(filename);
    if(!out.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }
    for(int i=0; i<courses.size(); i++) {
        out << courses[i].getCourseId() << " "
            << courses[i].getTitle() << " "
            << courses[i].getCredits() << " "
            << courses[i].getCapacity() << " "
            << courses[i].getEnrolledStudents() << endl;
    }
    out.close();
}

void CourseManager::loadCourses() {
    ifstream in(filename);
    if(!in.is_open()) return;

    courses.clear();

    string id, title;
    int credits, capacity, enrolled;

    while(in >> id >> title >> credits >> capacity >> enrolled) {
        Course c(title, id, capacity, credits, enrolled);
        courses.push_back(c);
    }
    in.close();
}
