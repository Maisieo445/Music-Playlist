// src/SongRecGenerator.cpp
#include "SongRecGenerator.h"
#include <algorithm>

SongRecGenerator::SongRecGenerator(const std::vector<Song>& allSongs) : allSongs(allSongs) {}

std::vector<Song> SongRecGenerator::recommendByArtist(const std::string& artistName) {
    std::vector<Song> recommendations;
    for (const auto& song : allSongs) {
        if (song.getArtistName() == artistName) {
            recommendations.push_back(song);
        }
    }
    return recommendations;
}

std::vector<Song> SongRecGenerator::recommendByGenre(const std::string& genreName) {
    std::vector<Song> recommendations;
    for (const auto& song : allSongs) {
        if (song.getGenreName() == genreName) {
            recommendations.push_back(song);
        }
    }
    return recommendations;
}

std::vector<Song> SongRecGenerator::recommendByPreferences(const User& user) {
    std::vector<Song> recommendations;
    std::vector<std::string> userGenres;

    for (const auto& favSong : user.getFavoriteSongs()) {
        if (std::find(userGenres.begin(), userGenres.end(), favSong.getGenreName()) == userGenres.end()) {
            userGenres.push_back(favSong.getGenreName());
        }
    }

    for (const auto& song : allSongs) {
        if (std::find(userGenres.begin(), userGenres.end(), song.getGenreName()) != userGenres.end()) {
            recommendations.push_back(song);
        }
    }
    return recommendations;
}

const std::vector<Song>& SongRecGenerator::getAllSongs() const {
    return allSongs;
}