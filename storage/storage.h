// Peter Schwendeman
//
//
// storage.h
//

#ifndef Storage_h
#define Storage_h

// #include "database/database.h"
#include <filesystem>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include "table/table.h"

typedef typename std::unordered_map<std::string, std::pair<std::string, std::string> > TableRouter;

class DatabaseRouter {
    public:
        TableRouter operator[](std::string db_key){
            auto it = router.find(db_key);
            if(it == router.end()) {
                string error_message = "Database of name " + db_key + " does not exit.";
                throw std::out_of_range(error_message);
            }
            
            return it->second;
        }

        void insert(std::pair<std::string, TableRouter> insert_pair) {
            router.insert(insert_pair);
        }
    private:
        std::unordered_map<std::string, TableRouter> router;
};
// namespace fs = std::filesystem;

namespace Storage {
    namespace fs = std::__fs::filesystem;
    // static void write_data(Database &db);
    void read_data();
    bool check_database_exists(string &db_name); 
    void create_database(string &db_name);
    void write_table(string &db_name, Table &table);
    void create_table(string &db_name, Table &table);
    
    // Load individual tables when using them
    Table read_table(std::string &db_name, std::string &table_name);
    // static void write_table(string &db_name, string &table_name);
    DatabaseRouter router;
    string path_to_database = "/Users/pschwendy/Database-Project/databases";
    string database_list_path = path_to_database + "/databases.txt";
}

// router = unordered_map<string, unordered_map<string, std::pair<string, string> > >();
#endif // Storage_h