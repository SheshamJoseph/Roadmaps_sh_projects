#include <iostream>
#include <getopt.h>
#include <iomanip>

static struct option long_options[] = {
    {"help", no_argument, 0, 'h'},
    {"type", no_argument, 0, 't'},
    {0,0,0,0}
};

int main(int argc, char* argv[])
{
    int option_index = 0;
    int option = getopt_long(argc, argv, "ht:", long_options, &option_index);

    switch (option) {
    case 'h': // --help or -h
        std::cout << "Usage: ./main [option].\n";
        std::cout << "Options:\n";
        std::cout << "  -h, --help                  - displays help.\n";
        std::cout << "  -t, --type <type>     - gets movie list by type.\n";
        return 0;
    case 't': // Unknown option
        std::cout << "Movie type entered: " << optarg << ".\n";
        break;
    default:
        std::cerr << "Invalid option entered. Try \"./main --help\" for more info on usage.\n";
        return 1;
    }
    return 0;


}
