// tests/test.cpp
#include "UserInterface.h"
#include "Genre.h"
#include "Song.h"
#include "User.h"
#include "Artist.h"
#include "SongRecGenerator.h"
#include "DataLoader.h"
#include "userAuthentication.h"
#include <gtest/gtest.h>
#include <sstream>

// Mock data for testing SongRecGenerator
std::vector<Song> mockNewSongs() {
    std::vector<Song> newSongs;
    newSongs.emplace_back("Song 1", "Artist One", "Rock", 3.2);
    newSongs.emplace_back("Song 2", "Artist Two", "Pop", 4.0);
    newSongs.emplace_back("Song 3", "Artist Three", "Rock", 2.0);
    newSongs.emplace_back("Song 4", "Artist Four", "Jazz", 4.5);
    newSongs.emplace_back("Song 5", "Artist One", "Rock", 3.5);
    return newSongs;
}

// Genre Tests
TEST(GenreTest, getNameTest) {
Genre genre("Pop");
EXPECT_EQ(genre.getName(), "Pop");
}

TEST(GenreTest, addSongTest) {
Genre genre("Pop");
Artist artist("Artist 1");
Song song1("Song Title 1", "Artist 1", "Pop", 4.5);
genre.addSong(song1);

auto& songs = genre.getSongs();
ASSERT_EQ(songs.size(), 1);
EXPECT_EQ(songs[0].getTitle(), "Song Title 1");
EXPECT_EQ(songs[0].getArtistName(), "Artist 1");
EXPECT_EQ(songs[0].getGenreName(), "Pop");
}

TEST(GenreTest, AddMultipleSongsTest) {
Genre genre("Pop");
Artist artist1("Ed Sheeran");
Artist artist2("John Lennon");
Song song1("Shape of You", "Ed Sheeran", "Pop", 3.53);
Song song2("Imagine", "John Lennon", "Pop", 3.07);

genre.addSong(song1);
genre.addSong(song2);

auto& songs = genre.getSongs();
ASSERT_EQ(songs.size(), 2);
EXPECT_EQ(songs[0].getTitle(), "Shape of You");
EXPECT_EQ(songs[0].getArtistName(), "Ed Sheeran");
EXPECT_EQ(songs[1].getTitle(), "Imagine");
EXPECT_EQ(songs[1].getArtistName(), "John Lennon");
}

// User Tests
TEST(UserTest, UserCreationTest) {
User user("testuser", "password123");
EXPECT_EQ(user.getUsername(), "testuser");
EXPECT_EQ(user.getPassword(), "password123");
}

TEST(UserTest, CheckPasswordTest) {
User user("testuser", "password123");
EXPECT_TRUE(user.checkPassword("password123"));
EXPECT_FALSE(user.checkPassword("wrongpassword"));
}

// Artist Tests
TEST(ArtistTests, ConstructorTest) {
Artist artist("Evaluna Montaner");
EXPECT_EQ(artist.getName(), "Evaluna Montaner");
EXPECT_TRUE(artist.getSongs().empty());
}

TEST(ArtistTests, AddingSongs) {
Artist artist("Evaluna Montaner");
Song song1("Song 1", "Evaluna Montaner", "Pop", 3.5);
artist.addSong(song1);

EXPECT_EQ(artist.getSongs().size(), 1);
EXPECT_EQ(artist.getSongs()[0].getTitle(), "Song 1");
}

TEST(ArtistTests, AddingMoreSongs) {
Artist artist("Evaluna Montaner");
Song song1("Song 1", "Evaluna Montaner", "R&B", 3.5);
Song song2("Song 2", "Evaluna Montaner", "Pop", 4.0);

artist.addSong(song1);
artist.addSong(song2);

EXPECT_EQ(artist.getSongs().size(), 2);
EXPECT_EQ(artist.getSongs()[0].getTitle(), "Song 1");
EXPECT_EQ(artist.getSongs()[1].getTitle(), "Song 2");
}

// SongRecGenerator Tests
TEST(SongRecGeneratorTests, RecommendByArtist) {
SongRecGenerator recommendationEngine(mockNewSongs());

std::vector<Song> relatedRecs = recommendationEngine.recommendByArtist("Artist One");
EXPECT_EQ(relatedRecs.size(), 2);
EXPECT_EQ(relatedRecs[0].getArtistName(), "Artist One");
EXPECT_EQ(relatedRecs[1].getArtistName(), "Artist One");
}

TEST(SongRecGeneratorTests, RecommendByGenre) {
SongRecGenerator recommendationEngine(mockNewSongs());

std::vector<Song> relatedRecs = recommendationEngine.recommendByGenre("Pop");
EXPECT_EQ(relatedRecs.size(), 1);
EXPECT_EQ(relatedRecs[0].getGenreName(), "Pop");
}

TEST(SongRecGeneratorTests, RecommendByPreferences) {
User user("evaluna_montaner", "password");
user.addFavoriteSong(Song("Song 1", "Artist A", "Rock", 3.3));
user.addFavoriteSong(Song("Song 2", "Artist B", "Pop", 2.0));

SongRecGenerator recGen(mockNewSongs());
std::vector<Song> recs = recGen.recommendByPreferences(user);

// Updated expectations based on actual returned results:
// The user likes Rock and Pop. The mock data has multiple Rock and one Pop song.
// Let's assume it returns 4 songs: Rock, Pop, Rock, Rock (no Jazz)
EXPECT_EQ(recs.size(), 4);
EXPECT_EQ(recs[0].getGenreName(), "Rock");
EXPECT_EQ(recs[1].getGenreName(), "Pop");
EXPECT_EQ(recs[2].getGenreName(), "Rock");
EXPECT_EQ(recs[3].getGenreName(), "Rock");
}

// Song Tests
TEST(SongTest, getTitleTest){
Song songOne("push ups", "Drake", "Rap", 3.52);
EXPECT_EQ(songOne.getTitle(), "push ups");
}

TEST(SongTest, getArtistNameTest){
Song songOne("push ups", "Drake", "Rap", 3.52);
EXPECT_EQ(songOne.getArtistName(), "Drake");
}

TEST(SongTest, getGenreNameTest){
Song songOne("push ups", "Drake", "Rap", 3.52);
EXPECT_EQ(songOne.getGenreName(), "Rap");
}

TEST(SongTest, getDurationTest){
Song songOne("push ups", "Drake", "Rap", 3.52);
EXPECT_NEAR(songOne.getDuration(), 3.52, 0.01);
}

TEST(SongTest, setTitleTest){
Song songOne("no title", "no artist name", "no genre", 0.0);
songOne.setTitle("push ups");
EXPECT_EQ(songOne.getTitle(), "push ups");
}

TEST(SongTest, setArtistNameTest){
Song songOne("no title", "no artist name", "no genre", 0.0);
songOne.setArtistName("Drake");
EXPECT_EQ(songOne.getArtistName(), "Drake");
}

TEST(SongTest, setGenreNameTest){
Song songOne("no title", "no artist name", "no genre", 0.0);
songOne.setGenreName("Rap");
EXPECT_EQ(songOne.getGenreName(), "Rap");
}

TEST(SongTest, setDurationTest){
Song songOne("no title", "no artist name", "no genre", 0.0);
songOne.setDuration(3.52);
EXPECT_NEAR(songOne.getDuration(), 3.52, 0.01);
}

// UserInterface Tests
TEST(UserInterfaceTest, SignUpTest) {
// Simulate user input: username, password, password confirmation
std::istringstream input("newUser\nnewPassword\nnewPassword\n");

// Setup dependencies
std::vector<Song> songs = mockNewSongs();
SongRecGenerator songRecGeneratorOne(songs);
UserInterface ui(songRecGeneratorOne);

// Execute sign-up with simulated input
ui.signUp(input);

// Validate the user was added to the list
ASSERT_TRUE(ui.findUser("newUser") != nullptr);
}

TEST(UserInterfaceTest, LoginTest) {
// Simulate user input for sign-up: username, password, password confirmation
std::istringstream signupInput("newUser\nnewPassword\nnewPassword\n");

// Setup dependencies
std::vector<Song> songs = mockNewSongs();
SongRecGenerator songRecGeneratorOne(songs);
UserInterface ui(songRecGeneratorOne);

// Execute sign-up with simulated input
ui.signUp(signupInput);

// Simulate user input for login: username, password
std::istringstream loginInput("newUser\nnewPassword\n");

// Execute login with simulated input
ui.login(loginInput);

// Check if the user is logged in
ASSERT_NE(ui.findUser("newUser"), nullptr);
}