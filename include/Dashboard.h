#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "../include/CourseManager.h"
#include "../include/AttendanceManager.h"
#include "../include/MarksManager.h"
#include "../include/LibraryManager.h"
#include "../include/logger.h"
void showAdminDashboard(CourseManager& cm,Logger& logger);
// dashboard.h
void showTeacherDashboard(AttendanceManager &am, MarksManager &mm, LibraryManager &lib, Logger &logger);
void showStudentDashboard(AttendanceManager &am, MarksManager &mm, LibraryManager &lib, Logger &logger);

#include <string>

/** @brief show the dashboard of the Admin */
 void showAdminDashboard();

 /** @brief show the dashboard of the student */
    void showStudentDashboard();

/** @brief show the dashboard of the Teacher  */
    void showTeacherDashboard();

#endif // DASHBOARD_H