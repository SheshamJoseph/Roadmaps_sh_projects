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
    if (!githubResponse.empty())
    {
        displayActivities(githubResponse);
    }
    // else 
    // {
    //     std::cerr << "Error in getting response.\n";
    // }

    return 0;
}
