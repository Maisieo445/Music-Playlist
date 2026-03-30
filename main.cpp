#include <iostream>
#include <unistd.h> // For getcwd
#include <limits.h> // For PATH_MAX
#include "DataLoader.h"
#include "SongRecGenerator.h"
#include "UserInterface.h"

int main(int argc, char* argv[]) {

    // Load songs
    std::vector<Song> allSongs = DataLoader::loadSongs("data/songs.txt");

    if (allSongs.empty()) {
        std::cerr << "Error opening songs file.\nNo songs available. Exiting application." << std::endl;
        return 1;
    }

    // Initialize the recommendation engine
    SongRecGenerator recEngine(allSongs);

    // Initialize the user interface
    UserInterface ui(recEngine);

    // Start the application
    ui.start();

    return 0;
}