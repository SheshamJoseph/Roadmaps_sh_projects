#include "GithubAPIResponse.h"
#include <curl/curl.h>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Callback function to write data to a string
static size_t writeCallback(void *contents, size_t size, size_t nmemb, std::string *userp) 
{
    userp->append((char *)contents, size * nmemb);
    return size * nmemb;
}

std::string fetchGithubActivity(std::string userName)
{
    CURL* curl;
    CURLcode response;
    std::string readBuffer;

    curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize CURL.\n";
        return "";
    }

    std::string url = "https://api.github.com/users/" + userName + "/events";
    struct curl_slist *headers = nullptr;

    headers = curl_slist_append(headers, "User-Agent:Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:133.0) Gecko/20100101 Firefox/133.0");

    // Set CURL options
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    response = curl_easy_perform(curl);

    if (response != CURLE_OK) {
        std::cerr << "CURL request failed: " << curl_easy_strerror(response) << "\n";
        readBuffer = "";
    } else {
        // Check HTTP response code
        long http_code = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        if (http_code != 200) {
            std::cerr << "Failed to fetch data. HTTP Code: " << http_code << "\n";
            readBuffer = "";
        }
    }

    // Clean up
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);

    return readBuffer;
}


void displayActivities(const std::string& userJson)
{
    try
    {
        auto events = json::parse(userJson);
        for(const auto& event: events)
        {
            parseJsonEvent(event);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

void parseJsonEvent(const json& event)
{
    try 
    {
        std::string eventType = event["type"];
        std::string repoName = event["repo"]["name"];
        if (eventType == "CommitCommentEvent")
        {
            std::cout << "Made a commit comment on " << repoName << ".\n";
        }
        else if (eventType == "CreateEvent")
        {
            std::cout << "Created a new repo " << repoName << ".\n";
        }
        else if (eventType == "PushEvent")
        {
            int commitCount = event["payload"]["size"];
            std::cout << "Pushed " << commitCount << " commits to " << repoName << ".\n";
        }
        else if (eventType == "DeleteEvent")
        {
            std::string refType = event["payload"]["ref_type"];
            std::string ref = event["payload"]["ref"];
            std::cout << "Deleted " << refType << " " << ref << " in " << repoName << ".\n";
        }
        else if (eventType == "IssuesEvent")
        {
            std::string action = event["payload"]["action"];
            std::cout << "Issue " << action << " in " << repoName << ".\n";
        }
        else if (eventType == "PullRequestEvent")
        {
            std::string action = event["payload"]["action"];
            std::cout << "Pull request " << action << " in " << repoName << ".\n";
        }
        else
        {
            std::cout << "Unhandled event type: " << eventType << ".\n";
        }
    } 
    catch (const json::exception& e)
    {
        std::cerr << "Error parsing event: " << e.what();
    }
}
