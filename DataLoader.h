#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include <vector>
#include "Song.h"

class DataLoader {
public:
    static std::vector<Song> loadSongs(const std::string& filename);
};

#endif // DATA_LOADER_H