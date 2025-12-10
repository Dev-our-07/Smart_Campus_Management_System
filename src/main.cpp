/**
 * @file main.cpp
 * @brief Implementation of the main menu for the Smart Campus Management System.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "../include/auth.h" ///< Local header file for authentication functionality.

#if defined(__cpp_lib_filesystem)   
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

//not using "using namespace std;" to avoid namespace pollution

// Resolve and ensure the data directory exists regardless of whether the app
// is run from the project root or the src folder.
fs::path resolveDataDir() {
    fs::path cwdData("data");
    fs::path parentData = fs::path("..") / "data";

    if (fs::exists(parentData)) {
        return parentData;
    }

    if (fs::exists(cwdData)) {
        return cwdData;
    }

    std::error_code ec;
    if (fs::create_directories(parentData, ec)) {
        return parentData;
    }

    ec.clear();
    if (fs::create_directories(cwdData, ec)) {
        return cwdData;
    }

    return parentData; // Fallback; caller will handle open failures.
}

void dashboard(const std::string& username) {
    std::cout << "\n--- Dashboard ---\n";
    std::cout << "Welcome, " << username << "!" << std::endl;
    std::cout << "(Stub) Add dashboard features here." << std::endl;
}

void registerUser(Auth& auth) {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    std::string hashedPassword = auth.generateHash(password);
    const fs::path dataDir = resolveDataDir();
    const fs::path userFile = dataDir / (username + ".txt");

    std::ofstream file(userFile.string());
    if (file.is_open()) {
        file << hashedPassword;
        file.close();
        std::cout << "Registration successful!" << std::endl;
        std::cout << "Username: " << username << "\nStored hash: " << hashedPassword << std::endl;
        std::cout << "Saved at: " << userFile.string() << std::endl;
    } else {
        std::cout << "Error creating user file at " << userFile.string() << std::endl;
    }
}

bool loginUser(Auth& auth, std::string& outUsername, std::string& outStoredHash) {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    const fs::path dataDir = resolveDataDir();
    const fs::path userFile = dataDir / (username + ".txt");

    std::ifstream file(userFile.string());
    if (file.is_open()) {
        std::string storedHash;
        file >> storedHash;
        file.close();

        if (auth.verifyPassword(password, storedHash)) {
            outUsername = username;
            outStoredHash = storedHash;
            return true;
        }
    } else {
        std::cout << "User not found at path: " << userFile.string() << std::endl;
    }

    return false;
}

/**
 * @brief Main entry point of the program.
 * 
 * @return int Exit status of the program.
 */
int main(){
    Auth auth; ///< Authentication object for testing.

    while (true) {
        // 1. Welcome Message
        std::cout<<"==============O(n v n)O==============="<<std::endl<<std::endl;

        std::cout<<"Welcome to Smart Campus Management System"<<std::endl;
        std::cout<<"Kindly read the instructions and choose your option to interact further with the system."<<std::endl<<std::endl;

        // Break line
        std::cout<<"==============O(n v n)O==============="<<std::endl;

        // 2. Main Menu
        std::cout<<std::endl<<"M A I N     M E N U"<<std::endl<<std::endl;

        std::cout<<"Select the corresponding number to access the feature:"<<std::endl;
        std::cout<<"1. Register"<<std::endl;
        std::cout<<"2. Login"<<std::endl;
        std::cout<<"3. Exit"<<std::endl;
        int choice;
        std::cout<<std::endl<<"Enter your choice: ";
        std::cin>>choice;
        std::cin.ignore(); // Clear the newline left in the input buffer

        /**
         * @brief Switch-case structure to handle user choice.
         */
        switch(choice)
        {
            case 1:
                registerUser(auth);
                break;

            case 2: {
                std::string loggedUser;
                std::string storedHash;
                if (loginUser(auth, loggedUser, storedHash)) {
                    std::cout << "Login successful!" << std::endl;
                    std::cout << "Username: " << loggedUser << "\nStored hash: " << storedHash << std::endl;
                    dashboard(loggedUser);
                } else {
                    std::cout << "Invalid credentials. Redirecting to registration..." << std::endl;
                    registerUser(auth);
                }
                break;
            }

            case 3:
                std::cout<<std::endl<<"Exiting the system. Goodbye!"<<std::endl;
                return 0;

            default:
                std::cout<<std::endl<<"Invalid choice. Please restart the program and select a valid option."<<std::endl; 
                // Handles invalid input and breaks out of the switch-case
        }
    }

    return 0;
}