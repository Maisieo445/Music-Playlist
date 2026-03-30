// include/UserInterface.h
#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <vector>
#include <string>
#include "User.h"
#include "SongRecGenerator.h"

#ifdef UNIT_TEST
#include <gtest/gtest_prod.h>  // Required for FRIEND_TEST
#endif

class UserInterface {
private:
    std::vector<User> users;
    User* currentUser;
    SongRecGenerator songRecGenerator;

public:
    // Constructor
    UserInterface(const SongRecGenerator& songRecGenerator);

    // Start the User Interface
    void start();

    // Overloaded methods for testing
    void signUp(std::istream& in);
    void login(std::istream& in);

    // Original methods using std::cin
    void signUp();
    void login();

private:
    // Main Menu Loop
    void mainMenu();

    // Other functionalities
    void searchSongs();
    void viewRecommendations();
    void manageFavorites();
    void logout();

    // Helper functions
    User* findUser(const std::string& username);
    void loadUsers();
    void saveUsers();

#ifdef UNIT_TEST
    // Friend declarations for GoogleTest
    FRIEND_TEST(UserInterfaceTest, SignUpTest);
    FRIEND_TEST(UserInterfaceTest, LoginTest);
#endif
};

#endif // USERINTERFACE_H