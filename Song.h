#pragma once

#include <string>

using namespace std;

class Song {
private:
    string title;
    string artistName;
    string genreName;
    double duration; // time in minutes

public:
    // Constructor
    Song(const string& title, const string& artistName, const string& genreName, double duration);

    // Getters
    string getTitle() const;
    string getArtistName() const;
    string getGenreName() const;
    double getDuration() const;

    // Setters
    void setTitle(const string& title);
    void setArtistName(const string& artistName);
    void setGenreName(const string& genreName);
    void setDuration(double duration);

};