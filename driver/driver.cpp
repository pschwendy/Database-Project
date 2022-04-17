// Peter Schwendeman
//
//
// driver.cpp
//

#include "driver.h"

using namespace std;

/************
 *  PUBLIC  *
 ************/

// Opens shell for input database commands
void Driver::run(istream& in) {
    cout << "...calling read_data" << endl;
    Storage::read_data();
    cout << "...after read_data" << endl;
    string input;
    cout << "# ";
    while(getline(in, input, ';')) {
        cout << "...parsing input" << endl;
        try {
            parse_input(input);
            cout << "# ";
        } catch (exception e) {
            cout << e.what() << endl;
        }
    }
}

/*************
 *  PRIVATE  *
 *************/

void Driver::parse_input(string &input) {
    cout << "...parsing input" << endl;
    stringstream ss(input);

    string command;
    ss >> command;

    // Add "USE Database"

    cout << "...parsing input" << endl;
    if(command == "SELECT" && using_db) {
        parse_select(ss);
    } else if(command == "INSERT" && using_db) {
        parse_insert(ss);
    } else if(command == "UPDATE" && using_db) {
        parse_update(ss);
    } else if(command == "CREATE") {
        cout << "---------CREATING---------" << endl;
        ss >> command;
        if(command == "TABLE" && using_db) {
            string thing = ss.str();
            parse_create(thing);
        } else if(command == "DATABASE") {
            cout << "---------DATABASE---------" << endl;
            ss >> command;
            int i = 0; 
            string database_name = "";
            while(input[i] != ';' && i < command.size()) {
                database_name += command[i];
                ++i;
            }
            Storage::create_database(database_name);
            db_name = database_name;
            using_db = true;
        }
    } if(command == "USE") {
        ss >> command;
        if(command == "DATABASE") {
            ss >> command;
            int i = 0; 
            string database_name = "";
            while(input[i] != ';' && i < command.size()) {
                database_name += command[i];
                ++i;
            }
            db_name = database_name;
            using_db = true;
            if(!Storage::check_database_exists(db_name)) {
                // throw some error
            }
        }
    } else if(!using_db) {
        throw std::out_of_range("Must select a database to use.");
    } else {
        throw std::out_of_range("Command " + command + "Not Known");
    }
}

void Driver::add_entry_to_row(Table &table, string &column_name, string &entry_name, ::database::Row entries) {
    ::database::Entry *entry = entries.add_entries();
    if(column_name == "") {
        return;
    }

    set_entry_value(*entry, entry_name, column_name, table);
}

void Driver::add_entry_to_row(Table &table, string &column_name, string &entry_name, vector<::database::Entry> entries) {
    ::database::Entry entry;
    if(column_name == "") {
        return;
    }

    set_entry_value(entry, entry_name, column_name, table);
    entries.emplace_back(entry);
}

void Driver::set_entry_value(::database::Entry &entry, string &entry_name, string &column_name, Table &table) {
    bool b_value;
    int i_value;
    float f_value;
    stringstream entry_name_ss(entry_name);
    switch(table.column_type(column_name)) {
        case ::database::Table_Type_BOOL:
            entry_name_ss >> b_value;
            entry.set_boolean(b_value);
            break;
        
        case ::database::Table_Type_INT:
            entry_name_ss >> i_value;
            entry.set_num(i_value);
            break;
        
        case ::database::Table_Type_FLOAT:
            entry_name_ss >> f_value;
            entry.set_flt(f_value);
            break;
        
        case ::database::Table_Type_STRING:
            entry.set_str(entry_name);
            break;
        
        default:
            throw std::out_of_range("Column " + column_name + " does not exist!");
            break;
    }
}
// Preproccess input, removing unnecessary spaces
string Driver::preprocess_input(string &input) {
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
        
        if(input[i] == '=' && new_input[new_input.length()-1] == ' ') {
            new_input[new_input.length() - 1] = '=';
            continue;
        
        } else if(new_input[new_input.length()-1] == '=' && input[i] == ' ') {
           continue;
        }
        
        new_input += input[i];
    }

    return new_input;
}

void Driver::parse_select(stringstream &input) {
    bool select_all_columns = false;
    vector<string> select_columns;
    
    string statement;
    input >> statement;

    if(statement == "*") {
        select_all_columns = true;
    }

    for(int i = 0; i < statement.length(); ++i) {
        string select_column;
        while(statement[i] != ',') {
            select_column += statement[i];
            ++i;
        }

        select_columns.emplace_back(select_column);
    }

    input >> statement;
    if(statement != "FROM") {
        throw std::out_of_range("Bad"); // Add nicer error message
    }

    string table_name;
    input >> table_name;
    Table table = Storage::read_table(db_name, table_name);

    if(input >> statement && statement == "WHERE") {
        vector<string> columns;
        vector<::database::Entry> entries;
        
        input >> statement;
        for(int i = 0; i < statement.length(); ++i) {
            string column_name = "";
            string entry_name = "";

            while(statement[i] != '=') {
                column_name += statement[i];
                ++i;
            }
            
            ++i;

            while(statement[i] != ',') {
                if(statement[i] == '"') {
                    ++i;
                    continue;
                }
                entry_name += statement[i];
                ++i;
            }

            add_entry_to_row(table, column_name, entry_name, entries);
        }

        vector<::database::Row> rows;
        if(select_all_columns) {
            rows = table.filter(columns, entries);
        
        } else {
            rows = table.filter(select_columns, columns, entries);
        }

        for(int i = 0; i < rows.size(); ++i) {
            ::database::Row row = rows[i];
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
        //db->output();
    }
}


void Driver::parse_update(stringstream &input) {
    vector<string> select_columns;
    
    string statement;
    
    string table_name;
    input >> table_name;
    Table table = Storage::read_table(db_name, table_name);

    input >> statement;
    if(statement != "SET") {
        throw std::out_of_range("Bad"); // Add nicer error message
    }

    vector<string> edit_columns;
    vector<::database::Entry> edit_entries;
    
    input >> statement;
    construct_columns_and_entries(edit_columns, edit_entries, statement, table);

    if(input >> statement && statement == "WHERE") {
        vector<string> columns;
        vector<::database::Entry> entries;
        
        input >> statement;
        construct_columns_and_entries(columns, entries, statement, table);
        table.edit_rows(edit_columns, edit_entries, columns, entries);
        
    } else {
        table.edit_all(edit_columns, edit_entries);
    }
    Storage::write_table(db_name, table);
}

// INSERT INTO table (col1, col2, ...) VALUES (x1, x2, );
// INSERT INTO table VALUES (x1, x2, ... );
// WORK WITH NULLABLE bool in Info struct for unordered map
void Driver::parse_insert(stringstream &input) {
    vector<string> insert_columns;
    
    string statement;
    input >> statement;

    if(statement != "INTO" || statement != "into") {
        throw std::out_of_range("BAd"); // add nicer
    }
        

    string table_name;
    input >> table_name;
    Table table = Storage::read_table(db_name, table_name);

    input >> statement;

    if(statement != "values" || statement != "VALUES") {
        assert(statement[0] != '(');
        for(int i = 1; i < statement.length(); ++i) {
            string insert_column;
            while(statement[i] != ',' || statement[i] != ')') {
                if(statement[i] == '"') {
                    ++i;
                    continue;
                }
                insert_column += statement[i];
                ++i;
            }

            for(int j = 0; table.column_index(insert_column) + j != insert_columns.size(); ++j) {
                insert_columns.emplace_back("");
            }
            insert_columns.emplace_back(insert_column);
        }
        input >> statement;
        assert(statement != "values" || statement != "VALUES");
    }

    input >> statement;
    assert(statement[0] != '(');
    
    ::database::Row entries;
    int j = 0;
    for(int i = 1; i < statement.length(); ++i) {
        string entry_name;
        while(statement[i] != ',' || statement[i] != ')') {
            if(statement[i] == '"') {
                ++i;
                continue;
            }
            entry_name += statement[i];
            ++i;
        }
        if(insert_columns.size() == 0) {
            add_entry_to_row(table, table.columns()[j], entry_name, entries);
        } else if (insert_columns.size() <= j) {
            // throw
        } else {
            add_entry_to_row(table, insert_columns[j], entry_name, entries);
        }
        
        ++j;
    }

    if(insert_columns.size() == 0) {
        table.insert(entries);
    }
    Storage::write_table(db_name, table);
}

void Driver::parse_delete(stringstream &input) {
    string statement;
    input >> statement;
    if(statement != "FROM") {
        throw std::out_of_range("Bad"); // Add nicer error message
    }

    string table_name;
    input >> table_name;
    Table table = Storage::read_table(db_name, table_name);

    if(input >> statement && statement == "WHERE") {
        vector<string> columns;
        vector<::database::Entry> entries;
        
        input >> statement;
        construct_columns_and_entries(columns, entries, statement, table);
        
        table.remove_rows(columns, entries);
    } else {
        // Add specific rows
        table.remove_all();
    }
    Storage::write_table(db_name, table);
}

void Driver::construct_columns_and_entries(vector<string> &columns, vector<::database::Entry> &entries, string &statement, Table &table) {
    for(int i = 0; i < statement.length(); ++i) {
        string column_name = "";
        string entry_name = "";

        while(statement[i] != '=') {
            column_name += statement[i];
            ++i;
        }
        
        ++i;

        while(statement[i] != ',') {
            if(statement[i] == '"') {
                ++i;
                continue;
            }
            entry_name += statement[i];
            ++i;
        }

        add_entry_to_row(table, column_name, entry_name, entries);
    }
}


void Driver::parse_create(string &input) {
    int i = 0; 
    string table_name = "";
    while(input[i] != '(' && i < input.size()) {
        table_name += input[i];
        ++i;
    }

    vector<string> columns;
    vector<string> types;
    vector<bool> nullable_list;

    enum inserting {
        column = 0,
        type = 1,
        nullable = 2
    } insert_type;

    while(input[i] == ')' && i < input.size()) {
        string sub_input = "";
        bool nullable_column = true;
        
        while((insert_type != inserting::nullable && input[i] != ' ') || input[i] != ',') {
            sub_input += input[i];
        }

        switch(insert_type) {
            case inserting::column:
                columns.emplace_back(sub_input);
                insert_type = static_cast<inserting>(static_cast<int>(insert_type) + 1);
                if(input[i] != ',') {
                    throw out_of_range("Must include column datatype for " + sub_input);
                }
                break;

            case inserting::type:
                types.emplace_back(sub_input);
                if(input[i] != ',') {
                    nullable_list.push_back(nullable_column);
                    insert_type = inserting::column;
                    continue;
                } else {
                    insert_type = static_cast<inserting>(static_cast<int>(insert_type) + 1);
                }
                break;

            case inserting::nullable:
                if(input != "NULL") {
                    nullable_column = false;
                }
                nullable_list.push_back(nullable_column);
                insert_type = inserting::column;
                break;

            default:
                break;
        }
        ++i;
    }
    Table table = Table(table_name, columns, types, nullable_list);

    Storage::create_table(db_name, table);
}