#include <string>
#include "Song.h"


using namespace std;

Song::Song(const string& title, const string& artistName, const string& genreName, double duration) 
        : title(title), artistName(artistName), genreName(genreName), duration(duration) {}

//Getters
string Song::getTitle() const{
     return title; 
}

string Song::getArtistName() const{
     return artistName; 
}

string Song::getGenreName() const{
     return genreName; 
}

double Song::getDuration() const{
     return duration; 
}

//Setters
void Song::setTitle(const string& title){
     this->title = title; 
}

void Song::setArtistName(const string& artistName){
     this->artistName = artistName; 
}

void Song::setGenreName(const string& genreName){
     this->genreName = genreName; 
}

void Song::setDuration(double duration){
     this->duration = duration;
}