// Peter Schwendeman
//
//
// Database.h
//

#ifndef Database_h
#define Database_h

#include <unordered_map>
#include <string>
#include <vector>
#include "Table.h"

using namespace std;

// Class containing database when running program
class Database {
    public:
        // Database Contructor
        // TODO: Implement when storage system is figured out
        Database();

        // Returns name of database
        string get_name() {
            return db_name;
        } // get_name()

        // Updates table entries @ edit_columns where row contains comparisons @ columns
        // Input: string &table_name -> name of table
        // Input: vector<string> &edit_columns -> list of names of columns where new entries are located
        // Input: vector<::database::Entry> &entries -> list of new entries
        // Input: vector<string> &columns -> list of names of columns where comparison entries are located
        // Input: vector<::database::Entry> &comparisons -> list of comparison entries
        void update(string &table_name, 
                    vector<string> &edit_columns, 
                    vector<::database::Entry> &entries, 
                    vector<string> &columns, 
                    vector<::database::Entry> &comparisons);
        
        // Inserts new row into table
        // Input: string &table_name -> name of table
        // Input: ::database::Row row -> row
        void insert(string &table_name, 
                    ::database::Row row);
        
        // Selects rows from table where row contains comparisons @ columns
        // Input: string &table_name -> name of table
        // Input: vector<string> &columns -> list of names of columns where comparison entries are located
        // Input: vector<::database::Entry> &comparisons -> list of comparison entries
        vector<::database::Row> select(string &table_name, 
                                    vector<string> &columns, 
                                    vector<::database::Entry> &comparisons);
        
        // Deletes table data
        // Input: string &table_name -> name of table
        void drop_table(string &table_name);
        
        // Creates new table w/ column names and specified types
        // Input: string &table_name -> name of table
        // Input: vector<string> &column_names -> list of columns in table
        // Input: vector<string> &column_types -> list of specified data types of columns in table
        void create_table(string &table_name, 
                        vector<string> &column_names, 
                        vector<string> &column_types);


        // input: string &table_name -> name of table
        void select_join(string &table_name);
    
    private:
        string db_name;
        unordered_map<string, Table*> tables;

        Table* get_table(string& table_name);
};

#endif // Database_h