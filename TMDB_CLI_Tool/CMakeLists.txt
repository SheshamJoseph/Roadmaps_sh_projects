cmake_minimum_required(VERSION 3.10)
project(TMDB_CLI_Tool)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set default build type to Debug
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

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

# Add debug flags explicitly if needed
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
endif()
