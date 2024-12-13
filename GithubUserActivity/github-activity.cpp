#include "GithubAPIResponse.h"
#include <curl/curl.h>
#include <iostream>
#include <fstream>


int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Invalid number of arguments...\n";
        std::cout << "Usage: ./github-activity <username>\n";
        return 1;
    }

    std::string username { argv[1] };
    std::string githubResponse = fetchGithubActivity(username);
    std::ofstream outfile { "output.json" };

    if (!outfile)
    {
        std::cerr << "Error in opening file\n";
        return 1;
    }

    outfile << githubResponse;
    outfile.close();

    return 0;
}
