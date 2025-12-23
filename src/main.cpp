/**
 * @file main.cpp
 * @brief Entry point for the Smart Campus Management System.
 *
 * This file handles:
 * - User authentication (login/register)
 * - Directory setup for user data
 * - Role-based dashboard routing (Admin, Teacher, Student)
 */

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

#include "../include/auth.h"
#include "../include/CourseManager.h"
#include "../include/course.h"
#include "../include/Logger.h"
#include "../include/Dashboard.h"
#include "../include/User.h"
#include "../include/AttendanceManager.h"
#include "../include/MarksManager.h"
#include "../include/LibraryManager.h"

#if defined(__cpp_lib_filesystem)
namespace fs = std::filesystem; ///< Use standard filesystem if supported
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem; ///< Fallback to experimental filesystem
#endif

/**
 * @brief Main function for SCMS.
 *
 * Initializes required managers, handles authentication, and loads
 * dashboards based on assigned user roles.
 *
 * @return int Program exit status.
 */
int main()
{
    /// Logger to record all program events
    Logger logger("logs/events.log");

    /// Authentication handler for hashing and verifying passwords
    Auth auth;

    /// Course manager responsible for reading/writing course data
    CourseManager cm("data/courses.txt");

    /// Attendance manager for handling attendance records
    AttendanceManager am("attendance.txt");

    // Marks manager for handling exam and marks records
    MarksManager mm("data/marks.txt");

   

    

    /// Library manager for handling library operations
    LibraryManager lib("books.txt");

    
    
   

    ///

    // --------------------------------------------------------
    //  DATA DIRECTORY SETUP
    // --------------------------------------------------------

    fs::path cwdData("data");                      ///< Data directory inside current folder
    fs::path parentData = fs::path("..") / "data"; ///< Data directory in parent folder
    fs::path dataDir;                              ///< Chosen valid data directory

    /**
     * @brief Determine appropriate data directory.
     *
     * Priority:
     * 1. ../data
     * 2. ./data
     * 3. Create ../data
     * 4. Create ./data
     */
    if (fs::exists(parentData))
        dataDir = parentData;
    else if (fs::exists(cwdData))
        dataDir = cwdData;
    else
    {
        std::error_code ec;
        if (fs::create_directories(parentData, ec))
            dataDir = parentData;
        else if (fs::create_directories(cwdData, ec))
            dataDir = cwdData;
        else
            dataDir = cwdData; ///< Fallback directory
    }

    // --------------------------------------------------------
    //  MAIN MENU LOOP
    // --------------------------------------------------------

    while (true)
    {
        std::cout << "\n================ SMART CAMPUS MANAGEMENT SYSTEM ================\n";
        std::cout << "1. Login\n2. Register\n3. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        // =====================================================
        //  LOGIN SECTION
        // =====================================================
        if (choice == 1)
        {
            std::string username, password;

            std::cout << "Enter username: ";
            std::cin.ignore();
            std::getline(std::cin, username);

            std::cout << "Enter password: ";
            std::getline(std::cin, password);

            fs::path userFile = dataDir / (username + ".txt");

            /**
             * @brief Attempt to load user file.
             */
            std::ifstream file(userFile.string());
            if (file.is_open())
            {
                std::string storedHash, email, role;

                std::getline(file, storedHash); ///< Line 1: hashed password
                std::getline(file, email);      ///< Line 2: email address
                std::getline(file, role);       ///< Line 3: user role
                file.close();

                /**
                 * @brief Verify password using Auth class.
                 */
                if (auth.verifyPassword(password, storedHash))
                {
                    std::cout << "Login successful! Welcome " << username << "\n";

                    /// Create logged-in user object
                    User currentUser(username, email, role);
                    currentUser.printProfile();

                    logger.log("INFO", "Login", "User logged in: " + username);

                    /**
                     * @brief Route user to role-based dashboards.
                     */
                    if (currentUser.getRole() == "Admin")
                        showAdminDashboard(cm, logger);

                    else if (currentUser.getRole() == "Teacher")
                        showTeacherDashboard(am, mm, lib, logger);
                    

                    else if (currentUser.getRole() == "Student")
                        showStudentDashboard(am, mm, lib, logger);
                    

                    else
                    {
                        std::cout << "Unknown role. Access denied.\n";
                        logger.log("ERROR", "Login", "Unknown role for: " + username);
                    }
                }
                else
                {
                    std::cout << "Invalid credentials!\n";
                    logger.log("WARNING", "Login", "Invalid password: " + username);
                }
            }
            else
            {
                std::cout << "User not found. Please register first.\n";
            }
        }

        // =====================================================
        //  REGISTRATION SECTION
        // =====================================================
        else if (choice == 2)
        {
            std::string username, email, password, role;

            std::cout << "Enter username: ";
            std::cin.ignore();
            std::getline(std::cin, username);

            std::cout << "Enter email: ";
            std::getline(std::cin, email);

            std::cout << "Enter password: ";
            std::getline(std::cin, password);

            std::cout << "Select Role (Admin / Teacher / Student): ";
            std::getline(std::cin, role);

            fs::path userFile = dataDir / (username + ".txt");
            std::ofstream file(userFile.string());

            /**
             * @brief Write new user data to file.
             */
            if (file.is_open())
            {
                file << auth.generateHash(password) << "\n"
                     << email << "\n"
                     << role << "\n";

                file.close();

                std::cout << "Registration successful! Role: " << role << "\n";
                logger.log("INFO", "Register", "User registered: " + username);
            }
            else
            {
                std::cout << "Error creating user file!\n";
                logger.log("ERROR", "Register",
                           "Unable to create file: " + userFile.string());
            }
        }

        // =====================================================
        //  EXIT OPTION
        // =====================================================
        else if (choice == 3)
        {
            std::cout << "Exiting system. Goodbye!\n";
            logger.log("INFO", "MainMenu", "System exited.");
            break;
        }

        // =====================================================
        //  INVALID CHOICE HANDLER
        // =====================================================
        else
        {
            std::cout << "Invalid choice. Try again.\n";
            logger.log("WARNING", "MainMenu", "Invalid choice entered.");
        }
    }

    return 0;
}
