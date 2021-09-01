// Peter Schwendeman
//
//
// driver.cpp
//

#include "driver.h"
#include <iostream>
#include <exception>
#include <sstream>

using namespace std;


/************
 *  PUBLIC  *
 ************/

// Opens shell for input database commands
void run() {
    string input;
    cout << "#" << endl;
    while(getline(cin, input)) {
        parse_input(input);
    }
}

/*************
 *  PRIVATE  *
 *************/

void parse_input(string &input) {
    stringstream ss(input);

    string command;
    ss >> command;

    if(command == "SELECT") {
        parse_select(ss);
    } else if(command == "INSERT") {
        // parse_insert(stringstream &input)
    } else if(command == "UPDATE") {
        // parse_update(stringstream &input)
    } else {
        throw std::exception("Command " + command + "Not Known");
    }
}

void parse_select(stringstream &input) {
    string statement;
    input >> statement;
    while (statement != "FROM") {
        // stringstream read_out(statement); 
    }

    string table;
    input >> table;

    if(input >> statement && statement == "WHERE") {
        vector<string> columns;
        vector<::database::Entry> entries;
        
        string column_name;
        while (input >> column_name) {
            columns.emplace_back(column_name);
            input >> statement;
            input >> statement;

            switch(db.get_column_type(table, column_name)) {
                case ::database::Table_Type_BOOL:
                    ::database::Entry *entry = entries.add_entries();
                    entry->set_bool(statement);
                    entries.emplace_back(entry);
                    break;
                
                case ::database::Table_Type_INT:
                    ::database::Entry *entry = entries.add_entries();
                    entry->set_num(statement);
                    entries.emplace_back(entry);
                    break;
                
                case ::database::Table_Type_FLOAT:
                    ::database::Entry *entry = entries.add_entries();
                    entry->set_flt((float)statement);
                    entries.emplace_back(entry);
                    break;
                
                case ::database::Table_Type_STRING:
                    ::database::Entry *entry = entries.add_entries();
                    entry->set_str(statement);
                    entries.emplace_back(entry);
                    break;
                
                default:
                    throw "Column " + column_name + " does not exist!";
                    break;
            }
        }

        // Add specific rows
        vector<::database::Row> rows = db.filter(columns, entries);

        for(int i = 0; i < rows.size(); ++i) {
            
        }
    } else {
        // Add specific rows
        db.output();
    }
}