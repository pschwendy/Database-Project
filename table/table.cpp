// Peter Schwendeman
//
//
// table.cpp
//

#include "table.h"
#include <iostream>
#include <exception>
#include <sstream>
#include <queue>
using namespace std;

/************
 *  PUBLIC  *
 ************/

// Constructor
// Constructs table given imput rows and columns
// Input: vector<string> &columns -> table colums, to be sorted in a map
// Input: vector<string> &column_types -> data types of columns
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
        switch(it.second.type) {
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
        string column = it.first;
        result += type_str + " " + column;
    }

    return result;
} // schema()

// Returns first row where Entry@column = comparison
// Input: string column -> column accessing
// Input: Entry comparison -> entry to compare row entry to
::database::Row Table::get_row(string &column, ::database::Entry comparison) {
    Info index;
    index = column_index(column);
    for(size_t i = 0; i < table.rows_size(); ++i) {
        if(compare_entries(table.rows(i).entries(index.index), comparison)) {
            return table.rows(i);
        }
    }
    throw out_of_range("No row found");
} // get_row()

// Filters and returns rows where each Entry@each column = the said comparison
// Input: vector<string> columns -> columns being accessed
// Input: vector<Entry> comparisons -> list of entries to compare each row entry@column to
vector<::database::Row> Table::filter(vector<string> &columns, vector<::database::Entry> &comparisons) {
    vector<::database::Row> subset;
    vector<Info> indecies;
    
    for (string column : columns) {
        Info index;
        index = column_index(column);
        indecies.push_back(index);
    }
    for(size_t i = 0; i < table.rows_size(); ++i) {
        bool good = check_row(table.rows(i), indecies, comparisons);
        if(good) {
            subset.emplace_back(table.rows(i));
        }
    }
    return subset;
} // filter() 2

// Finds and edits rows where each entry@each column = the said comparison
// Changes rows to set entry@each edit_column = the said new entry
// Input: vector<string> columns -> columns being accessed
// Input: vector<Entry> comparisons -> list of entries to compare each row entry@column to
// Input: vector<string> &edit_columns -> columns being edited in filtered entries
// Input: vector<::database::Entry> &entries -> new entries to update entries in edit_columns
void Table::edit_rows(vector<string> &columns, 
                        vector<::database::Entry> &comparisons, 
                        vector<string> &edit_columns, 
                        vector<::database::Entry> &entries) {
    vector<Info> indecies;
    for (string column : columns) {
        Info index = column_index(column);
        indecies.push_back(index);
    }
    vector<Info> edit_indecies;
    for (string column : edit_columns) {
        Info index = column_index(column);
        edit_indecies.push_back(index);
    }

    queue<size_t> edit_row_indecies;
    // Loops through rows and edits the ones that fit comparisons
    for(size_t i = 0; i < table.rows_size(); ++i) {
        bool good = check_row(table.rows(i), indecies, comparisons);

        if(!good) {
            continue;
        }

        // Edits each specified entry in row
        for(size_t j = 0; j < entries.size(); ++j) {
            if(!correct_type(edit_indecies[j], entries[j])) {
                throw type_mismatch(type_mismatch::error_type::updation, get_type(edit_indecies[j]), get_type(entries[j]));
            }
        }
        edit_row_indecies.push(i);
    }

    // Loops through rows and edits the ones that fit comparisons
    while(!edit_row_indecies.empty()) {
        size_t index = edit_row_indecies.front();
        edit_row_indecies.pop();

        // Edits each specified entry in row
        for(size_t j = 0; j < entries.size(); ++j) {
            ::database::Entry* edit_entry = table.mutable_rows(index)->mutable_entries(edit_indecies[j].index);
            edit_entry->CopyFrom(entries[j]);
        }
    }
} // edit_rows()

// Edits all rows to set entry@each edit_column = the said new entry
// Input: vector<string> &edit_columns -> columns being edited in filtered entries
// Input: vector<::database::Entry> &entries -> new entries to update entries in edit_columns
void Table::edit_all(vector<string> &edit_columns, 
                vector<::database::Entry> &entries) {
    vector<Info> edit_indecies;
    for (string column : edit_columns) {
        Info index = column_index(column);
        edit_indecies.push_back(index);
    }

    for(size_t i = 0; i < table.rows_size(); ++i) {
        // Edits each specified entry in row
        for(size_t j = 0; j < entries.size(); ++j) {
            if(!correct_type(edit_indecies[j], entries[j])) {
                throw type_mismatch(type_mismatch::error_type::updation, get_type(edit_indecies[j]), get_type(entries[j]));
            }
            ::database::Entry* edit_entry = table.mutable_rows(i)->mutable_entries(edit_indecies[j].index);
            edit_entry->CopyFrom(entries[j]);
        }
    }
}

// Inserts row into database
// Checks if row aligns with correct types
// Input: ::database::row &row -> row being inserted
void Table::insert(::database::Row &row) {
    for(auto it : column_indecies) {
        if(it.second.index > row.entries_size() - 1) {
            stringstream error_message;
            error_message << "ERROR: Row being inserted is too small! Row has " << row.entries_size() << " entries, when it is supposed to have " << column_indecies.size();
            throw out_of_range(error_message.str());
        } else if(!correct_type(it.second, row.entries(it.second.index))) {
            cout << "Throwing type mismatch" << endl;
            throw type_mismatch(type_mismatch::error_type::insertion, get_type(row.entries(it.second.index)), get_type(it.second));
        }
    }
    ::database::Row* new_row = table.add_rows();
    *new_row = row;
} // insert()

// Removes rows where each entry@each column = the said comparison
// Input: vector<string> columns -> columns being accessed
// Input: vector<Entry> comparisons -> list of entries to compare each row entry@column to
void Table::remove_rows(vector<string> &columns, vector<::database::Entry> &comparisons) {
    vector<Info> indecies;
    
    for (string column : columns) {
        Info index;
        index = column_index(column);
        indecies.push_back(index);
    }

    auto current_it = table.mutable_rows()->begin();
    auto end_it = table.mutable_rows()->begin() + table.rows_size();
    auto result_it = current_it;

    // "Deletes" or disregards rows that should be removed by moving rows that shouldn't into there places
    // Meanwhile, advances result iterator to be the new end iterator of the table
    while(current_it != end_it) {
        bool should_remove = check_row(*current_it, indecies, comparisons);
        if(!should_remove) {
            if (result_it != current_it) {
                *result_it = move(*current_it);
            }
            ++result_it;
        }
        ++current_it;
    }

    // Erases left over junk rows between new and old end iterators of the table
    table.mutable_rows()->erase(result_it, end_it);
}

// Returns type of column as string given column name
// Input: string &column -> column name
string Table::get_type(string &column) {
    auto it = column_indecies.find(column);
    if(it == column_indecies.end()) {
        throw out_of_range("Column '" + column + "' Does Not Exist!");
    }
    
    string type_str = "";
    switch(it->second.type) {
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

// Outputs Table row by row, entry by entry
void Table::output() {
    for(int i = 0; i < table.rows_size(); ++i) {
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
}

// Outputs given entry
// Input: ::database::Entry& entry -> entry being output
void Table::output_entry(::database::Entry& entry) {
    if(entry.has_str()) {
        cout << entry.str();
    } else if(entry.has_flt()) {
        cout << entry.flt();
    } else if(entry.has_num()) {
        cout << entry.num();
    } else if(entry.has_boolean()) {
        cout << entry.boolean();
    }
    cout << endl;
}

/*************
 *  PRIVATE  *
 *************/

Table::Info Table::column_index(const string &column) {
    auto it = column_indecies.find(column);
    if(it == column_indecies.end()) {
        throw out_of_range("Column '" + column + "' Does Not Exist!");
    }
    return it->second;
} // column_index()

// Loops through all comparisons, checking if row entry@index is equal to the corresponding comparison
// If all checks are good, returns true; else, returns false
bool Table::check_row(const ::database::Row &row, vector<Info> indecies, vector<::database::Entry> &comparisons) {
    bool good = true;
    for(size_t j = 0; j < comparisons.size(); ++j) {
        bool correct_comparison = correct_type(indecies[j], comparisons[j]);
        if(!correct_comparison) {
            throw type_mismatch(type_mismatch::error_type::comparison, get_type(indecies[j]), get_type(comparisons[j]));
        }
        
        if(!compare_entries(row.entries(indecies[j].index), comparisons[j])) {
            good = false;
            break;
        }
    }
    return good;
}

bool Table::compare_entries(const ::database::Entry &lhs, const ::database::Entry &rhs) {
    if (lhs.has_str() && rhs.has_str()) {
        return lhs.str() == rhs.str();
    } else if (lhs.has_flt() && rhs.has_flt()) {
        return lhs.flt() == rhs.flt();
    } else if (lhs.has_num() && rhs.has_num()) {
        return lhs.num() == rhs.num();
    } else if (lhs.has_boolean() && rhs.has_boolean()) {
        return lhs.boolean() == rhs.boolean();
    }
    return false;
} // compare_entries()

bool Table::correct_type(Info info, const ::database::Entry &entry) {
    switch(info.type) {
        case 0:
            return entry.has_boolean();
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

string Table::get_type(Info &info) {
    switch(info.type) {
        case 0:
            return "BOOL";
            break;
        case 1:
            return "INT";
            break;
        case 2:
            return "FLOAT";
            break;
        case 3:
            return "STRING";
            break;
    }
    return "NO TYPE";
} // get_type()

string Table::get_type(::database::Entry entry) {
    if(entry.has_boolean()) {
        return "BOOLEAN";
    } else if(entry.has_num()) {
        return "INT";
    } else if(entry.has_flt()) {
        return "FLOAT";
    } else if(entry.has_str()) {
        return "STRING";
    }
    return "NO TYPE";
} // get_type()