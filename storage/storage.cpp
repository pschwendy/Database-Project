// Peter Schwendeman
//
//
// Storage.cpp
//

#include "Storage.h"
using namespace std;

// Given the name of the database, reads data from file system if the database exists
// If not, creates a new blank database
// Input: string &db_name -> name of database 
static Database* Storage::read_data(string &db_name) {
    Database db;

    string file = "/databases/databases.txt";
    ifstream databases(file);

    string path = "/databases/" + db_name + "/";
    
    bool exists;
    string name_check;
    if(!databases.good()) {
        // throw()
    }
    while(databases >> name_check) {
        if(name_check == db_name) {
            exists = true;
            break;
        }
    }

    if(exists) {
        ifstream table_list(path + "tables.txt");
        string table_name;
        vector<string> names;
        vector<Table> tables;
        
        while(table_list >> table_name) {
            ifstream schema(path + table_name + "_schema.txt");
            vector<string> columns;
            vector<string> types;

            while(schema >> types) {
                schema >> columns;
            }

            ifstream rows(path + table_name + "_rows.txt");
            ::database::Table parse_table;
            parse_table.ParseFromIstream(&rows));
            Table table = Table(table_name, columns, types, parse_table);

            names.emplace_back(table_name);
            tables.emplace_back(table);
        }
        db = Database(db_name, names, tables);
    } else {
        db = Database(db_name);
    }

    return db;
} // read_data()

// Writes to database directory given a database
// Input: Database &db -> database being written to storage
static void Storage::write_data(Database &db) {
    // Add file to list databases inside of some collective database folder
    // Add file to list tables inside each individual database folder
    // Iterate throught files to get and use paths
    string file = "/databases/databases.txt";
    string path = "/databases/" + db.get_name() + "/";

    stringstream table_list;
    ifstream databases(file);

    bool exists;
    string name_check;
    if(!databases.good()) {
        // throw()
    }
    while(databases >> db_names) {
        if(name_check == db.get_name()) {
            exists = true;
            break;
        }
    }
    // If the directory with name exists
    if(!exists) {
        int dir = mkdir(path, 0777);
        if(dir == -1) {
            // throw()
        }
    } /*else { // Create Directory and write database to it
        // TODO: some creation code
        
    }*/
    for(auto it : *(db.get_tables())) {
        table_list << it.first << "\n";

        ofstream schema(path + it->first + "_schema.txt");
        schema << it->second->schema();
        
        ofstream rows(path + it->first + "_rows.txt");
        if(!it->second->serialize(rows)) {
            // throw()
        }
    }

    ofstream os(path + "tables.txt");
    os << table_list;
} // write_data()

// delete -> fs::remove_all("myDirectory");