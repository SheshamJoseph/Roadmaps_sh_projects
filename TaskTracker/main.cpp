#include <iostream>
#include <unistd.h>     // for command line options parsing

void displayHelp();
void parseArgumentList(int length, char* args[]);
bool writeTask();
bool readTask();
bool deleteTask();
void listTasks();

int main(int argc, char* argv[])
{

    if(argc < 2)
    {
        displayHelp();
    }
    else{
        parseArgumentList(argc, argv);
    }

    return 0;
}
