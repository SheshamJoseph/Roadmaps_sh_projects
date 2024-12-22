#ifndef UTILS_H
#define UTILS_H

#include <string>

static size_t writeCallback(void *contents, size_t size, size_t nmemb, std::string *userp);
std::string fetchMovieListData(const std::string& url, const std::string& apiKey);

#endif // UTILS_H
