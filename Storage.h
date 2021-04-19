// Peter Schwendeman
//
//
// Storage.h
//

#ifndef Storage_h
#define Storage_h

#include "Database.h"
#include <filesystem>
#include <iostream>
#include <fstream>

namespace fs = std::filesystem;

class Storage {
    public:
        static Database read_data();
        static void write_data(Database db);
};

#endif // Storage_h