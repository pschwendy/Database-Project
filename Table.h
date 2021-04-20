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
#include "table.pb.h"

using namespace std;

class Table {
    public:
        // Empty Constructor
        Table();

        // Constructor
        // Constructs table given imput rows and columns
        // Input: vector<Row> input_rows -> rows of new table
        // Input: vector<string> columns -> table colums, to be sorted in a map
        Table(vector<string> &columns, vector<string> &column_types);

        // Returns schema of table in string from
        string schema();

        // Returns first row where Entry@column = comparison
        // Input: string column -> column accessing
        // Input: Entry comparison -> entry to compare row entry to
        ::database::Row get_row(string &column, 
                                    ::database::Entry comparison);

        // Filters and returns rows where Entry@column = comparison
        // Input: string column -> column accessing
        // Input: Entry comparison -> entry to compare row entry to
        vector<::database::Row> filter(string &column, 
                                        ::database::Entry comparison);

        // Filters and returns rows where each Entry@each column = the said comparison
        // Input: vector<string> columns -> columns being accessed
        // Input: vector<Entry> comparisons -> list of entries to compare each row entry@column to
        vector<::database::Row> filter(vector<string> &columns, 
                                        vector<::database::Entry> &comparisons);
        
        // Input: vector<string> columns -> columns being accessed
        // Input: vector<Entry> comparisons -> list of entries to compare each row entry@column to
        void edit_rows(vector<string> &columns, 
                        vector<::database::Entry> &comparisons, 
                        vector<string> &edit_columns, 
                        vector<::database::Entry> &entries);

        // Inserts row into database
        // Checks if row aligns with correct types
        // Input: ::database::row &row -> row being inserted
        void insert(::database::row &row);
        
        // Serializes table to ostream
        // Input: ostream* out -> output ostream
        bool serialize(ostream* out) {
            return table.SerializeToOstream(out);
        }

        // Returns type as string given column name
        // Input: string &column -> column name
        string get_type(string &column);

    private:
        struct Info {
            size_t index;
            enum types {
                bool_ = 0,
                int_ = 1,
                float_ = 2,
                string_ = 3
            } type;
            
            // Info Constructor  
            Info(size_t index_in, string& type_str) {
                index = index_in;
                switch(type_str) {
                    case "Bool" || "bool":
                        type = bool_;
                        break;
                    case "Int" || "int":
                        type = int_;
                        break;
                    case "Float" || "float":
                        type = float_;
                        break;
                    case "String" || "string":
                        type = string_;
                        break;
                    default:
                        break;
                }
            } // Info()
        }; // struct Info

        unordered_map<string, Info> column_indecies;
        ::database::Table table;

        Info column_index(string &column);
        bool compare_entries(::database::Entry &lhs, ::database::Entry &rhs);
        bool correct_type(Info info);
}; // class Table

#endif // Table_h