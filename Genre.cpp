#include "Genre.h"

Genre::Genre(const std::string& name) : name(name) {}

std::string Genre::getName() const { return name; }
std::vector<Song>& Genre::getSongs() { return songs; }

void Genre::addSong(const Song& song) {
    songs.push_back(song);
}
