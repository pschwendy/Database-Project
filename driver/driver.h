// Peter Schwendeman
//
//
// driver.h
//

#ifndef Driver_h
#define Driver_h

#include <iostream>
#include <exception>
#include <sstream>
#include <cassert>
#include <string>
#include "storage/storage.h"
#include "table/table.h"

using namespace std;
//#include "Storage.h"

// Write doc explaining what the project can do
// Test to make sure

class Driver {
    public:
        // TODO: implement with storage system
        Driver() { 
            using_db = false;
        }

        // Gets input and calls functions accordingly
        void run(istream& in, ostream &out);

        // Closes program and tells storage class store data
        void finish() { }

        string preprocess_input(string &input);
        void parse_select(stringstream &input, ostream &out);
        void parse_insert(stringstream &input);
        void parse_delete(stringstream &input);
        void parse_update(stringstream &input);
        void parse_create(stringstream &input);
        void parse_join(stringstream &input, string &statement, ostream& out);
    private:
        // Database* db;
        string db_name;
        bool using_db;
        void print_condition(::database::Condition* condition) {
            cout << " HI ";
            if(condition->has_child()) {
                cout << "( ";
                print_condition(condition->mutable_child());
                cout << " )";
            } else if(condition->has_column()) {
                cout << condition->column() << " ";
                switch(condition->comparator()) {
                    case ::database::Condition::EQUALS:
                        cout << " = ";
                        break;
                    case ::database::Condition::GREATER:
                        cout << " > ";
                        break;
                    case ::database::Condition::LESS:
                        cout << " < ";
                        break;
                    case ::database::Condition::GREATER_EQUAL:
                        cout << " >= ";
                        break;
                    case ::database::Condition::LESS_EQUAL:
                        cout << " <= ";
                        break;
                    case ::database::Condition::NOT_EQUALS:
                        cout << " != ";
                        break;
                    default:
                        cout << "ISSUE";
                        break;
                }
                cout << condition->entry() << " ";
                if(condition->has_next()) {
                    switch(condition->linker()) {
                        case ::database::Condition::AND:
                            cout << " AND ";
                            print_condition(condition->mutable_next());
                        case ::database::Condition::OR:
                            cout << condition->column() << " OR ";
                            print_condition(condition->mutable_next());
                        default:
                            cout << "BAD";
                    }
                }
            }
        }

        void parse_input(string &input, ostream &out);
        void print_entry(::database::Entry &entry, ostream &out);
        void add_entry_to_row(Table &table, string &column_name, string &entry_name, ::database::Row &entries);
        void add_entry_to_row(Table &table, string &column_name, string &entry_name, vector<::database::Entry> &entries);
        void set_entry_value(::database::Entry &entry, string &entry_name, string &column_name, Table &table);
        void construct_conditions_comma(vector<string> &columns, vector<::database::Entry> &entries, string &statement, Table &table);
        void construct_conditions_comma(vector<string> &columns, vector<::database::Entry> &entries, stringstream &input, Table &table);
        void construct_conditions(vector<string> &columns, vector<::database::Entry> &entries, string &statement, Table &table);
        void construct_conditions(vector<string> &columns, vector<::database::Entry> &entries, stringstream &input, Table &table);
        ::database::Condition* read_conditions(stringstream &input, Table &table);
        void read_string(string &str, stringstream& input);
};

#endif // Driver_h