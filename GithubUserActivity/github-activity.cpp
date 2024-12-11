#include <curl/curl.h>
#include <iostream>
#include <fstream>

static size_t writeCallback(void *contents, size_t size, size_t nmemb, std::string *userp) 
{
    ((std::string*)userp)->append((char *)contents, size*nmemb);
    return size * nmemb;
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Invalid number of arguments...\n";
        std::cout << "Usage: ./main <username>\n";
        return 1;
    }
    std::string username {};
    CURL* curl;
    CURLcode code;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) 
    {
        username = static_cast<std::string>(argv[1]);
        std::string url { "https://api.github.com/users/"+ username + "/events" };
        // specify url
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        // add headers
        struct curl_slist *headers = nullptr;
        headers = curl_slist_append(headers, "Accept: application/vnd.github+json");
        headers = curl_slist_append(headers, "User-Agent:Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:133.0) Gecko/20100101 Firefox/133.0");
        headers = curl_slist_append(headers, "Authorization: Token ");
        headers = curl_slist_append(headers, "X-GitHub-Api-Version: 2022-11-28");

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        code = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if(code != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(code));
            return 1;
        }
        // std::cout << readBuffer << std::endl;
        std::ofstream output {"output.json"};
        if (!output)
        {
            std::cerr << "Error in opening file..\n";
            return 1;
        }
        output << readBuffer;
        std::cout << "Successfully written to file..\n";
        output.close();
    }
    return 0;
}
