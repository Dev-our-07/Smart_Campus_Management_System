#include <iostream>
#include <string>
#include "../include/dashboard.h"

using namespace std;

// -------------------- ADMIN DASHBOARD --------------------
void showAdminDashboard(CourseManager &cm, Logger &logger)
{
    int choice;

    while (true)
    {
        cout << "\n------- ADMIN DASHBOARD -------\n";
        cout << "1. Manage Courses\n";
        cout << "2. Manage Students\n";
        cout << "3. View System Logs\n";
        cout << "4. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int courseChoice;
            cout << "\n--- Course Management ---\n";
            cout << "1. Add Course\n";
            cout << "2. Update Course\n";
            cout << "3. Delete Course\n";
            cout << "4. View All Courses\n";
            cout << "5. Back to Admin Dashboard\n";
            cout << "Enter your choice: ";
            cin >> courseChoice;

            switch (courseChoice)
            {
            case 1:
            {
                string title, courseId;
                int credits, capacity;
                cout << "Enter Course Title: ";
                cin >> ws;
                getline(cin, title);
                cout << "Enter Course ID: ";
                cin >> courseId;
                cout << "Enter Credits: ";
                cin >> credits;
                cout << "Enter Capacity: ";
                cin >> capacity;

                Course newCourse(title, courseId, credits, capacity);
                cm.addCourse(newCourse);

                logger.log("INFO", "AdminDashboard", "Added course: " + courseId + " - " + title);
                break;
            }
            case 2:
            {
                string courseId, newTitle;
                int newCredits, newCapacity;
                cout << "Enter Course ID to update: ";
                cin >> courseId;
                cout << "Enter New Title: ";
                cin >> ws;
                getline(cin, newTitle);
                cout << "Enter New Credits: ";
                cin >> newCredits;
                cout << "Enter New Capacity: ";
                cin >> newCapacity;

                cm.updateCourse(courseId, newTitle, newCredits, newCapacity);
                logger.log("INFO", "AdminDashboard", "Updated course: " + courseId + " - " + newTitle);
                break;
            }
            case 3:
            {
                string courseId;
                cout << "Enter Course ID to delete: ";
                cin >> courseId;
                cm.deleteCourse(courseId);
                logger.log("INFO", "AdminDashboard", "Deleted course: " + courseId);
                break;
            }
            case 4:
                cm.printAllCourses();
                logger.log("INFO", "AdminDashboard", "Viewed all courses");
                break;
            case 5:
                break;
            default:
                cout << "Invalid choice! Try again.\n";
            }
            break;
        }
        case 2:
            cout << "Viewing / Managing Students...\n";
            logger.log("INFO", "AdminDashboard", "Accessed student management");
            break;
        case 3:
            cout << "Viewing System Logs...\n";
            logger.log("INFO", "AdminDashboard", "Viewed system logs");
            break;
        case 4:
            cout << "Logging out...\n";
            logger.log("INFO", "AdminDashboard", "Admin logged out");
            return;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    }
}

// -------------------- TEACHER DASHBOARD --------------------
void showTeacherDashboard(Logger &logger)
{
    int choice;
    while (true)
    {
        cout << "\n------- TEACHER DASHBOARD -------\n";
        cout << "1. View Assigned Courses\n";
        cout << "2. Manage Course Content (Attendance / Grades)\n";
        cout << "3. View Student Performance\n";
        cout << "4. Update Profile\n";
        cout << "5. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Viewing Assigned Courses...\n";
            logger.log("INFO", "TeacherDashboard", "Viewed assigned courses");
            break;
        case 2:
            cout << "Managing Attendance / Grades...\n";
            logger.log("INFO", "TeacherDashboard", "Managed attendance / grades");
            break;
        case 3:
            cout << "Viewing Student Performance...\n";
            logger.log("INFO", "TeacherDashboard", "Viewed student performance");
            break;
        case 4:
            cout << "Updating Profile...\n";
            logger.log("INFO", "TeacherDashboard", "Updated profile");
            break;
        case 5:
            cout << "Logging out...\n";
            logger.log("INFO", "TeacherDashboard", "Teacher logged out");
            return;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    }
}

// -------------------- STUDENT DASHBOARD --------------------
void showStudentDashboard(Logger &logger)
{
    int choice;
    while (true)
    {
        cout << "\n------- STUDENT DASHBOARD -------\n";
        cout << "1. View Enrolled Courses\n";
        cout << "2. Enroll in a Course\n";
        cout << "3. View Grades\n";
        cout << "4. Update Profile\n";
        cout << "5. Drop a Course\n";
        cout << "6. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Viewing Enrolled Courses...\n";
            logger.log("INFO", "StudentDashboard", "Viewed enrolled courses");
            break;
        case 2:
            cout << "Enrolling in a Course...\n";
            logger.log("INFO", "StudentDashboard", "Enrolled in a course");
            break;
        case 3:
            cout << "Viewing Grades...\n";
            logger.log("INFO", "StudentDashboard", "Viewed grades");
            break;
        case 4:
            cout << "Updating Profile...\n";
            logger.log("INFO", "StudentDashboard", "Updated profile");
            break;
        case 5:
            cout << "Dropping a Course...\n";
            logger.log("INFO", "StudentDashboard", "Dropped a course");
            break;
        case 6:
            cout << "Logging out...\n";
            logger.log("INFO", "StudentDashboard", "Student logged out");
            return;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    }
}