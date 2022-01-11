// Peter Schwendeman
//
//
// database.h
//

#ifndef Database_h
#define Database_h

#include <unordered_map>
#include <string>
#include <vector>
#include "table/table.h"
#include "storage/storage.h"

using namespace std;

// Class containing database when running program
class Database {
    public:
        // Default Constructor  
        Database(string name) { 
            db_name = name;
        }

        // Database Contructor
        Database(string &name, vector<string> &table_names, vector<Table> &table_ptrs);
        
        // Returns name of database
        string get_name() {
            return db_name;
        } // get_name()

        // Returns number of tables
        int num_tables() {
            return tables.size();
        } // num_tables()
        
        const unordered_map<string, Table*>* get_tables() {
            return &tables;
        }

        // Returns index of given column in given table
        size_t column_index(string &table_name, string &column_name) {
            Table* table = get_table(table_name);
            return table->column_index(column_name);
        }

        // 
        vector<string> get_columns(string &table_name) {
            Table* table = get_table(table_name);
            return table->columns();
        }

        database::Table_Type get_column_type(string &table_name, string &column_name) {
            Table* table = get_table(table_name);
            return table->column_type(column_name);
        }

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

        void update(string &table_name, 
                    vector<string> &edit_columns,  
                    vector<::database::Entry> &entries);
        
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
        
        // Selects specific columns from table where row contains comparisons @ columns
        // Returns vector of rows containing selected columns from table
        // Input: string &table_name -> name of table
        // Input: vector<string> columns select_columns -> columns in final row
        // Input: vector<string> &columns -> list of names of columns where comparison entries are located
        // Input: vector<::database::Entry> &comparisons -> list of comparison entries
        vector<::database::Row> select(string &table_name, 
                                        vector<string> &select_columns, 
                                        vector<string> &columns, 
                                        vector<::database::Entry> &comparisons);

        // Deletes rows from table where row contains comparisons @ columns
        // Input: string &table_name -> name of table
        // Input: vector<string> &columns -> list of names of columns where comparison entries are located
        // Input: vector<::database::Entry> &comparisons -> list of comparison entries
        void delete_rows(string &table_name, 
                            vector<string> &columns, 
                            vector<::database::Entry> &comparisons);

        // Deletes all rows from given table where row contains comparisons @ columns
        // Input: string &table_name -> name of table
        void delete_all_rows(string &table_name);

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