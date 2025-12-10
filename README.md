# Smart_Campus_Management_System
## Overview
This project provides a campus management system with various features to manage student, faculty, and staff information. It includes modules for authentication, student management, faculty management, course management, and more.

## Modules
   ***Assignment 1***
1.  **Module A: Project Setup & Coding Structure**
    *   Project directory created with: src/, include/, data/, logs/, tests/, build/
    *   README.md and Makefile/CMakeLists.txt created
    *   Basic menu in main.cpp using cin/cout
    *   Code documented using comments
      
2.  **Module B: Logger Subsystem**
    *   Logger class implemented
    *   Logs written with timestamp + severity levels
    *   Log file inside logs/scms.log
    *   System boot, shutdown & menu actions logged
      
3.  **Module C: Core Class Hierarchy**
    *   Person base class
    *   Derived classes: User, Student, Teacher, Admin
    *   Constructors, destructors, virtual functions implemented
    *   Polymorphic printProfile()
    *   Encapsulation enforced using private/protected members
    *   
4.  **Module D: Authentication System**
    *   AuthManager implemented
    *   User registration, login, logout
    *   Password hashing
    *   File storage using fstream (binary or text)
    *   Login attempts logged
    *   Exceptions handled
      
5.  **Module E: Course & Enrollment Module**
    *   Course + CourseManager classes
    *   Add, update, delete course
    *   Enroll & drop students
    *   Course persistence using file handling
    *   All actions logged

***Assignment 2***
To be added soon...

## Features
*   User authentication and authorization
*   Student and faculty management
*   Course management and enrollment
*   Logging and error handling
*   Secure password storage and verification

## Requirements
*   C++ compiler (g++)
*   OpenSSL library for password hashing

## Usage
1.  Run the executable and select an option from the main menu.
2.  Follow the prompts to navigate through the system.
3.  Use the various modules to manage campus information.

## Creators/Collaborators
*   Name      :   Roll no
*   Bhoomija Sharma: 241103039
*   Shagun Padha: 241103055
*   Devjeet Kour: 241103060
*   Divya Kumari: 241103064

## Notes
*   This is a comprehensive system and should be used as a starting point for further development.
*   Additional security measures should be implemented for production environments.
*   Data is stored in files, consider using a database for larger-scale applications.
