#ifndef ATTENDANCEMANAGER_H
#define ATTENDANCEMANAGER_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include "Logger.h"
using namespace std;

struct AttendanceRecord
{
    string date;
    map<string, bool> studentStatus; // studentID -> present/absent
};

class AttendanceManager
{
private:
    map<string, vector<AttendanceRecord>> attendanceData; // courseID -> list of attendance records
    string filename;
    Logger logger;
    

public:
    AttendanceManager(string file = "attendance.txt");

    void markAttendance();       // Mark attendance for a course
    void viewAttendanceByDate(); // View attendance for a course for a date range
    void loadAttendance();       // Load attendance from file
    void saveAttendance();       // Save attendance to file
    void viewAttendanceForStudent(); // View attendance for a specific student
};

#endif
