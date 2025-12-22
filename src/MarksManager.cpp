#include "../include/MarksManager.h"
#
using namespace std;

MarksManager::MarksManager(string file, string logFile) : logger(logFile)
{
    filename = file;
    loadMarks();
    logger = Logger("logs/events.log");
}

void MarksManager::createExam()
{
    string courseId, examDate;
    int maxMarks;
    cout << "Enter Course ID: ";
    cin >> courseId;
    cout << "Enter Exam Date (DD-MM-YYYY): ";
    cin >> examDate;
    cout << "Enter Max Marks: ";
    cin >> maxMarks;

    ExamRecord exam;
    exam.examDate = examDate;
    exam.maxMarks = maxMarks;

    marksData[courseId].push_back(exam);
    cout << "Exam created for " << courseId << " on " << examDate << endl;

    logger.log("INFO", "MarksManager", "Exam created for " + courseId + " on " + examDate);
    saveMarks();
}

void MarksManager::enterMarks()
{
    string courseId, examDate;
    cout << "Enter Course ID: ";
    cin >> courseId;
    cout << "Enter Exam Date: ";
    cin >> examDate;

    if (marksData.find(courseId) == marksData.end())
    {
        cout << "No exams found for this course.\n";
        return;
    }

    ExamRecord *examPtr = nullptr;
    for (auto &exam : marksData[courseId])
    {
        if (exam.examDate == examDate)
        {
            examPtr = &exam;
            break;
        }
    }
    if (!examPtr)
    {
        cout << "Exam not found.\n";
        return;
    }

    int n;
    cout << "Enter number of students: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string studentId;
        int marks;
        cout << "Student ID: ";
        cin >> studentId;
        cout << "Marks: ";
        cin >> marks;
        examPtr->studentMarks[studentId] = marks;
    }

    cout << "Marks entered successfully!\n";
    logger.log("INFO", "MarksManager", "Marks entered for " + courseId + " on " + examDate);
    saveMarks();
}

void MarksManager::viewMarks()
{
    string courseId;
    cout << "Enter Course ID: ";
    cin >> courseId;

    if (marksData.find(courseId) == marksData.end())
    {
        cout << "No exams for this course.\n";
        return;
    }

    for (auto &exam : marksData[courseId])
    {
        cout << "Exam Date: " << exam.examDate << " | Max Marks: " << exam.maxMarks << endl;
        for (auto &s : exam.studentMarks)
        {
            cout << s.first << " : " << s.second << endl;
        }
        cout << "------------------\n";
    }

    logger.log("INFO", "MarksManager", "Viewed marks for " + courseId);
}

void MarksManager::saveMarks()
{
    ofstream out(filename);
    if (!out.is_open())
    {
        cout << "Cannot open file!\n";
        return;
    }

    for (auto &c : marksData)
    {
        string courseId = c.first;
        for (auto &exam : c.second)
        {
            out << courseId << " " << exam.examDate << " " << exam.maxMarks;
            for (auto &s : exam.studentMarks)
                out << " " << s.first << ":" << s.second;
            out << endl;
        }
    }
    out.close();
}

void MarksManager::loadMarks()
{
    ifstream in(filename);
    if (!in.is_open())
        return;

    marksData.clear();
    string line;
    while (getline(in, line))
    {
        if (line.empty())
            continue;
        istringstream ss(line);
        string courseId, examDate, token;
        int maxMarks;
        ss >> courseId >> examDate >> maxMarks;
        ExamRecord exam;
        exam.examDate = examDate;
        exam.maxMarks = maxMarks;
        while (ss >> token)
        {
            size_t pos = token.find(':');
            string studentId = token.substr(0, pos);
            int marks = stoi(token.substr(pos + 1));
            exam.studentMarks[studentId] = marks;
        }
        marksData[courseId].push_back(exam);
    }
    in.close();
}
// view marks for a specific student

void MarksManager::viewStudentMarks()
{
    ifstream file("marks.txt");
    string line;

    cout << "\n--- MARKS RECORDS ---\n";

    while (getline(file, line))
    {
        cout << line << endl;
    }

    file.close();
}
