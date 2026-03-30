#ifndef GENRE_H
#define GENRE_H

#include <string>
#include <vector>
#include "Song.h"

class Genre {
private:
    std::string name;
    std::vector<Song> songs;

public:

    Genre(const std::string& name);

    // Getters
    std::string getName() const;
    std::vector<Song>& getSongs();

    // Methods
    void addSong(const Song& song);
};

#endif

