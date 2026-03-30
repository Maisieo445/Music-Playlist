// src/UserInterface.cpp
#include "UserInterface.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>

// Constructor
UserInterface::UserInterface(const SongRecGenerator& songRecGenerator)
        : currentUser(nullptr), songRecGenerator(songRecGenerator) {
    loadUsers();
}

// Start the User Interface
void UserInterface::start() {
    mainMenu();
}

// Main Menu Loop
void UserInterface::mainMenu() {
    int choice;
    do {
        std::cout << "\nWelcome to SongBeats!" << std::endl;
        std::cout << "1. Login" << std::endl;
        std::cout << "2. Sign Up" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Please select an option: ";

        if (!(std::cin >> choice)) {
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a number between 1 and 3." << std::endl;
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore newline

        switch (choice) {
            case 1:
                login(std::cin);
                break;
            case 2:
                signUp(std::cin);
                break;
            case 3:
                std::cout << "Thank you for using SongBeats. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid option. Please select again." << std::endl;
        }
    } while (choice != 3);
}

// Overloaded signUp Method for Testing
void UserInterface::signUp(std::istream& in) {
    std::string username, password, passwordConfirm;

    while (true) {
        std::cout << "Choose a Username: ";
        if (!std::getline(in, username)) {
            std::cout << "Failed to read username. Aborting sign-up." << std::endl;
            return;
        }

        if (username.empty()) {
            std::cout << "Username cannot be empty. Please try again." << std::endl;
            continue;
        }

        if (findUser(username)) {
            std::cout << "Username already taken. Please choose a different username." << std::endl;
            continue;
        }

        std::cout << "Choose a Password: ";
        if (!std::getline(in, password)) {
            std::cout << "Failed to read password. Aborting sign-up." << std::endl;
            return;
        }

        if (password.empty()) {
            std::cout << "Password cannot be empty. Please try again." << std::endl;
            continue;
        }

        std::cout << "Confirm Password: ";
        if (!std::getline(in, passwordConfirm)) {
            std::cout << "Failed to read password confirmation. Aborting sign-up." << std::endl;
            return;
        }

        if (password != passwordConfirm) {
            std::cout << "Passwords do not match. Please try again." << std::endl;
            continue;
        }

        // Add new user
        users.emplace_back(username, password);
        currentUser = &users.back();

        saveUsers();

        std::cout << "Sign-up successful! You are now logged in." << std::endl;
        mainMenu();
        break;
    }
}

// Original signUp Method Using std::cin
void UserInterface::signUp() {
    signUp(std::cin);
}

// Overloaded login Method for Testing
void UserInterface::login(std::istream& in) {
    std::string username, password;

    std::cout << "Enter Username: ";
    if (!std::getline(in, username)) {
        std::cout << "Failed to read username. Aborting login." << std::endl;
        return;
    }

    if (username.empty()) {
        std::cout << "Username cannot be empty." << std::endl;
        return;
    }

    User* user = findUser(username);
    if (!user) {
        std::cout << "User not found." << std::endl;
        return;
    }

    std::cout << "Enter Password: ";
    if (!std::getline(in, password)) {
        std::cout << "Failed to read password. Aborting login." << std::endl;
        return;
    }

    if (password.empty()) {
        std::cout << "Password cannot be empty." << std::endl;
        return;
    }

    if (user->checkPassword(password)) {
        currentUser = user;
        std::cout << "Login successful!" << std::endl;
        // Proceed to user-specific menu or actions
    } else {
        std::cout << "Incorrect password." << std::endl;
    }
}

// Original login Method Using std::cin
void UserInterface::login() {
    login(std::cin);
}

// Logout Method
void UserInterface::logout() {
    if (currentUser) {
        std::cout << "You have been logged out." << std::endl;
        currentUser = nullptr;
    } else {
        std::cout << "No user is currently logged in." << std::endl;
    }
}

// Search Songs Method (Placeholder Implementation)
void UserInterface::searchSongs() {
    std::string query;
    std::cout << "Enter song title, artist, or genre to search: ";
    if (!std::getline(std::cin, query)) {
        std::cout << "Failed to read search query." << std::endl;
        return;
    }

    if (query.empty()) {
        std::cout << "Search query cannot be empty." << std::endl;
        return;
    }

    std::vector<Song> results;
    for (const auto& song : songRecGenerator.getAllSongs()) {
        if (song.getTitle().find(query) != std::string::npos ||
            song.getArtistName().find(query) != std::string::npos ||
            song.getGenreName().find(query) != std::string::npos) {
            results.push_back(song);
        }
    }

    if (results.empty()) {
        std::cout << "No songs found matching your query." << std::endl;
        return;
    }

    std::cout << "\nSearch Results:" << std::endl;
    int index = 1;
    for (const auto& song : results) {
        std::cout << index++ << ". " << song.getTitle() << " by " << song.getArtistName()
                  << " [" << song.getGenreName() << "] (" << song.getDuration() << " mins)" << std::endl;
    }

    // Option to add songs to favorites
    std::cout << "Enter the number of the song to add to your favorites, or 0 to return to the main menu: ";
    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear(); // Clear error flags
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        std::cout << "Invalid input. Returning to main menu." << std::endl;
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore newline

    if (choice > 0 && choice <= static_cast<int>(results.size())) {
        currentUser->addFavoriteSong(results[choice - 1]);
        std::cout << "Song added to your favorites!" << std::endl;
    } else if (choice == 0) {
        // Do nothing, return to main menu
    } else {
        std::cout << "Invalid choice. Returning to main menu." << std::endl;
    }
}

// View Recommendations Method (Placeholder Implementation)
void UserInterface::viewRecommendations() {
    if (!currentUser) {
        std::cout << "No user is logged in. Please log in to view recommendations." << std::endl;
        return;
    }

    std::cout << "\nRecommendations based on your favorite songs:" << std::endl;
    std::vector<Song> recommendations = songRecGenerator.recommendByPreferences(*currentUser);

    if (recommendations.empty()) {
        std::cout << "No recommendations available. Add favorite songs to get personalized recommendations." << std::endl;
        return;
    }

    int index = 1;
    for (const auto& song : recommendations) {
        std::cout << index++ << ". " << song.getTitle() << " by " << song.getArtistName()
                  << " [" << song.getGenreName() << "] (" << song.getDuration() << " mins)" << std::endl;
    }
}

// Manage Favorites Method (Placeholder Implementation)
void UserInterface::manageFavorites() {
    if (!currentUser) {
        std::cout << "No user is logged in. Please log in to manage favorites." << std::endl;
        return;
    }

    std::vector<Song>& favorites = currentUser->getFavoriteSongs();

    if (favorites.empty()) {
        std::cout << "You have no favorite songs." << std::endl;
        return;
    }

    std::cout << "\nYour Favorite Songs:" << std::endl;
    int index = 1;
    for (const auto& song : favorites) {
        std::cout << index++ << ". " << song.getTitle() << " by " << song.getArtistName()
                  << " [" << song.getGenreName() << "] (" << song.getDuration() << " mins)" << std::endl;
    }

    std::cout << "Enter the number of the song to remove from favorites, or 0 to return to the main menu: ";
    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear(); // Clear error flags
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        std::cout << "Invalid input. Returning to main menu." << std::endl;
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore newline

    if (choice > 0 && choice <= static_cast<int>(favorites.size())) {
        favorites.erase(favorites.begin() + choice - 1);
        std::cout << "Song removed from your favorites." << std::endl;
    } else if (choice == 0) {
        // Do nothing, return to main menu
    } else {
        std::cout << "Invalid choice. Returning to main menu." << std::endl;
    }
}

// Helper Method to Find User by Username
User* UserInterface::findUser(const std::string& username) {
    for (auto& user : users) {
        if (user.getUsername() == username) {
            return &user;
        }
    }
    return nullptr;
}

// Load Users from Storage
void UserInterface::loadUsers() {
    std::ifstream file("data/users.txt");
    if (!file.is_open()) {
        std::cerr << "Users file not found. Starting with no users." << std::endl;
        return;
    }

    std::string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string username, password;

        getline(ss, username, ',');
        getline(ss, password, ',');

        if (username.empty() || password.empty()) {
            std::cerr << "Invalid user entry in file: " << line << std::endl;
            continue;
        }

        User user(username, password);
        users.push_back(user);
    }
    file.close();
}

// Save Users to Storage
void UserInterface::saveUsers() {
    std::ofstream file("data/users.txt");
    if (!file.is_open()) {
        std::cerr << "Error saving users." << std::endl;
        return;
    }

    file << "Username,Password\n";
    for (const auto& user : users) {
        file << user.getUsername() << "," << user.getPassword() << "\n";
    }
    file.close();
}