#ifndef JSON_H
#define JSON_H

#include "TaskTracker.h"
#include <vector>

std::string taskToJson(const Task& task);
Task jsonToTask(const std::string& json);
void saveTasksToFile(const std::vector<Task>& tasks, const std::string& file);
std::vector<Task> readTasksFromFile(const std::string& file);

#endif  // JSON_H
