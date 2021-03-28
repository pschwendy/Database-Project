// Peter Schwendeman
//
//
// Database.cpp
//

#include "Database.h"

/************
 *  PUBLIC  *
 ************/

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
}

vector<::database::Row> Database::select(string &table_name, 
/* parameter */ vector<string> &columns, 
/* parameter */ vector<::database::Entry> &comparisons) {
    try {
        Table* table = get_table(table_name);
    } catch () {
        // throw()
    }
    return table->filter(columns, comparisons);
}


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
}