// Peter Schwendeman
//
//
// Storage.cpp
//

#include "Storage.h"

// TODO: Implement once figure out how data is written
static Database Storage::read_data() {

} // read_data()

// TODO: Figure out how to read/write/search directory
static void Storage::write_data(Database db) {
    std::string path = "/" + db.get_name();
    // If the directory with name exists
    if(fs::directory_iterator(path) != fs::directory_iterator::end) {
        for (const auto & entry : fs::directory_iterator(path)) {
            std::cout << entry.path() << std::endl;
        }       
    } else { // Create Directory and write database to it
        // TODO: some creation code
        int dir = mkdir(path);
    }
    
} // write_data()
