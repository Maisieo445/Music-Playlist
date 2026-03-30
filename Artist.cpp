// Artist.cpp
#include "Artist.h"

Artist::Artist(const std::string& name) : name(name) {}

std::string Artist::getName() const { return name; }
std::vector<Song>& Artist::getSongs() { return songs; }

void Artist::addSong(const Song& song) {
    songs.push_back(song);
}
