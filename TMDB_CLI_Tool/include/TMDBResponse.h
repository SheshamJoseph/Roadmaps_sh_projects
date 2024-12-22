#ifndef TMDB_RESPONSE
#define TMDB_RESPONSE

#include <string>
class TMDBResponse
{
private:
    std::string m_apiKey {};
    std::string m_apiResponse {};
    std::string m_type {};
public:
    TMDBResponse(const std::string& type);
    void parseResponse(const std::string& response);
    void getMovieData();
};

#endif // TMDB_RESPONSE
