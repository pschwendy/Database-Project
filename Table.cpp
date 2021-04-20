// Peter Schwendeman
//
//
// Table.cpp
//

#include "Table.h"
#include <iostream>
#include <exception>

using namespace std;


/************
 *  PUBLIC  *
 ************/

// Constructor
// Constructs table given imput rows and columns
// Input: vector<Row> input_rows -> rows of new table
// Input: vector<string> columns -> table colums, to be sorted in a map
// Input: ::database::Table &input_table -> table
Table::Table(vector<string> &columns, vector<string> &column_types, ::database::Table &input_table) {
    for(size_t i = 0; i < columns.size(); ++i) {
        Info info = Info(i, column_types[i]);
        column_indecies.emplace(columns[i], info);
    }
    table = input_table;
} // Table()

// Constructor
// Constructs table given imput rows and columns
// Input: vector<Row> input_rows -> rows of new table
// Input: vector<string> columns -> table colums, to be sorted in a map
Table::Table(vector<string> &columns, vector<string> &column_types) {
    for(size_t i = 0; i < columns.size(); ++i) {
        Info info = Info(i, column_types[i]);
        column_indecies.emplace(columns[i], info);
    }
} // Table()

// Returns schema of table in string from
string Table::schema() {
    string result;
    for(auto it : column_indecies) {
        string type_str;
        switch(it->second().type) {
            case 0:
                type_str = "BOOL";
                break;
            case 1:
                type_str = "INT";
                break;
            case 2:
                type_str = "FLOAT";
                break;
            case 3:
                type_str = "STRING";
                break;
        }
        string column = it->first
        result += type_str + " " + column;
    }

    return result;
} // schema()

// Returns first row where Entry@column = comparison
// Input: string column -> column accessing
// Input: Entry comparison -> entry to compare row entry to
::database::Row Table::get_row(string &column, ::database::Entry comparison) {
    size_t index;
    try {
        index = column_index(column);
    } catch (std::exception e) {
        // catch code
        // throw()
    }
    for(size_t i = 0; i < table.rows_size(); ++i) {
        if(compare_entries(table.rows(i).entries(index.index), comparison)) {
            return row;
        }
    }
    // throw ()
} // get_row()

// Filters and returns rows where Entry@column = comparison
// Input: string column -> column accessing
// Input: Entry comparison -> entry to compare row entry to
vector<::database::Row> Table::filter(string &column, ::database::Entry comparison) {
    vector<::database::Row> subset;
    size_t index;
    try {
        index = column_index(column);
    } catch (std::exception e) {
        // catch code
        // throw()
    }
    for(size_t i = 0; i < table.rows_size(); ++i) {
        if(compare_entries(table.rows(i).entries(index.index), comparison)) {
            subset.emplace_back(table.rows(i));
        }
    }
    return subset;
} // filter() 1

// Filters and returns rows where each Entry@each column = the said comparison
// Input: vector<string> columns -> columns being accessed
// Input: vector<Entry> comparisons -> list of entries to compare each row entry@column to
vector<::database::Row> Table::filter(vector<string> &columns, vector<::database::Entry> &comparisons) {
    vector<Row> subset;
    vector<Info> indecies;
    for (string column: columns) {
        Info index;
        try {
            index = column_index(column);
        } catch (std::exception e) {
            // catch code
            // throw()
        }
        indecies.push_back(index);
    }
    for(size_t i = 0; i < table.rows_size(); ++i) {
        bool good = true;
        for(size_t j = 0; j < comparisons.size(); ++j) {
            bool correct_entry = correct_type(indecies[j], table.rows(i).entries(indecies[j].index));
            bool correct_comparison = correct_type(indecies[j], comparisons[j]);
            if(!correct_entry || !correct_comparison) {
                // throw()
            }
            if(!compare_entries(table.rows(i).entries(indecies[j].index), comparisons[j])) {
                good = false;
                j = comparisons.size();
            }
        }
        if(good) {
            subset.emplace_back(table.rows(i));
        }
    }
    return subset;
} // filter() 2

void Table::edit_rows(vector<string> &columns, 
                        vector<::database::Entry> &comparisons, 
                        vector<string> &edit_columns, 
                        vector<::database::Entry> &entries) {
    vector<Info> indecies;
    for (string column: columns) {
        try {
            Info index = column_index(column);
            indecies.push(index)
        } catch (std::exception e) {
            // catch code
            // throw()
        }
    }
    vector<Info> edit_indecies;
    for (string column: edit_columns) {
        try {
            Info index = column_index(column);
            edit_indecies.push(index)
        } catch (std::exception e) {
            // catch code
            // throw()
        }
    }
    for(size_t i = 0; i < table.rows_size(); ++i) {
        bool good = true;
        for(size_t j = 0; j < comparisons.size(); ++j) {
            bool correct_entry = correct_type(indecies[j], table.rows(i).entries(indecies[j].index));
            bool correct_comparison = correct_type(indecies[j], comparisons[j]);
            if(!correct_entry || !correct_comparison) {
                // throw()
            }
            if(!compare_entries(table.rows(i).entries(indecies[j].index), comparisons[j])) {
                good = false;
                j = comparisons.size();
            }
        }
        if(good == false) {
            continue;
        }
        for(size_t j = 0; j < comparisons.size(); ++j) {
            if(!correct_type(edit_indecies[j], entries[j])) {
                // throw()
            }
            table.rows(i).entries(edit_indecies[j].index) = entries[j];
        }
    }
} // edit_rows()

void insert(::database::Row* row) {
    for(auto it : column_indecies) {
        if(!correct_type(it->second(), row.get_entries((it->second()).index)) {
            // throw()
        }
    }
    table.add_rows() = row;
} // insert()

string Table::get_type(string &column) {
    auto it = column_indecies.find(column);
    if(it == column_indecies.end()) {
        // throw()
        cout << "ERROR" << endl;
        return;
    }
    
    string type_str;
    switch(it->second().type) {
        case 0:
            type_str = "BOOL";
            break;
        case 1:
            type_str = "INT";
            break;
        case 2:
            type_str = "FLOAT";
            break;
        case 3:
            type_str = "STRING";
            break;
    }

    return type_str;
}
/*************
 *  PRIVATE  *
 *************/

Info Table::column_index(string &column) {
    auto it = column_indecies.find(column);
    if(it == column_indecies.end()) {
        // throw()
        cout << "ERROR" << endl;
        return;
    }
    return it->second();
} // column_index()

bool Table::compare_entries(::database::Entry &lhs, ::database::Entry &rhs) {
    if (lhs.has_str() && rhs.has_str()) {
        return lhs.str() == rhs.str();
    } else if (lhs.has_flt() && rhs.has_flt()) {
        return lhs.flt() == rhs.flt();
    } else if (lhs.has_num() && rhs.has_num()) {
        return lhs.num() == rhs.num();
    } else if (lhs.has_boolean() && rhs.has_boolean()) {
        return lhs.boolean() == rhs.boolean();
    } else {
        // throw()
    }
} // compare_entries()

bool Table::correct_type(Info info, Entry &entry) {
    switch(info.type) {
        case 0:
            return entry.has_bool();
            break;
        case 1:
            return entry.has_num();
            break;
        case 2:
            return entry.has_flt();
            break;
        case 3:
            return entry.has_str();
            break;
        default:
            return false;
    }
} // correct_type()