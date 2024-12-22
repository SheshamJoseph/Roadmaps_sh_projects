#include "../include/TMDBResponse.h"
#include <iostream>
#include <getopt.h>
#include <iomanip>

static struct option long_options[] = {
    {"help", no_argument, 0, 'h'},
    {"type", no_argument, 0, 't'},
    {0,0,0,0}
};

// Transform user argument into the required format for API request
void parseType(std::string& type) {
    if (type == "playing")
        type = "now_playing";
    else if (type == "top")
        type = "top_rated";
    else if (type == "popular" || type == "upcoming")
        ; // Valid types, no transformation needed
    else {
        std::cerr << "Error: Invalid type entered. Valid types are: playing, popular, top, upcoming.\n";
        exit(1);
    }
}

void makeRequest(std::string movieType)
{
    parseType(movieType);
    TMDBResponse response (movieType);
    response.getMovieData();
    response.parseResponse();
}

int main(int argc, char* argv[])
{
    int option_index = 0;
    int option;
    // Parse command-line options
    while ((option = getopt_long(argc, argv, "ht:", long_options, &option_index)) != -1) {
        switch (option) {
        case 'h': // --help or -h
            std::cout << "Usage: ./main [option]\n";
            std::cout << "Options:\n";
            std::cout << "  -h, --help                     - displays help.\n";
            std::cout << "  -t <type> or --type=<type>     - gets movie list by type [playing, popular, top, upcoming].\n";
            std::cout << "    Example: ./main --type=playing\n";
            return 0;

        case 't': // --type or -t
            if (optarg) {
                std::string userInput(optarg); // Convert optarg to std::string
                makeRequest(userInput);
            } else {
                std::cerr << "Error: Missing argument for --type option.\n";
                return 1;
            }
            break;

        default: // Invalid option
            std::cerr << "Error: Invalid option entered. Try \"./main --help\" for usage information.\n";
            return 1;
        }
    }
    return 0;


}
