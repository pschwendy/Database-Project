// Peter Schwendeman
//
//
// Table.h
//

#ifndef Table_h
#define Table_h

#include <unordered_map>
#include <string>
#include <vector>
#include "row.pb.h"

using namespace std;

class Table {
    public:
        // Empty Constructor
        Table();

        // Constructor
        // Constructs table given imput rows and columns
        // Input: vector<Row> input_rows -> rows of new table
        // Input: vector<string> columns -> table colums, to be sorted in a map
        Table(vector<::database::Row> &input_rows, vector<string> &columns);

        // Returns first row where Entry@column = comparison
        // Input: string column -> column accessing
        // Input: Entry comparison -> entry to compare row entry to
        Row get_row(string &column, ::database::Entry comparison);

        // Filters and returns rows where Entry@column = comparison
        // Input: string column -> column accessing
        // Input: Entry comparison -> entry to compare row entry to
        vector<Row> filter(string &column, ::database::Entry comparison);

        // Filters and returns rows where each Entry@each column = the said comparison
        // Input: vector<string> columns -> columns being accessed
        // Input: vector<Entry> comparisons -> list of entries to compare each row entry@column to
        vector<Row> filter(vector<string> &columns, vector<::database::Entry> &comparisons);

        // Entry get_entry(string column);

        // Input: string column -> column accessing
        // Input: Entry comparison -> entry to compare row entry to
        void edit_row(string &column, ::database::Entry comparison, vector<string> &columns, vector<Entry> &entries);

        // Input: vector<string> columns -> columns being accessed
        // Input: vector<Entry> comparisons -> list of entries to compare each row entry@column to
        void edit_rows(vector<string> &columns, vector<::database::Entry> &comparisons, vector<string> &columns, vector<::database::Entry> &entries);

        // Input: string &comparison_column ->
        // Input: string column -> column accessing
        // Input: Entry comparison -> entry to compare row entry to
        void edit_row(string &comparison_column, ::database::Entry comparison, string &column, ::database::Entry entry);

        // Input: vector<string> columns -> columns being accessed
        // Input: vector<Entry> comparisons -> list of entries to compare each row entry@column to
        void edit_rows(vector<string> &columns, vector<::database::Entry> &comparisons, string &column, ::database::Entry entry);

    private:
        unordered_map<string, size_t> column_indexes;
        vector<::database::Row> rows;
};

#endif // Table_h