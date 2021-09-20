// Peter Schwendeman
//
//
// driver.cpp
//

#include "driver.h"
#include <iostream>
#include <exception>
#include <sstream>
#include <cassert>

using std::cout, std::cin, std::exception, std::string;


/************
 *  PUBLIC  *
 ************/

// Opens shell for input database commands
void run() {
    string input;
    cout << "#" << endl;
    while(getline(cin, input, ";")) {
        try {
            parse_input(input);
        } catch (exception e) {
            cout << e.what() << endl;
        }
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
        parse_insert(ss);
    } else if(command == "UPDATE") {
        // parse_update(stringstream &input)
    } else {
        throw std::exception("Command " + command + "Not Known");
    }
}

::database::Entry add_entry_to_row(string &table, string &column_name, string &entry_name, ::database::Row entries) {
    if(column_name == "") {
        ::database::Entry *entry = entries.add_entries();
        entries.emplace_back(entry);
        return;
    }

    switch(db.get_column_type(table, column_name)) {
        case ::database::Table_Type_BOOL:
            ::database::Entry *entry = entries.add_entries();

            bool value;
            stringstream entry_name_ss(entry_name);
            entry_name_ss >> value;

            entry->set_bool(value);
            entries.emplace_back(entry);
            break;
        
        case ::database::Table_Type_INT:
            ::database::Entry *entry = entries.add_entries();

            int value;
            stringstream entry_name_ss(entry_name);
            entry_name_ss >> value;

            entry->set_num(value);
            entries.emplace_back(entry);
            break;
        
        case ::database::Table_Type_FLOAT:
            ::database::Entry *entry = entries.add_entries();

            float value;
            stringstream entry_name_ss(entry_name);
            entry_name_ss >> value;

            entry->set_flt(value);
            entries.emplace_back(entry);
            break;
        
        case ::database::Table_Type_STRING:
            ::database::Entry *entry = entries.add_entries();
            entry->set_str(entry_name);
            entries.emplace_back(entry);
            break;
        
        default:
            throw std::exception("Column " + column_name + " does not exist!");
            break;
    }
}
// Preproccess input, removing unnecessary spaces
string preprocess_input(string &input) {
    bool remove_space = false;
    string new_input = "";
    for(int i = 0; i < input.length(); ++i) {
        if(remove_space && input[i] == ' ') {
            continue;

        } else if(remove_space && input[i] != ' ') {
            remove_space = false;

        } else if(!remove_space && input[i] == ',') {
            remove_space = true;

        } else if(!remove_space && input[i] == ' ') {
            remove_space = true;
        }

        new_input += input[i];
    }

    return new_input;
}

void parse_select(stringstream &input) {
    bool select_all_columns = false;
    vector<string> select_columns;
    
    string statement;
    input >> statement;

    if(statement == "*") {
        select_all_columns = true;
    }

    for(int i = 0; i < statement.length(), ++i) {
        string select_column;
        while(input[i] != ',') {
            select_column += input[i];
            ++i;
        }

        select_column.emblace_back(select_column);
    }

    input >> statement;
    if(statement != "FROM") {
        throw std::exception("Bad"); // Add nicer error message
    }

    string table;
    input >> table;

    if(input >> statement && statement == "WHERE") {
        vector<string> columns;
        vector<::database::Entry> entries;
        
        input >> statement;
        for(int i = 0; i < statement.length(), ++i) {
            string column_name = "";
            string entry_name = "";

            while(input[i] != '=') {
                column_name += input[i];
                ++i;
            }
            
            ++i;

            while(input[i] != ',') {
                entry_name += input[i];
                ++i;
            }

            add_entry_to_row(table, column_name, entry_name, entries);
        }

        
        if(select_all_columns) {
            vector<::database::Row> rows = db.select(table, columns, entries);
        
        } else {
            vector<::database::Row> rows = db.select_columns(table, select_columns, columns, entries);
        }

        for(int i = 0; i < rows.size(); ++i) {
            ::database::Row row = table.rows(i);
            for(int j = 0; j < row.entries_size(); ++j) {
                ::database::Entry entry = row.entries(j);
                if(entry.has_str()) {
                    cout << entry.str();
                } else if(entry.has_flt()) {
                    cout << entry.flt();
                } else if(entry.has_num()) {
                    cout << entry.num();
                } else if(entry.has_boolean()) {
                    cout << entry.boolean();
                }
                cout << " | ";
            }
            cout << endl;
        }
    } else {
        // Add specific rows
        db.output();
    }
}

// INSERT INTO table (col1, col2, ...) VALUES (x1, x2, );
// INSERT INTO table VALUES (x1, x2, ... );
// WORK WITH NULLABLE bool in Info struct for unordered map
void parse_insert(stringstream &input) {
    vector<string> insert_columns;
    
    string statement;
    input >> statement;

    if(statement != "INTO" || statement != "into") {
        throw std:exception("BAd"); // add nicer
    }
        

    string table;
    input >> table;

    input >> statement;

    if(statement != "values" || statement != "VALUES") {
        assert(statement[0] != '(');
        for(int i = 1; i < statement.length(), ++i) {
            string insert_column;
            while(input[i] != ',' || input[i] != ')') {
                insert_column += input[i];
                ++i;
            }

            for(int j = 0; db.column_index(insert_column) + j != insert_columns.size(); ++j) {
                insert_columns.emplace_back("");
            }
            insert_columns.emblace_back(insert_column);
        }
        input >> statement;
        assert(statement != "values" || statement != "VALUES");
    }

    input >> statement;
    assert(statement[0] != '(');
    
    ::database::Row entries;
    int j = 0;
    for(int i = 1; i < statement.length(), ++i) {
        string entry_name;
        while(input[i] != ',' || input[i] != ')') {
            entry_name += input[i];
            ++i;
        }
        if(insert_columns.size() == 0) {
            add_entry_to_row(table, db.get_columns(table)[j], entry_name, entries);
        } else if (insert_columns.size() <= j) {
            // throw
        } else {
            add_entry_to_row(table, insert_columns[j], entry_name, entries);
        }
        
        ++j;
    }

    if(insert_columns.size() == 0) {
        db.insert(table, entries);
    }
}

