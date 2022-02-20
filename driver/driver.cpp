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
    Storage::read_data();
    string input;
    cout << "# ";
    while(getline(in, input, ';')) {
        try {
            input = preprocess_input(input);
            parse_input(input);
        } catch (out_of_range e) {
            cout << "ERROR: " << e.what() << endl;
        }
        cout << "# ";
    }
}

/*************
 *  PRIVATE  *
 *************/

void Driver::parse_input(string &input) {
    stringstream ss(input);

    string command;
    ss >> command;

    if((command == "SELECT" || command == "select") && using_db) {
        parse_select(ss);
    } else if((command == "INSERT" || command == "insert") && using_db) {
        parse_insert(ss);
    } else if((command == "UPDATE" || command == "update") && using_db) {
        parse_update(ss);
    } else if((command == "DELETE" || command == "delete") && using_db) {
        parse_delete(ss);
    } else if((command == "CREATE" || command == "create")) {
        // cout << "---------CREATING---------" << endl;
        ss >> command;
        // cout << command << endl;
        if((command == "TABLE" || command == "table") && using_db) {
            // cout << "---------TABLE---------" << endl;
            parse_create(ss);
        } else if(command == "DATABASE" || command == "database") {
            // cout << "---------DATABASE---------" << endl;
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
    } else if(command == "USE" || command == "use") {
        ss >> command;
        if(command == "DATABASE" || command == "database") {
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
        throw std::out_of_range("Command " + command + " not known");
    }
}

void Driver::add_entry_to_row(Table &table, string &column_name, string &entry_name, ::database::Row &entries) {
    ::database::Entry *entry = entries.add_entries();
    if(column_name == "") {
        return;
    }

    set_entry_value(*entry, entry_name, column_name, table);
}

void Driver::add_entry_to_row(Table &table, string &column_name, string &entry_name, vector<::database::Entry> &entries) {
    ::database::Entry entry;
    if(column_name == "") {
        return;
    }

    set_entry_value(entry, entry_name, column_name, table);
    entries.emplace_back(entry);
}

void Driver::set_entry_value(::database::Entry &entry, string &entry_name, string &column_name, Table &table) {
    // cout << "USING COLUMN NAME—--" << column_name << "---to set entry value" << endl;
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
    // cout << "SET ENTRY VALUE" << endl;
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

        } else if(!remove_space && input[i] == ' ') {
            remove_space = true;
        } else if(new_input.length() - 1 >= 0 && input[i] != ' ' && new_input[new_input.length()-1] == ',') {
            new_input += ' ';
        }   
        
        if(input[i] == '=' && new_input[new_input.length()-1] == ' ') {
            new_input[new_input.length() - 1] = '=';
            remove_space = true;
            continue;
        
        } else if(input[i] == '(') {
            if(new_input[new_input.length()-1] != ' ')
                new_input += " ";
            new_input += input[i];
            new_input += " ";
            remove_space = true;
            continue;
        }
        
        new_input += input[i];
    }

    cout << new_input << endl;
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

    while(!select_all_columns && input >> statement) {
        //string select_column;
        /*for(int i = 0; statement[i] != ','; ++i) {
            select_column += statement[i];
        }*/
        if (statement[statement.length() - 1] == ',' || statement[statement.length() - 1] == ')') {
            statement.pop_back();
        }
        select_columns.emplace_back(statement);
    }
/*
    for(int i = 0; i < statement.length(); ++i) {
        string select_column;
        while(statement[i] != ',') {
            select_column += statement[i];
            ++i;
        }

        select_columns.emplace_back(select_column);
    }
*/
    input >> statement;
    // cout << "HELLO: " << statement << endl;
    if(statement != "FROM") {
        throw std::runtime_error("Bad"); // Add nicer error message
    }

    string table_name;
    input >> table_name;
    Table table = Storage::read_table(db_name, table_name);

    if(input >> statement && statement == "WHERE") {
        vector<string> columns;
        vector<::database::Entry> entries;

        construct_columns_and_entries(columns, entries, input, table);
        // cout << "UMMMMMMM" << endl;
        vector<::database::Row> rows;
        if(select_all_columns) {
            rows = table.filter(columns, entries);
        
        } else {
            rows = table.filter(select_columns, columns, entries);
        }
        // cout << "UHHHHH" << endl;
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
        ::database::Table rows = table.filter_all();
        for(int i = 0; i < rows.rows_size(); ++i) {
            ::database::Row row = rows.rows(i);
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
    
    //input >> statement;
    // cout << "HELLOOOOOOOOO1" << endl;
    construct_columns_and_entries(edit_columns, edit_entries, input, table);

    if(input >> statement && statement == "WHERE") {
        // cout << "HELLOOOOOOOOO" << endl;
        vector<string> columns;
        vector<::database::Entry> entries;
        
        // input >> statement;
        construct_columns_and_entries(columns, entries, input, table);
        table.edit_rows(columns, entries, edit_columns, edit_entries);
        // cout << "DONEEEEEEEEE" << endl;
    } else {
        table.edit_all(edit_columns, edit_entries);
    }
    ::database::Table rows = table.filter_all();
    for(int i = 0; i < rows.rows_size(); ++i) {
        ::database::Row row = rows.rows(i);
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
    Storage::write_table(db_name, table);
}

// INSERT INTO table (col1, col2, ...) VALUES (x1, x2, );
// INSERT INTO table VALUES (x1, x2, ... );
// WORK WITH NULLABLE bool in Info struct for unordered map
void Driver::parse_insert(stringstream &input) {
    vector<string> insert_columns;
    vector<::database::Entry> entries;
    
    string statement;
    input >> statement;

    if(statement != "INTO" && statement != "into") {
        throw std::out_of_range("BAd"); // add nicer
    }
        

    string table_name;
    input >> table_name;
    Table table = Storage::read_table(db_name, table_name);

    input >> statement;

    if(statement != "values" || statement != "VALUES") {
        assert(statement == "(");
        bool end_loop = false;
        // cout << "THE FIRST STATEMENT: " << statement << endl;
        while(!end_loop && input >> statement) {
            // cout << "THE STATEMENT: " << statement << endl;
            if(statement[statement.length() - 1] == ',') {
                statement.pop_back();
            } else if(statement[statement.length() - 1] == ')') {
                // cout << "UMMMM" << endl;
                statement.pop_back();
                end_loop = true;
            }
            // cout << "HIIII" << endl;
            bool entry_is_string = statement[0] == '"' && statement[statement.length() - 1] == '"';
            if(entry_is_string) {
                statement.erase(statement.begin());
                statement.pop_back();
            }

            insert_columns.emplace_back(statement);
        }

        input >> statement;
    }

    input >> statement;
    // cout << statement << endl;
    // cout << "COLUMNS SIZE: " << insert_columns.size() << endl;

    for(int i = 0; i < insert_columns.size(); ++i) {
        input >> statement;
        string entry_name;
        for(int j = 0; statement[j] != ',' && statement[j] != ')'; ++j) {
            if(statement[j] == '"') {
                continue;
            }
            entry_name += statement[j];
        }
        // cout << "ENTRY NAME: " << entry_name << endl;
        add_entry_to_row(table, insert_columns[i], entry_name, entries);
    }

    // if(insert_columns.size() == 0) { }
    cout << "here" << endl;
    table.insert(insert_columns, entries);
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
        
        // input >> statement;
        construct_columns_and_entries(columns, entries, input, table);
        
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
        columns.emplace_back(column_name);
    }
}

void Driver::construct_columns_and_entries(vector<string> &columns, vector<::database::Entry> &entries, stringstream &input, Table &table) {
    string statement;
    bool stop = false;
    while(!stop && input >> statement) {
        if(statement[statement.length() - 1] != ',') {
            stop = true;
        }
        string column_name = "";
        string entry_name = "";
        int i = 0;
        while(statement[i] != '=') {
            column_name += statement[i];
            ++i;
        }
        cout << "COLUMN NAME: " << column_name << endl;
        ++i;

        while(statement[i] != '=') {
            if(statement[i] == '"') {
                ++i;
                continue;
            }
            entry_name += statement[i];
            ++i;
        }

        add_entry_to_row(table, column_name, entry_name, entries);
        columns.emplace_back(column_name);
    }
}


void Driver::parse_create(stringstream &input) {
    // cout << "IN HERE" << endl;
    string junk;
    string table_name;

    input >> table_name;
    // cout << "TABLE NAME: " << table_name << endl;
    input >> junk;

    vector<string> columns;
    vector<string> types;
    vector<bool> nullable_list;

    /*enum inserting {
        column = 0,
        type = 1,
        nullable = 2
    } insert_type;*/

    // input.str()[i] == ')' && i < input.str().size()
    string sub_input;
    while(input >> sub_input) {
        // insert column
        if(sub_input[sub_input.length() - 1] == ',') {
            throw out_of_range("Must include column datatype for " + sub_input);
        } else if(sub_input[sub_input.length() - 1] == ')') {
            throw out_of_range("Must include column datatype for " + sub_input);
        }
        columns.emplace_back(sub_input);

        // insert type
        input >> sub_input;
        if(sub_input[sub_input.length() - 1] == ',') {
            nullable_list.push_back(true);
            string removed_comma = "";
            for(int i = 0; sub_input[i] != ','; ++i) {
                removed_comma += sub_input[i];
            }
            columns.emplace_back(removed_comma);
            continue;
        } else if(sub_input[sub_input.length() - 1] == ')') {
            nullable_list.push_back(true);
            string removed_comma = "";
            for(int i = 0; sub_input[i] != ','; ++i) {
                removed_comma += sub_input[i];
            }
            types.emplace_back(removed_comma);
            break;
        }
        types.emplace_back(sub_input);

        // insert type
        input >> sub_input;
        if(sub_input[sub_input.length() - 1] == ',') {
            nullable_list.push_back(true);
        } else if(sub_input[sub_input.length() - 1] == ')') {
            nullable_list.push_back(true);
            break;
        } else {
            nullable_list.push_back(false);
            input >> sub_input;
        }
       

        /*while((insert_type != inserting::nullable && input.str()[i] != ' ') || input.str()[i] != ',') {
            sub_input += input.str()[i];
        }*/
        /*
        if(sub_input[sub_input.length() - 1] == ',') {
            junk = "";
            for(int i = 0; i < sub_input.length(); ++i) {
                junk += sub_input;
            }
            switch(insert_type) {
                case inserting::column:
                    throw out_of_range("Must include column datatype for " + sub_input);
                    break;
                case inserting::type:
                    columns.emplace_back(junk);
                    nullable_list.push_back(nullable_column);
                    insert_type = inserting::column;
                    continue;
                    break;

                case inserting::nullable:
                    if( != "NULL") {
                        nullable_column = false;
                    }
                    nullable_list.push_back(nullable_column);
                    insert_type = inserting::column;
                    break;
            }
        }

        switch(insert_type) {
            case inserting::column:
                columns.emplace_back(sub_input);
                insert_type = static_cast<inserting>(static_cast<int>(insert_type) + 1);
                break;

            case inserting::type:
                types.emplace_back(sub_input);
                insert_type = static_cast<inserting>(static_cast<int>(insert_type) + 1);
                break;

            default:
                break;
        }
        ++i;*/
    }

    /* for (int i = 0; i < columns.size(); ++i) {
        cout << columns[i] << " " << types[i] << " " << nullable_list[i] << endl;
    } */

    Table table = Table(table_name, columns, types, nullable_list);

    Storage::create_table(db_name, table);
}