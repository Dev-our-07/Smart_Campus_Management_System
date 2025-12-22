#ifndef MARKSMANAGER_H
#define MARKSMANAGER_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include "Logger.h"
using namespace std;

struct ExamRecord
{
    string examDate;
    int maxMarks;
    map<string, int> studentMarks; // studentID -> marks
};

class MarksManager
{
private:
    map<string, vector<ExamRecord>> marksData; // courseID -> exams
    string filename;
    Logger logger;

public:
    MarksManager(string file = "marks.txt", string logFile = "events.log");

    void createExam(); // Create new exam
    void enterMarks(); // Enter marks for students
    void viewMarks();  // View marks for a course
    void saveMarks();  // Save to file
    void loadMarks();  // Load from file
    void viewStudentMarks();
};

#endif
