#include "DataLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<Song> DataLoader::loadSongs(const std::string& filename) {
    std::vector<Song> songs;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening songs file." << std::endl;
        return songs;
    }

    std::string line;
    getline(file, line); // Skip header line

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string title, artist, genre, durationStr;

        getline(ss, title, ',');
        getline(ss, artist, ',');
        getline(ss, genre, ',');
        getline(ss, durationStr, ',');

        double duration = std::stod(durationStr);

        Song song(title, artist, genre, duration);
        songs.push_back(song);
    }

    file.close();
    return songs;
}