// Peter Schwendeman
//
//
// driver.cpp
//

#include "driver.h"
#include <stack>

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
            cout << input << endl;
            parse_input(input);
            cout << "here6" << endl;
        } catch (runtime_error e) {
            cout << "ERROR: " << e.what() << endl;
        } catch (out_of_range e) {
            cout << "ERROR: " << e.what() << endl;
        } catch (Table::type_mismatch e) {
            cout << "ERROR: " << e.what() << endl;
        }
        cout << "# ";
        cout << "here7" << endl;
    }
    cout << "here8" << endl;
} // run()

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
        ss >> command;
        if((command == "TABLE" || command == "table") && using_db) {
            parse_create(ss);
        } else if(command == "DATABASE" || command == "database") {
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
        throw std::runtime_error("Must select a database to use.");
    } else {
        throw std::runtime_error("Command " + command + " not known");
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

    return new_input;
} // preprocess_input()

void Driver::parse_select(stringstream &input) {
    bool select_all_columns = false;
    vector<string> select_columns;
    
    string statement;
    
    input >> statement;
    // cout << "STATEMENT BEFORE SELECT ALL COLUMNS: " << statement << endl;
    select_all_columns = statement == "*";

    if(!select_all_columns) {
        for(int i = 0; i < statement.length(); ++i) {
            if(statement[i] == '.') {
                parse_join(input, statement);
                return;
            } 
        }

        if (statement[statement.length() - 1] == ',' || statement[statement.length() - 1] == ')') {
            statement.pop_back();
            select_columns.emplace_back(statement);
        } else {
            select_columns.emplace_back(statement);
        }

        while(input >> statement) {
            if(select_all_columns) {
                break;
            }
            if (statement[statement.length() - 1] == ',' || statement[statement.length() - 1] == ')') {
                statement.pop_back();
                select_columns.emplace_back(statement);
            } else {
                select_columns.emplace_back(statement);
                break;
            }
        }
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
    cout << "STATEMENT BEFORE BAD: " << statement << endl;
    if(statement != "FROM") {
        throw std::runtime_error("Bad"); // Add nicer error message
    }

    string table_name;
    input >> table_name;
    Table table = Storage::read_table(db_name, table_name);

    if(input >> statement && statement == "WHERE") {
        vector<string> columns;
        vector<::database::Entry> entries;

        // construct_conditions(columns, entries, input, table);
        ::database::Condition top_condition = read_conditions(input, table);
        // cout << "UMMMMMMM" << endl;
        vector<::database::Row> rows;
        if(select_all_columns) {
            rows = table.filter(top_condition);
        } else {
            rows = table.filter(select_columns, top_condition);
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
    construct_conditions_comma(edit_columns, edit_entries, input, table);

    if(input >> statement && statement == "WHERE") {
        // cout << "HELLOOOOOOOOO" << endl;
        vector<string> columns;
        vector<::database::Entry> entries;
        
        // input >> statement;
        // construct_conditions(columns, entries, input, table);
        ::database::Condition top_condition = read_conditions(input, table);
        table.edit_rows(top_condition, edit_columns, edit_entries);
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

    if(statement != "values" && statement != "VALUES") {
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

    table.insert(insert_columns, entries);
    cout << "here4 " << db_name << endl;
    Storage::write_table(db_name, table);
    cout << "here5" << endl;
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
        // construct_conditions(columns, entries, input, table);
        ::database::Condition top_condition = read_conditions(input, table);
        table.remove_rows(top_condition);
    } else {
        // Add specific rows
        table.remove_all();
    }
    Storage::write_table(db_name, table);
}

void Driver::construct_conditions_comma(vector<string> &columns, vector<::database::Entry> &entries, string &statement, Table &table) {
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

void Driver::construct_conditions(vector<string> &columns, vector<::database::Entry> &entries, stringstream &input, Table &table) {
    string statement;
    while(input >> statement) {
        string column_name = "";
        string entry_name = "";
        int i = 0;
        while(statement[i] != '=') {
            column_name += statement[i];
            ++i;
        }
        cout << "COLUMN NAME: " << column_name << endl;
        ++i;

        while(i < statement.length()) {
            if(statement[i] == '"') {
                ++i;
                continue;
            }
            entry_name += statement[i];
            ++i;
        }

        add_entry_to_row(table, column_name, entry_name, entries);
        columns.emplace_back(column_name);
        if(input >> statement) {
            assert(statement == "AND" || statement == "and");
        }
    }
}

void Driver::construct_conditions_comma(vector<string> &columns, vector<::database::Entry> &entries, stringstream &input, Table &table) {
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

// Reads conditions and creates condition node data structure
::database::Condition Driver::read_conditions(stringstream &input, Table &table) {
    stack<::database::Condition> reader;
    string statement;
    while(input >> statement) {
        if(statement[0] == '(') {
            // Push blank condition to stack
            ::database::Condition condition;
            reader.push(condition);

        } else if(statement[0] == ')') {
            // Pop all condition until you reach overarching condition
            ::database::Condition condition;
            while(!reader.top().has_child() && !reader.top().has_column()) {
                condition = reader.top();
                reader.pop();
                reader.top().set_allocated_next(&condition);
            }

            condition = reader.top();
            reader.pop();
            reader.top().set_allocated_child(&condition);

        } else if(statement == "AND") {
            // Set linker of previously read condition
            reader.top().set_linker(::database::Condition_Linker_AND); 

        } else if(statement == "OR") {
            // Set linker of previously read condition
            reader.top().set_linker(::database::Condition_Linker_OR); 
            
        } else {
            cout << statement << endl;
            // Read in specific condition and push to stack
            ::database::Condition condition;
            
            condition.set_column(statement);

            input >> statement;
            switch(statement[0]) {
                case '=':
                    condition.set_comparator(::database::Condition::EQUALS);
                    break;
                case '>':
                    if(statement.size() == 1) {
                        condition.set_comparator(::database::Condition::GREATER);
                    } else if(statement[1] == '=') {
                        condition.set_comparator(::database::Condition::GREATER_EQUAL);
                    }
                    break;
                case '<':
                    if(statement.size() == 1) {
                        condition.set_comparator(::database::Condition::LESS_EQUAL);
                    } else if(statement[1] == '=') {
                        condition.set_comparator(::database::Condition::LESS);
                    }
                    break;
                case '!':
                    if(statement.size() > 1 && statement[1] == '=') {
                        condition.set_comparator(::database::Condition::EQUALS);
                        condition.set_contradiction(!condition.contradiction());
                    }
                    break;
                default:
                    throw runtime_error("Error: Comparator does not exist: " + statement);
            }

            input >> statement;
            if(statement[0] == '"') {
                read_string(statement, input);
            }
            condition.set_entry(statement);
        }
    }
    return reader.top();
} // construct_conditions

void Driver::read_string(string &str, stringstream& input) {
    str.erase(str.begin());
    if(str[str.length()] == '"') {
        str.pop_back();
        return;
    }

    string statement;
    while(input >> statement) {
        str += statement;
        if(str[str.length()] == '"') {
            str.pop_back();
            return;
        }
    }
}

void Driver::parse_create(stringstream &input) {
    string junk;
    string table_name;

    input >> table_name;
    input >> junk;

    vector<string> columns;
    vector<string> types;
    vector<bool> nullable_list;

    string sub_input;
    while(input >> sub_input) {
        if(sub_input == ")") {
            break;
        }

        // insert column
        if(sub_input[sub_input.length() - 1] == ',') {
            throw runtime_error("Must include column datatype for " + sub_input);
        } else if(sub_input[sub_input.length() - 1] == ')') {
            throw runtime_error("Must include column datatype for " + sub_input);
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
       
    }

    Table table = Table(table_name, columns, types, nullable_list);

    Storage::create_table(db_name, table);
}

void Driver::parse_join(stringstream &input, string &statement) {
    unordered_map<string, vector<pair<string, int> > > select_columns_map;

    int index = 0;

    string table = "";
    string column = "";
    bool before_period = true;
    for(int i = 0; i < statement.length(); ++i) {
        if(statement[i] == '.') {
            before_period = false;
            continue;
        }

        if(before_period) {
            table += statement[i];
        } else {
            column += statement[i];
        }
    }

    select_columns_map.insert({ table, vector<pair<string, int> >({{ column, index }}) });

    while(input >> statement) {
        ++index;
        table = "";
        column = "";
        before_period = true;

        for(int i = 0; i < statement.length(); ++i) {
            if(statement[i] == '.') {
                before_period = false;
                continue;
            }

            if(before_period) {
                table += statement[i];
            } else {
                column += statement[i];
            }
        }

        auto it = select_columns_map.find(table);
        if(it == select_columns_map.end()) {
            select_columns_map.insert({ table, vector<pair<string, int> >{{ column, index }} });
        } else {
            (it->second).push_back({ column, index });
        }
    }

    input >> statement;
    cout << "STATEMENT BEFORE BAD: " << statement << endl;
    if(statement != "FROM") {
        throw std::runtime_error("Bad"); // Add nicer error message
    }

    string table_name;
    input >> table_name;
    Table start_table = Storage::read_table(db_name, table_name);

    input >> statement;
    if(statement != "INNER") {
        throw std::runtime_error("Bad"); // Add nicer error message
    }

    input >> statement;
    if(statement != "JOIN") {
        throw std::runtime_error("Bad"); // Add nicer error message
    }

    string compare_table_name;
    input >> table_name;
    Table compare_table = Storage::read_table(db_name, table_name);

    input >> statement;
    if(statement != "ON") {
        throw std::runtime_error("Bad"); // Add nicer error message
    }

    input >> statement;
    string join_column1;
    string join_column2;

    bool table1 = false;
    table = "";
    column = "";
    for(int i = 0; i < statement.length(); ++i) {
        if(statement[i] == '.') {
            before_period = false;
            table1 = table == table_name;
            continue;
        } else if(statement[i] == '=') {
            if(table1) join_column1 = column;
            else join_column2 = column;
        }

        if(before_period) {
            table += statement[i];
        } else {
            column += statement[i];
        }
    }

    if(table1) join_column1 = column;
    else join_column2 = column;

    vector<::database::Row> rows;
    JoinMap<bool> join_map_bool;
    JoinMap<int> join_map_int;
    JoinMap<float> join_map_float;
    JoinMap<string> join_map_string;
    switch(start_table.column_type(join_column1)) {
        case ::database::Table_Type_BOOL:
            join_map_bool = compare_table.map_out<bool>(join_column2);
            rows = start_table.join<bool>(compare_table, join_map_bool, select_columns_map, join_column1);
            break;
        
        case ::database::Table_Type_INT:
            join_map_int = compare_table.map_out<int>(join_column2);
            rows = start_table.join<int>(compare_table, join_map_int, select_columns_map, join_column1);
            break;
        
        case ::database::Table_Type_FLOAT:
            join_map_float = compare_table.map_out<float>(join_column2);
            rows = start_table.join<float>(compare_table, join_map_float, select_columns_map, join_column1);
            break;
        
        case ::database::Table_Type_STRING:
            join_map_string = compare_table.map_out<string>(join_column2);
            rows = start_table.join<string>(compare_table, join_map_string, select_columns_map, join_column1);
            break;
        
        default:
            throw std::out_of_range("Column " + join_column1 + " does not exist!");
            break;
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
}