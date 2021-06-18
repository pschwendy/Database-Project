// Peter Schwendeman
//
//
// table.h
//

#ifndef Table_h
#define Table_h

#include <unordered_map>
#include <string>
#include <vector>
#include "protos/table.pb.h"

using namespace std;

// Class for Singular Table in a database
// Allows for insertion, updation, selection, serialization, and output
class Table {
    public:
        // Empty Constructor
        Table() { }

        // Constructor
        // Constructs table given imput rows and columns
        // Input: vector<string> &columns -> table colums, to be sorted in a map
        // Input: vector<string> &column_types -> data types of columns
        // Input: ::database::Table &input_table -> table
        Table(vector<string> &columns, vector<string> &column_types, ::database::Table &input_table);

        // Constructor
        // Constructs table given imput rows and columns
        // Input: vector<Row> input_rows -> rows of new table
        // Input: vector<string> columns -> table colums, to be sorted in a map
        Table(vector<string> &columns, vector<string> &column_types);

        // Returns schema of table in string form
        string schema();

        // Returns first row where Entry@column = comparison
        // Input: string column -> column accessing
        // Input: Entry comparison -> entry to compare row entry to
        ::database::Row get_row(string &column, 
                                    ::database::Entry comparison);

        // Filters and returns rows where each Entry@each column = the said comparison
        // Input: vector<string> columns -> columns being accessed
        // Input: vector<Entry> comparisons -> list of entries to compare each row entry@column to
        vector<::database::Row> filter(vector<string> &columns, 
                                        vector<::database::Entry> &comparisons);
        
        // Finds and edits rows where each entry@each column = the said comparison
        // Changes rows to set entry@each edit_column = the said new entry
        // Input: vector<string> columns -> columns being accessed
        // Input: vector<Entry> comparisons -> list of entries to compare each row entry@column to
        // Input: vector<string> &edit_columns -> columns being edited in filtered entries
        // Input: vector<::database::Entry> &entries -> new entries to update entries in edit_columns
        void edit_rows(vector<string> &columns, 
                        vector<::database::Entry> &comparisons, 
                        vector<string> &edit_columns, 
                        vector<::database::Entry> &entries);

        // Edits all rows to set entry@each edit_column = the said new entry
        // Input: vector<string> &edit_columns -> columns being edited in filtered entries
        // Input: vector<::database::Entry> &entries -> new entries to update entries in edit_columns
        void edit_all(vector<string> &edit_columns, 
                        vector<::database::Entry> &entries);

        // Inserts row into database
        // Checks if row aligns with correct types
        // Input: ::database::row &row -> row being inserted
        void insert(::database::Row &row);
        
        // Removes rows where each entry@each column = the said comparison
        // Input: vector<string> columns -> columns being accessed
        // Input: vector<Entry> comparisons -> list of entries to compare each row entry@column to
        void remove_rows(vector<string> &columns, 
                            vector<::database::Entry> &comparisons);
        
        // Removes all rows in table
        void remove_all() {
            table.mutable_rows()->erase(table.mutable_rows()->begin(), table.mutable_rows()->begin() + table.rows_size());
        }

        // Serializes table to ostream
        // Input: ostream* out -> output ostream
        bool serialize(ostream* out) {
            return table.SerializeToOstream(out);
        }

        // Returns type of column as string given column name
        // Input: string &column -> column name
        string get_type(string &column);

        // Outputs Table row by row, entry by entry
        void output();

        // Outputs given entry
        // Input: ::database::Entry& entry -> entry being output
        void output_entry(::database::Entry& entry);

        // Error caused by mismatch between column and entry through comparison, insertion, or updation
        struct type_mismatch : public std::exception {
            enum error_type {
                comparison = 0,
                insertion = 1,
                updation = 2
            };
            string error_message;

            // Constructs an error given a type of error, column type, and entry type
            // Input: error_type e_type -> error category: comparison, insertion, or updation
            // Input: string column_type -> datatype of column being mismatched
            // Input: string entry_type -> datatype of entry being mismatched
            type_mismatch(error_type e_type, string column_type, string entry_type) {
                switch (e_type) {
                    case 0:
                        error_message = "ERROR: Type Mismatch - Trying to compare Entry of type '" + entry_type + "' into Column of type '" + column_type + "'";
                        break;
                    
                    case 1:
                        error_message = "ERROR: Type Mismatch - Trying to insert Entry of type '" + entry_type + "' into Column of type '" + column_type + "'";
                        break;

                    case 2:
                        error_message = "ERROR: Type Mismatch - Trying to update Column of type '" + column_type + "' with Entry of type '" + entry_type + "'";
                        break;

                    default:
                        error_message = "ERROR: Type Mismatch - Trying to compare Entry of type '" + entry_type + "' into Column of type '" + column_type + "'";
                        break;

                }
            } // type_mismatch()

            // Outputs error message
            const char * what () const throw () {
                return error_message.c_str();
            } // what()
        }; // struct type_mismatch

    private:
        // Info Type
        // Stores column index in row as size_t
        // Stores type of said column as enum
        struct Info {
            size_t index;
            enum types {
                bool_ = 0,
                int_ = 1,
                float_ = 2,
                string_ = 3
            } type;
            
            Info() { }

            // Info Constructor  
            Info(size_t index_in, string& type_str) {
                index = index_in;
                if(type_str == "BOOL" || type_str == "bool") {
                    type = bool_;
                } else if(type_str == "INT" || type_str == "int") {
                    type = int_;
                } else if(type_str == "FLOAT" || type_str == "float") {
                    type = float_;
                } else if(type_str == "STRING" || type_str == "string") {
                    type = string_;
                }
            } // Info()
        }; // struct Info

        unordered_map<string, Info> column_indecies;
        ::database::Table table;

        Info column_index(const string &column);
        
        bool check_row(const ::database::Row &row, vector<Info> indecies, vector<::database::Entry> &comparisons);
        bool compare_entries(const ::database::Entry &lhs, const ::database::Entry &rhs);
        bool correct_type(Info info, const ::database::Entry &entry);
        
        string get_type(Info &info);
        string get_type(::database::Entry entry);
}; // class Table

#endif // Table_h