// Peter Schwendeman
//
//
// driver.h
//

#ifndef Driver_h
#define Driver_h

#include <iostream>
#include <exception>
#include <sstream>
#include <cassert>
#include <string>
#include "storage/storage.h"
#include "table/table.h"

using namespace std;
//#include "Storage.h"

class Driver {
    public:
        // TODO: implement with storage system
        Driver() { 
            using_db = false;
        }

        // Gets input and calls functions accordingly
        void run(istream& in);

        // Closes program and tells storage class store data
        void finish() { }

        string preprocess_input(string &input);
        void parse_select(stringstream &input);
        void parse_insert(stringstream &input);
        void parse_delete(stringstream &input);
        void parse_update(stringstream &input);
        void parse_create(string &input);

    private:
        // Database* db;
        string db_name;
        bool using_db;

        void parse_input(string &input);
        void add_entry_to_row(Table &table, string &column_name, string &entry_name, ::database::Row entries);
        void add_entry_to_row(Table &table, string &column_name, string &entry_name, vector<::database::Entry> entries);
        void set_entry_value(::database::Entry &entry, string &entry_name, string &column_name, Table &table);
        void construct_columns_and_entries(vector<string> &columns, vector<::database::Entry> &entries, string &statement, Table &table);
        // Add preprocessing project
        /*string preprocess_input(string &input);
        void parse_select(stringstream &input)
        void parse_insert(stringstream &input)
        void parse_delete(stringstream &input)*/
};

#endif // Driver_h