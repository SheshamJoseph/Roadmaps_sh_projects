#ifndef GITHUB_API_RESPONSE
#define GITHUB_API_RESPONSE

#include <string>

std::string fetchGithubActivity(std::string userName);
void displayActivities(const std::string& userJson);


#endif // GITHUB_API_RESPONSE
