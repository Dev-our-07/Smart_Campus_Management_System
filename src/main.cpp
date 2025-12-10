#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "../include/auth.h"
#include "../include/CourseManager.h"
#include "../include/course.h"
#include "../include/Logger.h"

#if defined(__cpp_lib_filesystem)
namespace fs = std::filesystem; ///< Use standard filesystem if available
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem; ///< Fallback to experimental filesystem
#endif

/**
 * @brief Main function for the Smart Campus Management System
 *
 * Handles user authentication (login/register) and course management menu.

 *
 * @return int Exit status of the program
 */
int main()
{
    /// Initialize the logger to track all events in the system
    Logger logger("logs/events.log");

    /// Authentication object for password hashing and verification
    Auth auth;

    /// CourseManager object to manage courses
    CourseManager cm("courses.txt");

    /// Resolve and create data directory for user files
    fs::path cwdData("data");                      ///< Current working directory data path
    fs::path parentData = fs::path("..") / "data"; ///< Parent directory data path
    fs::path dataDir;

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
            dataDir = parentData; ///< Fallback if creation fails
    }

    // ================= Main Menu Loop =================
    while (true)
    {
        std::cout << "\n==============O(n v n)O===============" << std::endl;
        std::cout << "Welcome to Smart Campus Management System" << std::endl;
        std::cout << "1. Login" << std::endl;
        std::cout << "2. Register" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        // ---------------- LOGIN SECTION ----------------
        if (choice == 1)
        {
            std::string username, password;
            std::cout << "Enter username: ";
            std::cin >> username;
            std::cout << "Enter password: ";
            std::cin >> password;

            fs::path userFile = dataDir / (username + ".txt");
            std::ifstream file(userFile.string());
            if (file.is_open())
            {
                std::string storedHash;
                file >> storedHash;
                file.close();

                /// Verify password
                if (auth.verifyPassword(password, storedHash))
                {
                    std::cout << "Login successful! Welcome, " << username << std::endl;
                    logger.log("INFO", "Login", "User logged in: " + username);

                    // =============== COURSE MANAGEMENT MENU ===============
                    while (true)
                    {
                        std::cout << "\n====== COURSE MANAGEMENT MENU ======" << std::endl;
                        std::cout << "1. Add Course" << std::endl;
                        std::cout << "2. View All Courses" << std::endl;
                        std::cout << "3. Enroll Student" << std::endl;
                        std::cout << "4. Drop Student" << std::endl;
                        std::cout << "5. Delete Course" << std::endl;
                        std::cout << "6. Logout / Back to Main Menu" << std::endl;
                        std::cout << "Enter your choice: ";

                        int c_choice;
                        std::cin >> c_choice;
                        if (c_choice == 6)
                            break; ///< Logout to main menu

                        // ---------- Course Menu Options ----------
                        switch (c_choice)
                        {
                        case 1:
                        { ///< Add a new course
                            std::string id, title;
                            int credits, capacity;
                            std::cout << "Enter Course ID: ";
                            std::cin >> id;
                            std::cout << "Enter Course Title: ";
                            std::cin.ignore();
                            std::getline(std::cin, title);
                            std::cout << "Enter Credits: ";
                            std::cin >> credits;
                            std::cout << "Enter Capacity: ";
                            std::cin >> capacity;
                            Course c(title, id, capacity, credits);
                            cm.addCourse(c);
                            break;
                        }
                        case 2: ///< View all courses
                            cm.printAllCourses();
                            break;
                        case 3:
                        { ///< Enroll student in a course
                            std::string id;
                            std::cout << "Enter Course ID to enroll student: ";
                            std::cin >> id;
                            cm.enrollStudent(id);
                            break;
                        }
                        case 4:
                        { ///< Drop student from course
                            std::string id;
                            std::cout << "Enter Course ID to drop student: ";
                            std::cin >> id;
                            cm.dropStudent(id);
                            break;
                        }
                        case 5:
                        { ///< Delete a course
                            std::string id;
                            std::cout << "Enter Course ID to delete: ";
                            std::cin >> id;
                            cm.deleteCourse(id);
                            break;
                        }
                        default: ///< Invalid option
                            std::cout << "Invalid choice!" << std::endl;
                        }
                    }
                }
                else
                { ///< Wrong password
                    std::cout << "Invalid credentials!" << std::endl;
                    logger.log("WARNING", "Login", "Failed login attempt for: " + username);
                }
            }
            else
            { ///< User file not found
                std::cout << "User not found. Please register first." << std::endl;
            }
        }

        // ---------------- REGISTRATION SECTION ----------------
        else if (choice == 2)
        {
            std::string username, password;
            std::cout << "Enter username: ";
            std::cin >> username;
            std::cout << "Enter password: ";
            std::cin >> password;

            fs::path userFile = dataDir / (username + ".txt");
            std::ofstream file(userFile.string());
            if (file.is_open())
            {
                std::string hashedPassword = auth.generateHash(password);
                file << hashedPassword;
                file.close();
                std::cout << "Registration successful!" << std::endl;
                logger.log("INFO", "Register", "User registered: " + username);
            }
            else
            { ///< Error creating user file
                std::cout << "Error creating user file!" << std::endl;
                logger.log("ERROR", "Register", "Failed to create user file: " + userFile.string());
            }
        }

        // ---------------- EXIT ----------------
        else if (choice == 3)
        {
            std::cout << "Exiting system. Goodbye!" << std::endl;
            logger.log("INFO", "MainMenu", "System exited by user.");
            break;
        }

        // ---------------- INVALID CHOICE ----------------
        else
        {
            std::cout << "Invalid choice. Try again." << std::endl;
            logger.log("WARNING", "MainMenu", "Invalid menu choice entered.");
        }
    }

    return 0;
}
