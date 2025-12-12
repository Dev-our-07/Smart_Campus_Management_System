#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "../include/CourseManager.h"
void showAdminDashboard(CourseManager& cm,Logger& logger);
void showStudentDashboard(Logger& logger);
void showTeacherDashboard(Logger& logger);

#include <string>

/** @brief show the dashboard of the Admin */
 void showAdminDashboard();

 /** @brief show the dashboard of the student */
    void showStudentDashboard();

/** @brief show the dashboard of the Teacher  */
    void showTeacherDashboard();

#endif // DASHBOARD_H