cmake_minimum_required(VERSION 3.10)
project(TMDB_CLI_Tool)

set(CMAKE_CXX_STANDARD 17)

#include directory for header files
include_directories(include)

# Add main source files
add_executable(TMDB_CLI_Tool
    src/main.cpp
    src/TMDBResponse.cpp
    src/Utils.cpp
)

# Include directories
target_include_directories(TMDB_CLI_Tool PRIVATE include)

# Link libraries (curl, etc.)
find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)
target_link_libraries(
    TMDB_CLI_Tool 
    CURL::libcurl
    nlohmann_json::nlohmann_json
)
