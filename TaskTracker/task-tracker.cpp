#include "TaskTracker.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <iomanip>          // for formatting the tasks list display
#include <algorithm>

// #include <unistd.h>     // for command line options parsing

std::string formatTime(std::time_t time) {
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&time));
    return std::string(buffer);
}

std::vector<Task> tasks {
    {
        0,
        "task1",
        Status::todo,                       // default to todo
        formatTime( std::time(nullptr) ),
        formatTime( std::time(nullptr) )
    },
    {
        1,
        "task2",
        Status::todo,                       // default to todo
        formatTime( std::time(nullptr) ),
        formatTime( std::time(nullptr) )
    },
    {
        2,
        "task3",
        Status::todo,                       // default to todo
        formatTime( std::time(nullptr) ),
        formatTime( std::time(nullptr) )
    },
};

const int iDWidth (5);
const int descriptionWidth {50};
const int timeWidth {20};
const int statusWidth (12);
const char separator = ' ';

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
                    listTasksByStatus(status);
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid status: \"" << status << "\". Should be either ['done', 'in-progress', or 'todo']\n";
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
    std::cout << "New task with id #" << newTask.id << " added to tasks list.\n";
    listTasks();
}

void updateTask(int id, const std::string& description)
{
    auto found { std::find_if(tasks.begin(), tasks.end(), [id](Task t){
        return t.id == id;
    }) };
    if (found == tasks.end())
    {
        std::cout << "Task with id #" << id << " does not exist.\n";
    }
    else {
        found->description = description;
        std::cout << "Successfully changed description of task #" << id << ".\n";
    }

    listTasks();
}

void deleteTask(int id)
{
    auto found { std::find_if(tasks.begin(), tasks.end(), [id](Task t){
        return t.id == id;
    }) };
    if(found == tasks.end()) 
    {
        std::cout << "Task with id #" << id << " does not exist.\n";
    }
    else 
    {
        tasks.erase(found);
        std::cout << "Task with id(" << id << ") has been deleted..\n";
    }
    listTasks();
}

void markAsDone(int id)
{
    auto found { std::find_if(tasks.begin(), tasks.end(), [id](Task t){
        return t.id == id;
    }) };
    if(found == tasks.end()) 
    {
        std::cout << "Task with id #" << id << " does not exist.\n";
    }
    else
    {
        found->status = Status::done;
    }
}

void markAsInProgress(int id)
{
    auto found { std::find_if(tasks.begin(), tasks.end(), [id](Task t){
        return t.id == id;
    }) };
    if(found == tasks.end()) 
    {
        std::cout << "Task with id #" << id << " does not exist.\n";
    }
    else
    {
        found->status = Status::in_progress;
    }
    listTasks();
}

void listTasks() {

    displayTitleRow();
    for (const auto& task: tasks)
    {
        printTask(task);
    }
}

void listTasksByStatus(Status status)
{
    displayTitleRow();
    switch (status)
    {
        case Status::done:
            for(const auto& task: tasks)
            {
                if(task.status == Status::done)
                    printTask(task);
            }
            break;

        case Status::in_progress:
            for(const auto& task: tasks)
            {
                if(task.status == Status::in_progress)
                    printTask(task);
            }
            break;

        case Status::todo:
            for(const auto& task: tasks)
            {
                if(task.status == Status::todo)
                    printTask(task);
            }
            break;
    }
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

void displayTitleRow() 
{
    std::cout << std::left << std::setw(iDWidth) << std::setfill(separator) << "ID";
    std::cout << std::left << std::setw(descriptionWidth) << std::setfill(separator) << "Description";
    std::cout << std::left << std::setw(statusWidth) << std::setfill(separator) << "Status";
    std::cout << std::left << std::setw(timeWidth) << std::setfill(separator) << "Created At";
    std::cout << std::left << std::setw(timeWidth) << std::setfill(separator) << "Modified At";
    std::cout << std::endl;
}

void printTask(Task task)
{
    std::cout << std::left << std::setw(iDWidth) << std::setfill(separator) << task.id;
    std::cout << std::left << std::setw(descriptionWidth) << std::setfill(separator) << task.description;
    std::cout << std::left << std::setw(statusWidth) << std::setfill(separator) << task.status;
    std::cout << std::left << std::setw(timeWidth) << std::setfill(separator) << task.createdAt;
    std::cout << std::left << std::setw(timeWidth) << std::setfill(separator) << task.modifiedAt;
    std::cout << std::endl;
}
