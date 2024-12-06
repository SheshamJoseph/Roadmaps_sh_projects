#include "TaskTracker.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>

// #include <unistd.h>     // for command line options parsing

std::string formatTime(std::time_t time) {
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&time));
    return std::string(buffer);
}

std::vector<Task> tasks {};


int main(int argc, char* argv[]) 
{
    std::string option {};
    if (argc < 2) {
        displayHelp();
    }
    else {
        option = static_cast<std::string>(argv[1]);

        if (option == "add") { 
            addTask(static_cast<std::string>(argv[2]));
        }
        else if (option == "update") {
            updateTask(
                std::atoi(argv[2]),         // converts value from (char*) to (int)
                static_cast<std::string>(argv[3])
            );
        }
        else if (option == "delete") {
            deleteTask(std::atoi(argv[2]));
        }
        else if (option == "mark-done") {
            markAsDone(std::atoi(argv[2]));
        }
        else if (option == "mark-in-progress") {
            markAsInProgress(std::atoi(argv[2]));
        }
        else if (option == "list"){
            // check if 3 arguements were passed into
            if (argc > 2) { 
                Status status {};
                try {
                    status = stringToStatus(static_cast<std::string>(argv[2]));
                    // Implement logic for listing tasks by status
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid status: " << status << "\n";
                }
            }
            else {
                listTasks();
            }
        }
    }
    return 0;
}

// ======== Helper functions =========
void displayHelp()
{
    std::cout << "Usage:\n";
    std::cout << "  add <description>          - Add a new task\n";
    std::cout << "  update <id> <description>  - Update a task description\n";
    std::cout << "  delete <id>                - Delete a task\n";
    std::cout << "  mark-done <id>             - Mark a task as done\n";
    std::cout << "  mark-in-progress <id>      - Mark a task as in-progress\n";
    std::cout << "  list                       - List all tasks\n";
    std::cout << "  list <status>              - List tasks by status (todo, done, in-progress)\n";
}

void addTask(const std::string& description) {
    Task newTask {
        static_cast<int>(tasks.size()),
        description,
        Status::todo,                       // default to todo
        formatTime( std::time(nullptr) ),
        formatTime( std::time(nullptr) ),   // modified time same as created time
    };
    
    tasks.push_back(newTask);
}

void updateTask(int id, const std::string& description)
{
    std::cout << "Task with id(" << id << ") has had it\'s description updated to \" "<< description << "\".\n";
}

void deleteTask(int id)
{
    std::cout << "Task with id(" << id << ") has been deleted..\n";
}

void markAsDone(int id)
{
    std::cout << "Task with id(" << id << ") has been marked as done..\n";
}

void markAsInProgress(int id)
{
    std::cout << "Task with id(" << id << ") has been marked as in progress..\n";
}

void listTasks() {
    std::cout << "Listing all stored tasks\n";
}

void listTasksByStatus(std::string_view flag)
{
    std::cout << "Listing all stored tasks\n";
}

std::string statusToString(Status status) 
{
    switch (status)
    {
        case Status::done: return "done";
        case Status::in_progress: return "in-progress";
        case Status::todo: return "todo";
    }
    return "unknown";
}

Status stringToStatus(const std::string& status){
    if (status == "done") return done;
    if (status == "in-progress") return in_progress;
    if (status == "todo") return todo;
    throw std::invalid_argument("Invalid status");
}


