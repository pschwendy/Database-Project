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
#include <google/protobuf/util/message_differencer.h>
using namespace std;

/************
 *  PUBLIC  *
 ************/

// Constructor
// Constructs table given imput rows and columns
// Input: vector<string> &columns -> table colums, to be sorted in a map
// Input: vector<string> &column_types -> data types of columns
// Input: ::database::Table &input_table -> table
Table::Table(string &tb_name, vector<string> &columns, vector<string> &column_types, vector<bool> &nullable_list, ::database::Table &input_table) {
    table_name = tb_name;
    for(size_t i = 0; i < columns.size(); ++i) {
        Info info = Info(i, column_types[i], nullable_list[i]);
        column_indecies.insert({columns[i], info});
    }
    table = input_table;
} // Table()

// Constructor
// Constructs table given imput rows and columns
// Input: vector<string> &columns -> table colums, to be sorted in a map
// Input: vector<string> &column_types -> data types of columns
// Input: ::database::Table &input_table -> table
Table::Table(string &tb_name, vector<string> &columns, vector<string> &column_types, vector<bool> &nullable_list, vector<int> &indecies, ::database::Table &input_table) {
    table_name = tb_name;
    for(size_t i = 0; i < columns.size(); ++i) {
        Info info = Info(indecies[i], column_types[i], nullable_list[i]);
        column_indecies.insert({columns[i], info});
    }
    table = input_table;
} // Table()

// Constructor
// Constructs table given imput rows and columns
// Input: vector<string> &columns -> table colums, to be sorted in a map
// Input: vector<string> &column_types -> data types of columns
// Input: ::database::Table &input_table -> table
Table::Table(string &tb_name, vector<string> &columns, vector<string> &column_types, vector<bool> &nullable_list) {
    // cout << "here1" << endl;
    table_name = tb_name;
    for(size_t i = 0; i < columns.size(); ++i) {
        // cout << "here1" << endl;
        Info info = Info(i, column_types[i], nullable_list[i]);
        column_indecies.insert({columns[i], info});
    }
    /*for(auto it : column_indecies) {
        cout << Table_Type_Name(it.second.type) << " " << it.first;
    }*/
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
    // ADD NULLABLE ROWS
    stringstream result;
    for(auto it : column_indecies) {
        string type_str;
        string column = it.first;
        result << Table_Type_Name(it.second.type) << " " << column;
        if(it.second.nullable) {
            result << " NULL ";
        } else {
            result << " NOT NULL ";
        }
        result << it.second.index << "\n";
    }

    return result.str();
} // schema()

// Returns first row where Entry@column = comparison
// Input: string column -> column accessing
// Input: Entry comparison -> entry to compare row entry to
::database::Row Table::get_row(string &column, ::database::Entry comparison) {
    Info index;
    index = column_info(column);
    for(size_t i = 0; i < table.rows_size(); ++i) {
        if(google::protobuf::util::MessageDifferencer::Equals(table.rows(i).entries(index.index), comparison)) {
            return table.rows(i);
        }
    }
    throw out_of_range("No row found");
} // get_row()


// Filters and returns rows where each Entry@each column = the said comparison
// Input: vector<string> columns -> columns being accessed
// Input: vector<Entry> comparisons -> list of entries to compare each row entry@column to
::database::Table& Table::filter_all() {
    return table;
} // filter()

// Filters and returns rows where each Entry@each column = the said comparison
// Input: vector<string> columns -> columns being accessed
// Input: vector<Entry> comparisons -> list of entries to compare each row entry@column to
vector<::database::Row> Table::filter(vector<string> &columns, vector<::database::Entry> &comparisons) {
    vector<::database::Row> subset;
    vector<Info> indecies;
    // cout << columns.size() << endl;
    
    for (string column : columns) {
        // cout << "THE COLUMN: " << column << endl;
        Info index;
        index = column_info(column);
        indecies.push_back(index);
    }
    for(size_t i = 0; i < table.rows_size(); ++i) {
        bool good = check_row(table.rows(i), indecies, comparisons);
        if(good) {
            subset.emplace_back(table.rows(i));
        }
    }
    return subset;
} // filter()

// Filters and returns rows where Condition set is met
vector<::database::Row> Table::filter(::database::Condition &top_condition) {
    vector<::database::Row> subset;

    for(size_t i = 0; i < table.rows_size(); ++i) {
        bool good = check_row(table.rows(i), top_condition);
        if(good) {
            subset.emplace_back(table.rows(i));
        }
    }
    return subset;
} // filter()

// Filters and returns rows where each Entry@each column = the said comparison
// Input: vector<string> columns -> columns being accessed
// Input: vector<Entry> comparisons -> list of entries to compare each row entry@column to
vector<::database::Row> Table::filter(vector<string> select_columns, vector<string> &columns, vector<::database::Entry> &comparisons) {
    vector<::database::Row> subset;
    vector<Info> indecies;
    vector<Info> return_entries;
    
    for (string column : columns) {
        Info index;
        index = column_info(column);
        indecies.push_back(index);
    }

    for (string column : select_columns) {
        Info index;
        index = column_info(column);
        return_entries.push_back(index);
    }

    for(size_t i = 0; i < table.rows_size(); ++i) {
        bool good = check_row(table.rows(i), indecies, comparisons);
        if(good) {
            // ASK ASH IF THIS IS POSSIBLE/FEASIBLE
            ::database::Row row;
            for(Info info: return_entries) {
                ::database::Entry *entry = row.add_entries();
                entry->CopyFrom(table.rows(i).entries(info.index));
            }
            subset.emplace_back(row);
        }
    }
    return subset;
} // filter() 2

// Filters and returns specified rows where condition set is met
vector<::database::Row> Table::filter(vector<string> &select_columns, ::database::Condition &top_condition) {
    vector<::database::Row> subset;
    vector<Info> return_entries;

    for (string column : select_columns) {
        Info index;
        index = column_info(column);
        return_entries.push_back(index);
    }

    for(size_t i = 0; i < table.rows_size(); ++i) {
        bool good = check_row(table.rows(i), top_condition);
        if(good) {
            // ASK ASH IF THIS IS POSSIBLE/FEASIBLE
            ::database::Row row;
            for(Info info: return_entries) {
                ::database::Entry *entry = row.add_entries();
                entry->CopyFrom(table.rows(i).entries(info.index));
            }
            subset.emplace_back(row);
        }
    }
    return subset;
} // filter() 2


// Maps out joining entry to rows
template <typename T>
JoinMap<T> Table::map_out(string &column) {
    JoinMap<T> join_map;
    Info joining_info = column_info(column);

    for(size_t i = 0; i < table.rows_size(); ++i) {
        join_map.insert({ get_value<T>(table.rows(i).entries(joining_info.index)), i });
    }
    return join_map;
}

// CAN YOU USE AN ENTRY AS A KEY?
// Joins table specific entries with mapped out rows
template <typename T>
// Orders.OrderID, Customers.CustomerName, Orders.OrderDate
vector<::database::Row> Table::join(Table& table_compare, 
                                JoinMap<T> &join_map,
                                unordered_map<string, vector<pair<string, int> > > select_columns_map,
                                string &column) {
    // = table_compare.map_out<T>(column);
    
    vector<::database::Row> subset;
    int joining_index = column_index(column);
    
    auto local_select_columns_it = select_columns_map.find(table_name);
    if(local_select_columns_it == select_columns_map.end()) {
        // throw
    }
    vector<pair<string, int> > select_columns = local_select_columns_it->second;

    
    auto compare_select_columns_it = select_columns_map.find(table_name);
    if(local_select_columns_it == select_columns_map.end()) {
        // throw
    }
    vector<pair<string, int> > select_columns_compare = local_select_columns_it->second;

    // Get index of placement w/in old column and new 
    vector<pair<Info, int> > join_placements;
    for (pair<string, int> paired_column : select_columns) {
        Info index;
        index = column_info(paired_column.first);
        join_placements.push_back({ index, paired_column.second });
    }

    vector<pair<Info, int> > join_placements_compare;
    for (pair<string, int> paired_column : select_columns_compare) {
        Info index;
        index = column_info(paired_column.first);
        join_placements_compare.push_back({ index, paired_column.second });
    }

    for(size_t i = 0; i < table.rows_size(); ++i) {
        auto it = join_map.find(table.rows(i).entries(joining_index));
        if(it == join_map.end()) continue;

        // Create new row and add correct amount of entries to it
        ::database::Row row = ::database::Row();
        for(pair<Info, int> placement_info: join_placements_compare) {
            row.add_entries();
        }

        for(pair<Info, int> placement_info: join_placements) {
            row.add_entries();
        }

        // Input entries at selected columns in their proper placements
        for(pair<Info, int> placement_info: join_placements_compare) {
            ::database::Entry* entry = row.mutable_entries(placement_info.second);
            entry->CopyFrom(table_compare.get_row(i).entries(placement_info.first.index));
        }

        for(pair<Info, int> placement_info: join_placements) {
            ::database::Entry* entry = row.mutable_entries(placement_info.second);
            entry->CopyFrom(table.rows(i).entries(placement_info.first.index));
        }

        // Push newly created row to the "join" subset
        subset.emplace_back(row);
    }

    return subset;
}

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
    cout << "           SIZES          " << endl;
    cout << "---------------------------" << endl;
    cout << "COLUMNS: " << columns.size() << endl;
    cout << "COMPARISONS: " << comparisons.size() << endl;
    cout << "EDIT COLUMNS: " << edit_columns.size() << endl;
    cout << "ENTRIES: " << entries.size() << endl;
    cout << "---------------------------" << endl;
    vector<Info> indecies;
    for (string column : columns) {
        Info index = column_info(column);
        indecies.push_back(index);
    }
    vector<Info> edit_indecies;
    for (string column : edit_columns) {
        Info index = column_info(column);
        edit_indecies.push_back(index);
    }

    queue<size_t> edit_row_indecies;
    // Loops through rows and edits the ones that fit comparisons
    for(size_t i = 0; i < table.rows_size(); ++i) {
        bool good = check_row(table.rows(i), indecies, comparisons);
        // cout << "GOOD? " << good << endl;
        if(!good) {
            continue;
        }

        // Edits each specified entry in row
        for(size_t j = 0; j < entries.size(); ++j) {
            if(!correct_type(edit_indecies[j], entries[j])) {
                throw type_mismatch(type_mismatch::error_type::UPDATION, get_type(edit_indecies[j]), get_type(entries[j]));
            }
        }
        edit_row_indecies.push(i);
    }

    cout << "EDIT ROWS SIZE: " << edit_row_indecies.size() << endl;
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

// Finds and edits rows where each entry@each column = the said comparison
// Changes rows to set entry@each edit_column = the said new entry
// Input: vector<string> columns -> columns being accessed
// Input: vector<Entry> comparisons -> list of entries to compare each row entry@column to
// Input: vector<string> &edit_columns -> columns being edited in filtered entries
// Input: vector<::database::Entry> &entries -> new entries to update entries in edit_columns
void Table::edit_rows(::database::Condition &top_condition,
                        vector<string> &edit_columns, 
                        vector<::database::Entry> &entries) {
    vector<Info> edit_indecies;
    for (string column : edit_columns) {
        Info index = column_info(column);
        edit_indecies.push_back(index);
    }

    queue<size_t> edit_row_indecies;
    // Loops through rows and edits the ones that fit comparisons
    for(size_t i = 0; i < table.rows_size(); ++i) {
        bool good = check_row(table.rows(i), top_condition);
        // cout << "GOOD? " << good << endl;
        if(!good) {
            continue;
        }

        // Edits each specified entry in row
        for(size_t j = 0; j < entries.size(); ++j) {
            if(!correct_type(edit_indecies[j], entries[j])) {
                throw type_mismatch(type_mismatch::error_type::UPDATION, get_type(edit_indecies[j]), get_type(entries[j]));
            }
        }
        edit_row_indecies.push(i);
    }

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
        Info index = column_info(column);
        edit_indecies.push_back(index);
    }

    for(size_t i = 0; i < table.rows_size(); ++i) {
        // Edits each specified entry in row
        for(size_t j = 0; j < entries.size(); ++j) {
            if(!correct_type(edit_indecies[j], entries[j])) {
                throw type_mismatch(type_mismatch::error_type::UPDATION, get_type(edit_indecies[j]), get_type(entries[j]));
            }
            ::database::Entry* edit_entry = table.mutable_rows(i)->mutable_entries(edit_indecies[j].index);
            edit_entry->CopyFrom(entries[j]);
        }
    }
}

// Inserts row into database
// Checks if row aligns with correct types
// Input: ::database::row &row -> row being inserted
void Table::insert(vector<string> columns, vector<::database::Entry> entries) {
    ::database::Row* new_row = table.add_rows();
    new_row->mutable_entries()->Reserve(column_indecies.size());
    for(int i = 0; i < column_indecies.size(); ++i) {
        new_row->add_entries();
    }
    cout << "here1" << endl;
    for(int i = 0; i < columns.size(); ++i) {
        auto it = column_indecies.find(columns[i]);
        Info info = it->second;
        ::database::Entry* edit_entry = new_row->mutable_entries(info.index);
        edit_entry->CopyFrom(entries[i]);
    }
    cout << "here2" << endl;
    for(auto it: column_indecies) {
        Info info = it.second;
        ::database::Entry entry = new_row->entries(info.index);
        bool full = entry.has_boolean() || entry.has_str() || entry.has_flt() || entry.has_num();
        if(!info.nullable && !full) {
            throw runtime_error("UMMM");
        }
    }
    cout << "here3" << endl;
} // insert()

// Removes rows where each entry@each column = the said comparison
// Input: vector<string> columns -> columns being accessed
// Input: vector<Entry> comparisons -> list of entries to compare each row entry@column to
void Table::remove_rows(vector<string> &columns, vector<::database::Entry> &comparisons) {
    vector<Info> indecies;
    
    for (string column : columns) {
        Info index;
        index = column_info(column);
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

// Removes rows where condition set is met
void Table::remove_rows(::database::Condition &top_condition) {
    auto current_it = table.mutable_rows()->begin();
    auto end_it = table.mutable_rows()->begin() + table.rows_size();
    auto result_it = current_it;

    // "Deletes" or disregards rows that should be removed by moving rows that shouldn't into there places
    // Meanwhile, advances result iterator to be the new end iterator of the table
    while(current_it != end_it) {
        bool should_remove = check_row(*current_it, top_condition);
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
    /*switch(it->second.type) {
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
    }*/
    return Table_Type_Name(it->second.type);
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

Table::Info Table::column_info(const string &column) {
    
    auto it = column_indecies.find(column);
    if(it == column_indecies.end()) {
        throw out_of_range("Column '" + column + "' Does Not Exist!");
    }
    return it->second;
} // column_info()

// Loops through all comparisons, checking if row entry@index is equal to the corresponding comparison
// If all checks are good, returns true; else, returns false
bool Table::check_row(const ::database::Row &row, vector<Info> indecies, vector<::database::Entry> &comparisons) {
    bool good = true;
    for(size_t j = 0; j < comparisons.size(); ++j) {
        bool correct_comparison = correct_type(indecies[j], comparisons[j]);
        if(!correct_comparison) {
            throw type_mismatch(type_mismatch::error_type::COMPARISON, get_type(indecies[j]), get_type(comparisons[j]));
        }
        
        // cout << row.entries(indecies[j].index).num() << " = " << comparisons[j].num() << endl;
        if(!google::protobuf::util::MessageDifferencer::Equals(row.entries(indecies[j].index), comparisons[j])) {
            good = false;
            break;
        }
    }
    return good;
}

// Recursively goes through every condition, checking if condition is true for said row
// If all checks are good, returns true; else, returns false
bool Table::check_row(const ::database::Row &row, const ::database::Condition &condition) {
    bool good = true;
    if(condition.has_child()) {
        good = check_row(row, condition.child());
    } else if(condition.has_column() && condition.has_entry()) {
        int col_index = column_index(condition.column());
        stringstream type_converter(condition.entry());

        switch(column_type(condition.column())) {
            case ::database::Table_Type_BOOL:
                bool val_b;
                type_converter >> val_b;
                //good = comparator(row.entries(col_index).boolean(), val_b);
                good = compare_entries<bool>(row.entries(col_index).boolean(), val_b, condition.comparator());
                break;
            
            case ::database::Table_Type_INT:
                int val_i;
                type_converter >> val_i;
                // good = comparator(row.entries(col_index).val(), val_i);
                good = compare_entries<int>(row.entries(col_index).num(), val_i, condition.comparator());
                break;
            
            case ::database::Table_Type_FLOAT:
                float val_f;
                type_converter >> val_f;
                // good = comparator(row.entries(col_index).flt(), val_f);
                good = compare_entries<float>(row.entries(col_index).flt(), val_f, condition.comparator());
                break;
            
            case ::database::Table_Type_STRING:
                // good = comparator(row.entries(col_index).str(), type_converter.str());
                good = compare_entries<string>(row.entries(col_index).str(), type_converter.str(), condition.comparator());
                break;
            
            default:
                throw std::out_of_range("Column " + condition.column() + " does not exist!");
                break;
        }
    }    

    if(condition.has_next()) {
        switch(condition.linker()) {
            case ::database::Condition::AND:
                return good && check_row(row, condition.next());
            case ::database::Condition::OR:
                return good || check_row(row, condition.next());
            default:
                return good;
        }
    }
    
    return good;
}

template<typename T> 
bool Table::compare_entries(T lhs, T rhs, ::database::Condition_Comparator comparator) {
    switch(comparator) {
        case ::database::Condition::EQUALS:
            return lhs == rhs;
            break;
        case ::database::Condition::GREATER:
            return lhs > rhs;
            break;
        case ::database::Condition::LESS:
            return lhs < rhs;
            break;
        case ::database::Condition::GREATER_EQUAL:
            return lhs >= rhs;
            break;
        case ::database::Condition::LESS_EQUAL:
            return lhs <= rhs;
            break;
        case ::database::Condition::NOT_EQUALS:
            return lhs != rhs;
            break;
        default:
            return false;
            break;
    }
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
    bool null_entry = !(entry.has_boolean() || entry.has_num() || entry.has_flt() || entry.has_str());
    switch(info.type) {
        case ::database::Table_Type_BOOL:
            return entry.has_boolean() || (info.nullable && null_entry);
            break;
        case ::database::Table_Type_INT:
            return entry.has_num() || (info.nullable && null_entry);
            break;
        case ::database::Table_Type_FLOAT:
            return entry.has_flt() || (info.nullable && null_entry);
            break;
        case ::database::Table_Type_STRING:
            return entry.has_str() || (info.nullable && null_entry);
            break;
        default:
            return false;
    }
} // correct_type()

string Table::get_type(Info &info) {
    return Table_Type_Name(info.type);
} // get_type()

string Table::get_type(::database::Entry entry) {
    if(entry.has_boolean()) {
        return Table_Type_Name(::database::Table_Type_BOOL);
    } else if(entry.has_num()) {
        return Table_Type_Name(::database::Table_Type_INT);
    } else if(entry.has_flt()) {
        return Table_Type_Name(::database::Table_Type_FLOAT);
    } else if(entry.has_str()) {
        return Table_Type_Name(::database::Table_Type_STRING);
    }
    return "NO TYPE";
} // get_type()