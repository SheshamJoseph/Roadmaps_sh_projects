#ifndef GITHUB_API_RESPONSE
#define GITHUB_API_RESPONSE

#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

std::string fetchGithubActivity(std::string userName);
void displayActivities(const std::string& userJson);
void parseJsonEvent(const json& event);


#endif // GITHUB_API_RESPONSE
