# TMDB CLI App

The TMDB CLI App is a simple app that fetches data from The Movie Database (TMSB) and displays it in the terminal. It fetches data about 4 movie lists, "Popular", "Top Rated", "Now Playing" and "Upcoming". [Link](https://roadmap.sh/projects/tmdb-cli) to project page.

### To run the program
1. Clone the repository
<pre>
git clone 
cd TMDB_CLI_App
</pre>
2. Create you own Config.h file to store your own TMDB API key
<pre>
cd include
touch Config.h
</pre>
A sample of how the `Config.h` file should look is:
<pre>
<code>
#ifndef CONFIG_H
#define CONFIG_H

// API Configuration
constexpr const char* API_KEY = "your api key here";
constexpr const char* MOVIE_LISTS_URL = "https://api.themoviedb.org/3/movie/";

#endif // CONFIG_H
</code>
</pre>
3. Build the project
<pre>
# Requirements for this project
# - CMake (version 3.10)
# - libcurl
# - nlohmann_json library

$ mkdir build
$ cd build
$ cmake ..
$ make
</pre>

Here is a sample of how the program is run
<pre><code>
$ cd build
$ ./TMDB_CLI_Tool -t "upcoming"
Movie Title: "Sonic the Hedgehog 3".
Overview: "Sonic, Knuckles, and Tails reunite against a powerful new adversary, Shadow, a mysterious villain with powers unlike anything they have faced before. With their abilities outmatched in every way, Team Sonic must seek out an unlikely alliance in hopes of stopping Shadow and protecting the planet.".
Release Date: "2024-12-19".
Rating: 7.8.
===========
</code></pre>
