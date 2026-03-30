// Artist.h
#ifndef ARTIST_H
#define ARTIST_H

#include <string>
#include <vector>
#include "Song.h"

class Artist {
private:
    std::string name;
    std::vector<Song> songs;

public:
    Artist(const std::string& name);

    // Getters
    std::string getName() const;
    std::vector<Song>& getSongs();

    // Methods
    void addSong(const Song& song);
};

#endif // ARTIST_H
