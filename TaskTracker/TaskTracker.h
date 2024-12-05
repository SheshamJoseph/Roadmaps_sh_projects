#ifndef TASK_TRACKER_H
#define TASK_TRACKER_H

#include <ctime>

struct Task {
    int id {};
    std::string description {};
    std::string status {};
    std::time_t createdAt {};
    std::time_t modifiedAt {};
};

void displayHelp();

void addTask(std::string_view description);
void updateTask(int id, std::string_view description);
void deleteTask(int id);

void markAsDone(int id);
void markAsInProgress(int id);

void listTasks();
void listTasksByStatus(std::string_view flag="all");

#endif // TASK_TRACKER_H
