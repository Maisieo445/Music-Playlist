// include/SongRecGenerator.h
#ifndef SONGRECGENERATOR_H
#define SONGRECGENERATOR_H

#include <vector>
#include <string>
#include "Song.h"
#include "User.h"

class SongRecGenerator {
private:
    std::vector<Song> allSongs;

public:
    SongRecGenerator(const std::vector<Song>& allSongs);

    // Recommendation Methods
    std::vector<Song> recommendByArtist(const std::string& artistName);
    std::vector<Song> recommendByGenre(const std::string& genreName);
    std::vector<Song> recommendByPreferences(const User& user);

    // Accessor for all songs
    const std::vector<Song>& getAllSongs() const;
};

#endif // SONGRECGENERATOR_H