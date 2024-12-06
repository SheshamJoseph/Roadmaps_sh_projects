#ifndef TASK_TRACKER_H
#define TASK_TRACKER_H

#include <string>
#include <ctime>

enum Status{
    done,
    in_progress,
    todo,
};

struct Task {
    int id {};
    std::string description {};
    Status status {};    
    std::string createdAt {};
    std::string modifiedAt {};
};

void displayHelp();

void addTask(const std::string& description);
void updateTask(int id, const std::string& description);
void deleteTask(int id);

void markAsDone(int id);
void markAsInProgress(int id);

void listTasks();
void listTasksByStatus(Status status);

std::string formatTime(std::time_t time);
std::string statusToString(Status status);
Status stringToStatus(const std::string& status);

#endif // TASK_TRACKER_H
