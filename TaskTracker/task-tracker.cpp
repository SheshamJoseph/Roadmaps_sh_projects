#include "TaskTracker.h"
#include "Json.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <iomanip>          // for formatting the tasks list display
#include <algorithm>
#include <fstream>

// #include <unistd.h>     // for command line options parsing

std::string formatTime(std::time_t time) {
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&time));
    return std::string(buffer);
}


const int iDWidth (5);
const int descriptionWidth {50};
const int timeWidth {20};
const int statusWidth (12);
const char separator = ' ';
std::string file {"tasks.json"};

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
    std::vector<Task> tasks { readTasksFromFile(file) };
    int newId {};
    if (tasks.empty()){
        newId = 0;
    }
    else {
        newId = tasks[tasks.size()-1].id + 1;
    }
    Task newTask {
        newId,
        description,
        Status::todo,                       // default to todo
        formatTime( std::time(nullptr) ),
        formatTime( std::time(nullptr) ),   // modified time same as created time
    };
    
    tasks.push_back(newTask);
    std::cout << "New task with id #" << newTask.id << " added to tasks list.\n";
    saveTasksToFile(tasks, file);
    // listTasks();
}

void updateTask(int id, const std::string& description)
{
    std::vector<Task> tasks { readTasksFromFile(file) };
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
    saveTasksToFile(tasks, file);
    // listTasks();
}

void deleteTask(int id)
{
    std::vector<Task> tasks { readTasksFromFile(file) };
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
    saveTasksToFile(tasks, file);
    // listTasks();
}

void markAsDone(int id)
{
    std::vector<Task> tasks { readTasksFromFile(file) };
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
    saveTasksToFile(tasks, "tasks.json");
}

void markAsInProgress(int id)
{
    std::vector<Task> tasks { readTasksFromFile(file) };
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
    saveTasksToFile(tasks, file);
    // listTasks();
}

void listTasks() {

    std::vector<Task> tasks { readTasksFromFile("tasks.json") };
    displayTitleRow();
    for (const auto& task: tasks)
    {
        printTask(task);
    }
}

void listTasksByStatus(Status status)
{
    std::vector<Task> tasks { readTasksFromFile("tasks.json") };
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


std::string taskToJson(const Task& task)
{
    std::string json = "{";
    json += "\"id\": \"" + std::to_string(task.id) + "\", ";
    json += "\"description\": \"" + task.description + "\", ";
    json += "\"status\": \"" + statusToString(task.status) + "\", ";
    json += "\"createdAt\": \"" + task.createdAt + "\", ";
    json += "\"modifiedAt\": \"" + task.modifiedAt + "\",";
    json += "}";

    return json;
}

Task jsonToTask(const std::string& json)
{
    Task task {};

    auto findValue = [&](const std::string& key) {
        size_t start = json.find("\"" + key + "\":") + key.length() + 4;
        size_t end = json.find(",", start);
        if (end == std::string::npos) {
            end = json.find("}", start);
        }
        return json.substr(start, end - start);
    };

    task.id = std::stoi(findValue("id").substr(1, findValue("id").size()-2));
    task.description = findValue("description").substr(1, findValue("description").size() - 2); // Remove quotes
    std::string temp = findValue("status").substr(1, findValue("status").size() - 2);               // Remove quotes
    task.status = stringToStatus(temp);     // temp holds string value of 'status' before being converted to type 'Status'
    task.createdAt = findValue("createdAt").substr(1, findValue("createdAt").size() - 2);
    task.modifiedAt = findValue("modifiedAt").substr(1, findValue("modifiedAt").size() - 2);

    return task;
}

std::vector<Task> readTasksFromFile(const std::string& file)
{
    std::ifstream inFile {file};
    if(!inFile)
    {
        std::cerr << "Error!!! Can't open file for reading\n";
        return {};
    } 

    std::vector<Task> tasks {};
    std::string line {};
    while(std::getline(inFile, line))
    {
        if(line.find("{") != std::string::npos)
        {
            std::string taskJson {};
            do{
                taskJson += line;
            } while (line.find("}") == std::string::npos && std::getline(inFile, line));

            tasks.push_back(jsonToTask(taskJson));
        }
    }
    inFile.close();
    return tasks;
}

void saveTasksToFile(const std::vector<Task>& tasks, const std::string& file)
{
    std::ofstream outFile{file};
    if(!outFile)
    {
        std::cerr << "Error!!! Can't open file for writing\n";
        return;
    } 

    outFile << "[\n";
    for (size_t i=0; i < tasks.size(); ++i)
    {
        outFile << taskToJson(tasks[i]);
        if (i != (tasks.size()-1)) {
            outFile << ",";
        }
        outFile << "\n";
    }
    outFile << "]\n";
    outFile.close();

}
