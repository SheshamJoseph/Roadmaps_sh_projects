#include "../include/TMDBResponse.h"
#include "../include/Config.h"
#include "../include/Utils.h"
#include <string>
#include <iostream>
// #include <cstdlib>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

TMDBResponse::TMDBResponse(const std::string& type)
    : m_apiKey {API_KEY}
    , m_type {type}
    {}

void TMDBResponse::getMovieData()
{
    std::string url { MOVIE_LISTS_URL + m_type };
    m_apiResponse = fetchMovieListData(url, m_apiKey);

}

void TMDBResponse::parseResponse()
{
    try{
        auto jsonResponse = json::parse( m_apiResponse );
        for (const auto& movie: jsonResponse["results"])
        {
            std::cout << "Movie Title: " << movie["title"] << ".\n";
            std::cout << "Overview: " << movie["overview"] << ".\n";
            std::cout << "Release Date: " << movie["release_date"] << ".\n";
            std::cout << "Rating: " << movie["vote_average"] << ".\n";
            std::cout << "===========\n\n"; 
        }
    } catch (const std::exception& e)
    {
        std::cerr << "Error in parsing json: " << e.what() << ".\n";
    }
}
