#include <iostream>
#include <string>
#include "../include/dashboard.h"
#include "../include/CourseManager.h"
#include "../include/AttendanceManager.h"
#include "../include/MarksManager.h"
#include "../include/Library.h"



using namespace std;

//-------------------- ADMIN DASHBOARD --------------------
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
// -------------------- TEACHER DASHBOARD --------------------
void showTeacherDashboard(AttendanceManager &am, MarksManager &mm, LibraryManager &lib, Logger &logger)

    {
        int choice;

        while (true)
        {
            cout << "\n------- TEACHER DASHBOARD -------\n";
            cout << "1. Attendance Management\n";
            cout << "2. Examination & Marks\n";
            cout << "3. Library Management\n";
            cout << "4. Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            // ================= ATTENDANCE =================
            case 1:
            {
                int attChoice;
                cout << "\n--- Attendance Management ---\n";
                cout << "1. Mark Attendance\n";

                cout << "2. View Attendance (by date)\n";
                cout << "3. Back\n";
                cout << "Enter choice: ";
                cin >> attChoice;

                switch (attChoice)
                {
                case 1:
                    am.markAttendance(); // call mark attendance function
                    logger.log("INFO", "TeacherDashboard", "Attendance marked");
                    break;

                case 2:
                    am.viewAttendanceByDate(); // ✅ REAL CALL
                    logger.log("INFO", "TeacherDashboard", "Viewed attendance by date");
                    break;

                case 3:
                    break;

                default:
                    cout << "Invalid choice!\n";
                }
                break;
            }

            // ================= MARKS =================
            case 2:
            {
                int markChoice;
                cout << "\n--- Examination & Marks ---\n";
                cout << "1. Create Exam\n";
                cout << "2. Enter Student Marks\n";
                cout << "3. Save Marks to File\n";
                cout << "4. View Marks\n";
                cout << "5. Generate Result Report\n";
                cout << "6. Back\n";
                cout << "Enter choice: ";
                cin >> markChoice;

                try
                {
                    switch (markChoice)
                    {
                    case 1:
                        mm.createExam();
                        logger.log("INFO", "TeacherDashboard", "Exam created");
                        break;

                    case 2:
                        mm.enterMarks();
                        logger.log("INFO", "TeacherDashboard", "Entered student marks");
                        break;
                    case 3:
                        mm.saveMarks();
                        logger.log("INFO", "TeacherDashboard", "Saved marks to file");
                        break;

                    case 4:
                        mm.viewMarks();
                        logger.log("INFO", "TeacherDashboard", "Generated result report");
                        break;

                    case 5:
                        mm.loadMarks();
                        logger.log("INFO", "TeacherDashboard", "Loaded marks from file");
                        break;

                    default:
                        cout << "Invalid choice!\n";
                    }
                }
                catch (exception &e)
                {
                    cout << "Error: " << e.what() << endl;
                    logger.log("ERROR", "TeacherDashboard", e.what());
                }
                break;
            }

            // ================= LIBRARY =================
            case 3:
            {
                int libChoice;
                cout << "\n--- Library Management ---\n";
                cout << "1. Add Book\n";
                cout << "2. Issue Book\n";
                cout << "3. Return Book\n";
                cout << "4. Back\n";
                cout << "Enter choice: ";
                cin >> libChoice;

                try
                {
                    switch (libChoice)
                    {
                    case 1:
                        lib.addBook();
                        logger.log("INFO", "TeacherDashboard", "Added new book");
                        break;

                    default:
                        cout << "Invalid choice!\n";
                    }
                }
                catch (exception &e)
                {
                    cout << "Error: " << e.what() << endl;
                    logger.log("ERROR", "TeacherDashboard", e.what());
                }
                break;
            }

            // ================= LOGOUT =================
            case 4:
                cout << "Logging out...\n";
                logger.log("INFO", "TeacherDashboard", "Teacher logged out");
                return;

            default:
                cout << "Invalid choice! Try again.\n";
            }
        }
    }

    // -------------------- STUDENT DASHBOARD --------------------
    // -------------------- STUDENT DASHBOARD --------------------
    void showDashboard(AttendanceManager &am, MarksManager &mm, LibraryManager &lib, Logger &logger)

    {
        int choice;

        while (true)
        {
            cout << "\n------- STUDENT DASHBOARD -------\n";
            cout << "1. View Attendance\n";
            cout << "2. View Marks\n";
            cout << "3. issue Book\n";
            cout << "5. Return Book\n";
            cout << "4. Logout\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                am.viewAttendanceForStudent();
                logger.log("INFO", "StudentDashboard", "Viewed attendance");
                break;

            case 2:
                mm.viewMarks();
                logger.log("INFO", "StudentDashboard", "Viewed marks");
                break;

            case 3:
                lib.issueBook();
                logger.log("INFO", "StudentDashboard", "Viewed library status");
                break;

            case 4:
                lib.returnBook();
                logger.log("INFO", "StudentDashboard", "Returned book");
                break;
            case 5:

                cout << "Logging out...\n";
                logger.log("INFO", "StudentDashboard", "Student logged out");
                return;

            default:
                cout << "Invalid choice! Try again.\n";
            }
        }
    }
