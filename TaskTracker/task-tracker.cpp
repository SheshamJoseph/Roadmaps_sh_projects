#include <iostream>
#include "TaskTracker.h"
// #include <unistd.h>     // for command line options parsing

enum Status{
    done,
    in_progress,
    todo,
};


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
                std::string status { static_cast<std::string>(argv[2])};
                listTasksByStatus(status); 
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
    std::cout << "Displays help message...\n";
}

void addTask(std::string_view description) {
    std::cout << "New task added: " << description << ".\n";        // just a line to test
}

void updateTask(int id, std::string_view description)
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
