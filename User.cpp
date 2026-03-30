//src/User.cpp
#include "User.h"

User::User(const std::string& username, const std::string& password)
        : username(username), password(password) {}

std::string User::getUsername() const { return username; }
std::string User::getPassword() const { return password; }

bool User::checkPassword(const std::string& password) const {
    return this->password == password;
}

void User::addFavoriteSong(const Song& song) {
    favoriteSongs.push_back(song);
}

// **Implement both getters**

const std::vector<Song>& User::getFavoriteSongs() const {
    return favoriteSongs;
}

std::vector<Song>& User::getFavoriteSongs() {
    return favoriteSongs;
}

