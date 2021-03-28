// Peter Schwendeman
//
//
// Table.cpp
//

#include "Table.h"
#include <iostream>
#include <exception>

using namespace std;

Table::Table(vector<Row> &input_rows, vector<string> &columns) {
    rows = input_rows;
    for(int i = 0; i < columns.size(); ++i) {
        column_indexes.emplace(columns[i], i);
    }
} // Table()

Row Table::get_row(string &column, Entry comparison) {

} // get_row()

// Filters and returns rows where Entry@column = comparison
// Input: string column -> column accessing
// Input: Entry comparison -> entry to compare row entry to
vector<Row> Table::filter(string &column, Entry comparison) {
    vector<Row> subset;
    auto it = column_indexes.find(column);
    if(it == column_indexes.end()) {
        cout << "ERROR" << endl;
        return;
    }
    size_t index = it->second();
    for(size_t i = 0; i < rows.size(); ++i) {
        if(rows[i][index] == comparison) {
            subset.emplace_back(rows[i]);
        }
    }
    return subset;
} // filter() 1

// Filters and returns rows where each Entry@each column = the said comparison
// Input: vector<string> columns -> columns being accessed
// Input: vector<Entry> comparisons -> list of entries to compare each row entry@column to
vector<Row> Table::filter(vector<string> &columns, vector<Entry> &comparisons) {
    vector<Row> subset;
    vector<size_t> indecies;
    for (string column: columns) {
        auto it = column_indexes.find(column);
        if(it == column_indexes.end()) {
            cout << "ERROR" << endl;
            throw();//some exeption
        }
        size_t index = it->second();
        indecies.push_back(index);
    }
    for(size_t i = 0; i < rows.size(); ++i) {
        bool good = true;
        for(size_t j = 0; j < comparisons.size(); ++j) {
            if(rows[i][indecies[j]] != comparisons[j]) {
                good = false;
            }
        }
        if(good) {
            subset.emplace_back(rows[i]);
        }
    }
    return subset;
} // filter() 2

void Table::edit_row(string &column, Entry comparison, vector<string> &columns, vector<Entry> &entries) {
    auto it = column_indexes.find(column);
    if(it == column_indexes.end()) {
        cout << "ERROR" << endl;
        return;
    }
    size_t index = it->second();
    for(size_t i = 0; i < rows.size(); ++i) {
        if(rows[i][index] != comparison) {
            continue;
        }
        for(size_t j = 0; j < columns.size(); ++i) {
            auto edit_it = column_indexes.find(columns[j]);
            if(edit_it == column_indexes.end()) {
                cout << "ERROR" << endl;
                return;
            }
            size_t edit_index = edit_it.second();
            rows[i][edit_index] = entries[j];
        }
    }
} // edit_row 1