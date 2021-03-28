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
Table::Table(vector<::database::Row> &input_rows, vector<string> &columns) {
    rows = input_rows;
    for(int i = 0; i < columns.size(); ++i) {
        column_indecies.emplace(columns[i], i);
    }
} // Table()

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
    for(size_t i = 0; i < rows.size(); ++i) {
        if(compare_entries(rows[i].entries(index), comparison)) {
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
    for(size_t i = 0; i < rows.size(); ++i) {
        if(compare_entries(rows[i].entries(index), comparison)) {
            subset.emplace_back(rows[i]);
        }
    }
    return subset;
} // filter() 1

// Filters and returns rows where each Entry@each column = the said comparison
// Input: vector<string> columns -> columns being accessed
// Input: vector<Entry> comparisons -> list of entries to compare each row entry@column to
vector<::database::Row> Table::filter(vector<string> &columns, vector<::database::Entry> &comparisons) {
    vector<Row> subset;
    vector<size_t> indecies;
    for (string column: columns) {
        size_t index;
        try {
            index = column_index(column);
        } catch (std::exception e) {
            // catch code
            // throw()
        }
        indecies.push_back(index);
    }
    for(size_t i = 0; i < rows.size(); ++i) {
        bool good = true;
        for(size_t j = 0; j < comparisons.size(); ++j) {
            if(!compare_entries(rows[i].entries(indecies[j]), comparisons[j])) {
                good = false;
                j = comparisons.size();
            }
        }
        if(good) {
            subset.emplace_back(rows[i]);
        }
    }
    return subset;
} // filter() 2

void Table::edit_rows(vector<string> &columns, vector<::database::Entry> &comparisons, vector<string> &edit_columns, vector<::database::Entry> &entries) {
    vector<size_t> indecies;
    for (string column: columns) {
        try {
            size_t index = column_index(column);
            indecies.push(index)
        } catch (std::exception e) {
            // catch code
            // throw()
        }
    }
    vector<size_t> edit_indecies;
    for (string column: edit_columns) {
        try {
            size_t index = column_index(column);
            edit_indecies.push(index)
        } catch (std::exception e) {
            // catch code
            // throw()
        }
    }
    for(size_t i = 0; i < rows.size(); ++i) {
        bool good = true;
        for(size_t j = 0; j < comparisons.size(); ++j) {
            if(!compare_entries(rows[i].entries(indecies[j]), comparisons[j])) {
                good = false;
                j = comparisons.size();
            }
        }
        if(good == false) {
            continue;
        }
        for(size_t j = 0; j < comparisons.size(); ++j) {
            rows[i].entries(edit_indecies[j]) = entries[j];
        }
    }
} // edit_rows()


/*************
 *  PRIVATE  *
 *************/

size_t Table::column_index(string &column) {
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