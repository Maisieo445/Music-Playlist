
#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "Song.h"

class User {
private:
    std::string username;
    std::string password; // For simplicity; in real applications, passwords should be hashed
    std::vector<Song> favoriteSongs;

public:
    User(const std::string& username, const std::string& password);

    // Getters
    std::string getUsername() const;
    std::string getPassword() const;
    bool checkPassword(const std::string& password) const;

    // Methods
    void addFavoriteSong(const Song& song);

    // **Add both const and non-const getters**
    const std::vector<Song>& getFavoriteSongs() const;
    std::vector<Song>& getFavoriteSongs(); // Non-const version
};

#endif 
