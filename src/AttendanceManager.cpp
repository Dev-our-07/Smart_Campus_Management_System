#include "../include/AttendanceManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// ---------------- Constructor ----------------
AttendanceManager::AttendanceManager(string file)
{
    filename = file;
    logger = Logger("logs/events.log");
    loadAttendance();
}

// ---------------- Mark Attendance ----------------
void AttendanceManager::markAttendance()
{
    string courseId, studentId, date;
    char status;

    cout << "Enter Course ID: ";
    cin >> courseId;
    cout << "Enter Date (YYYY-MM-DD): ";
    cin >> date;

    AttendanceRecord record;
    record.date = date;

    while (true)
    {
        cout << "Enter Student ID (or '0' to stop): ";
        cin >> studentId;
        if (studentId == "0")
            break;

        cout << "Is student present? (y/n): ";
        cin >> status;
        record.studentStatus[studentId] = (status == 'y' || status == 'Y');
    }

    attendanceData[courseId].push_back(record);
    saveAttendance();
    logger.log("INFO", "AttendanceManager", "Attendance marked for course: " + courseId + " on " + date);
    cout << "Attendance marked successfully!\n";
}

// ---------------- View Attendance by Date ----------------
void AttendanceManager::viewAttendanceByDate()
{
    string courseId, startDate, endDate;
    cout << "Enter Course ID: ";
    cin >> courseId;
    cout << "Enter Start Date (YYYY-MM-DD): ";
    cin >> startDate;
    cout << "Enter End Date (YYYY-MM-DD): ";
    cin >> endDate;

    if (attendanceData.find(courseId) == attendanceData.end())
    {
        cout << "No attendance records for this course.\n";
        return;
    }

    for (auto &record : attendanceData[courseId])
    {
        if (record.date >= startDate && record.date <= endDate)
        {
            cout << "Date: " << record.date << "\n";
            for (auto &s : record.studentStatus)
                cout << "StudentID: " << s.first << " - " << (s.second ? "Present" : "Absent") << "\n";
            cout << "-----------------------\n";
        }
    }

    logger.log("INFO", "AttendanceManager", "Viewed attendance for course: " + courseId);
}

// ---------------- View Attendance for Student ----------------
void AttendanceManager::viewAttendanceForStudent()
{
    string studentId;
    cout << "Enter Student ID: ";
    cin >> studentId;

    for (auto &course : attendanceData)
    {
        cout << "Course: " << course.first << "\n";
        for (auto &record : course.second)
        {
            auto it = record.studentStatus.find(studentId);
            if (it != record.studentStatus.end())
            {
                cout << "Date: " << record.date << " - " << (it->second ? "Present" : "Absent") << "\n";
            }
        }
        cout << "----------------------\n";
    }

    logger.log("INFO", "AttendanceManager", "Viewed attendance for student: " + studentId);
}

// ---------------- Load Attendance from File ----------------
void AttendanceManager::loadAttendance()
{
    ifstream in(filename);
    if (!in.is_open())
        return;

    attendanceData.clear();
    string line;

    while (getline(in, line))
    {
        stringstream ss(line);
        string courseId, date, studentId;
        bool status;
        ss >> courseId >> date;

        AttendanceRecord record;
        record.date = date;

        while (ss >> studentId >> status)
        {
            record.studentStatus[studentId] = status;
        }

        attendanceData[courseId].push_back(record);
    }

    in.close();
}

// ---------------- Save Attendance to File ----------------
void AttendanceManager::saveAttendance()
{
    ofstream out(filename);
    if (!out.is_open())
        return;

    for (auto &course : attendanceData)
    {
        for (auto &record : course.second)
        {
            out << course.first << " " << record.date << " ";
            for (auto &s : record.studentStatus)
            {
                out << s.first << " " << s.second << " ";
            }
            out << "\n";
        }
    }
}
