// Peter Schwendeman
//
//
// storage.h
//

#ifndef Storage_h
#define Storage_h

#include "database/database.h"
#include <filesystem>
#include <iostream>
#include <fstream>

namespace fs = std::filesystem;

class Storage {
    public:
        static Database read_data(string &db_name);
        static void write_data(Database &db);
};

#endif // Storage_h