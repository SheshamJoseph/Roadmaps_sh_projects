#include "../include/Utils.h"
#include <string>
#include <iostream>
#include <curl/curl.h>

static size_t writeCallback(void *contents, size_t size, size_t nmemb, std::string *userp)
{
    userp->append((char *)contents, size * nmemb);
    return size * nmemb;
}

std::string fetchMovieListData(const std::string& url, const std::string& apiKey)
{
    CURL *handle = curl_easy_init();
    CURLcode response;
    std::string buffer;

    if(!handle)
    {
        std::cerr << "Failed to initialize curl.\n";
        return "";
    }

    curl_easy_setopt(handle, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &buffer);
    curl_easy_setopt(handle, CURLOPT_URL, url.c_str());

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "accept: application/json");
    headers = curl_slist_append(headers, ("Authorization: Bearer " + apiKey).c_str());
    curl_easy_setopt(handle, CURLOPT_HTTPHEADER, headers);

    response = curl_easy_perform(handle);
    if (response != CURLE_OK)
    {
        std::cerr << "Curl request failed: " << curl_easy_strerror(response) << ".\n";
        buffer = "";
    }
    else
    {
        long http_code {0};
        curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &http_code);
        if(http_code != 200)
        {
            std::cerr << "Failed to fetch data. HTP code: " << http_code << ".\n";
            buffer = "";
        }
    }

    // clean up
    curl_easy_cleanup(handle);
    curl_slist_free_all(headers);
    return buffer;
}
