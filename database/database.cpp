// Peter Schwendeman
//
//
// database.cpp
//

#include "database.h"

/************
 *  PUBLIC  *
 ************/

// Database Contructor
Database::Database(string &name, vector<string> &table_names, vector<Table> &table_ptrs) {
    db_name = name;
    for(int i = 0; i < table_names.size(); ++i) {
        tables.insert(pair<string, Table*>(table_names[i], &(table_ptrs[i])));
    }
}

// Updates table entries @ edit_columns where row contains comparisons @ columns
// Input: string &table_name -> name of table
// Input: vector<string> &edit_columns -> list of names of columns where new entries are located
// Input: vector<::database::Entry> &entries -> list of new entries
// Input: vector<string> &columns -> list of names of columns where comparison entries are located
// Input: vector<::database::Entry> &comparisons -> list of comparison entries
void Database::update(string &table_name, 
                        vector<string> &edit_columns,  
                        vector<::database::Entry> &entries, 
                        vector<string> &columns, 
                        vector<::database::Entry> &comparisons) {
    Table* table = get_table(table_name);
    table->edit_rows(edit_columns, entries, columns, comparisons);
} // update()

// Updates table entries @ edit_columns where row contains comparisons @ columns
// Input: string &table_name -> name of table
// Input: vector<string> &edit_columns -> list of names of columns where new entries are located
// Input: vector<::database::Entry> &entries -> list of new entries
// Input: vector<string> &columns -> list of names of columns where comparison entries are located
// Input: vector<::database::Entry> &comparisons -> list of comparison entries
void Database::update(string &table_name, 
                        vector<string> &edit_columns,  
                        vector<::database::Entry> &entries) {
    //Table* table = get_table(table_name);
    Table table = Storage::read_table(db_name, table_name);
    table->edit_all(edit_columns, entries);
} // update()

// Inserts new row into table
// Input: string &table_name -> name of table
// Input: ::database::Row row -> row
void Database::insert(string &table_name, 
            ::database::Row row) {
    Table* table = get_table(table_name);
    table->insert(row);
} // insert()

// Selects rows from table where row contains comparisons @ columns
// Input: string &table_name -> name of table
// Input: vector<string> &columns -> list of names of columns where comparison entries are located
// Input: vector<::database::Entry> &comparisons -> list of comparison entries
vector<::database::Row> Database::select(string &table_name, 
                                            vector<string> &columns, 
                                            vector<::database::Entry> &comparisons) {
    Table* table = get_table(table_name);
    return table->filter(columns, comparisons);
} // select()

// Selects rows from table where row contains comparisons @ columns
// Input: string &table_name -> name of table
// Input: vector<string> &columns -> list of names of columns where comparison entries are located
// Input: vector<::database::Entry> &comparisons -> list of comparison entries
vector<::database::Row> Database::select(string &table_name, 
                                            vector<string> &select_columns, 
                                            vector<string> &columns, 
                                            vector<::database::Entry> &comparisons) {
    Table* table = get_table(table_name);
    return table->filter(select_columns, columns, comparisons);
} // select()

void Database::delete_rows(string &table_name, 
                            vector<string> &columns, 
                            vector<::database::Entry> &comparisons) {
    Table* table = get_table(table_name);
    table->remove_rows(columns, comparisons);
}

void Database::delete_all_rows(string &table_name) {
    Table* table = get_table(table_name);
    table->remove_all();
}

// Deletes table data
// Input: string &table_name -> name of table
void Database::drop_table(string &table_name) {
    tables.erase(table_name);
} // drop_table()

// Creates new table w/ column names and specified types
// Input: string &table_name -> name of table
// Input: vector<string> &column_names -> list of columns in table
// Input: vector<string> &column_types -> list of specified data types of columns in table
void Database::create_table(string &table_name, 
                    vector<string> &column_names, 
                    vector<string> &column_types) {
    Table table = Table(column_names, column_types);
    tables.emplace(table_name, &table);
} // create_table()

/*************
 *  PRIVATE  *
 *************/

Table* Database::get_table(string& table_name) {
    auto it = tables.find(table_name);
    if(it == tables.end()) {
        string error_message = "Table of name " + table_name + " does not exit.";
        throw std::out_of_range(error_message);
    }
    return it->second;
} // get_table()