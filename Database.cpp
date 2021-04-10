// Peter Schwendeman
//
//
// Database.cpp
//

#include "Database.h"

/************
 *  PUBLIC  *
 ************/

// Updates table entries @ edit_columns where row contains comparisons @ columns
// Input: string &table_name -> name of table
// Input: vector<string> &edit_columns -> list of names of columns where new entries are located
// Input: vector<::database::Entry> &entries -> list of new entries
// Input: vector<string> &columns -> list of names of columns where comparison entries are located
// Input: vector<::database::Entry> &comparisons -> list of comparison entries
void Database::update(string &table_name, 
/* parameter */ vector<string> &edit_columns,  
/* parameter */ vector<::database::Entry> &entries, 
/* parameter */ vector<string> &columns, 
/* parameter */ vector<::database::Entry> &comparisons) {
    try {
        Table* table = get_table(table_name);
    } catch () {
        // throw()
    }
    table->edit_rows(edit_columns, entries, columns, comparisons);
} // update()

// Inserts new row into table
// Input: string &table_name -> name of table
// Input: ::database::Row row -> row
void insert(string &table_name, 
/* parameter */ ::database::Row row) {
    Table* table = get_table(table_name);
    table->insert(row);
} // insert()

// Selects rows from table where row contains comparisons @ columns
// Input: string &table_name -> name of table
// Input: vector<string> &columns -> list of names of columns where comparison entries are located
// Input: vector<::database::Entry> &comparisons -> list of comparison entries
vector<::database::Row> Database::select(string &table_name, 
/* parameter */ vector<string> &columns, 
/* parameter */ vector<::database::Entry> &comparisons) {
    try {
        Table* table = get_table(table_name);
    } catch () {
        // throw()
    }
    return table->filter(columns, comparisons);
} // select()

// Deletes table data
// Input: string &table_name -> name of table
void Database::drop_table(string &table_name) {
    tables.erase(table_name);
} // drop_table()

// Creates new table w/ column names and specified types
// Input: string &table_name -> name of table
// Input: vector<string> &column_names -> list of columns in table
// Input: vector<string> &column_types -> list of specified data types of columns in table
void create_table(string &table_name, 
/* parameter */ vector<string> &column_names, 
/* parameter */ vector<string> &column_types) {
    table = Table(column_names, column_types);
    tables.emplace(table_name, table);
} // create_table()

/*************
 *  PRIVATE  *
 *************/

Table* Database::get_table(string& table_name) {
    auto it = tables.find(table_name);
    if(it == tables.end()) {
        // throw()
        cout << "ERROR" << endl;
        return;
    }
    return it->second();
} // get_table()