// Peter Schwendeman
//
//
// storage.cpp
//

#include "storage.h"
using namespace std;

namespace Storage {

    // !!!!!!!!hash table of hash tables: db_name -> hash table(table_name, table_path)
    // Given the name of the database, reads data from file system if the database exists
    // If not, creates a new blank database
    // Input: string &db_name -> name of database 
    // Database name -> unordered map w/ (table -> schema, rows)
    // Wrap maps in class or use typename
    void read_data() {
        string db_name;

        // string file = "/databases/databases.txt";
        ifstream databases(database_list_path);

        if(!databases.good()) {
            throw out_of_range("Error: Missing file - " + database_list_path);
        }
        
        if(databases.peek() == std::ifstream::traits_type::eof()) {
            databases.close();
            return;
        }

        while(databases >> db_name) {
            string path = path_to_database + db_name + "/";
            ifstream table_list(path + "tables.txt");
            //unordered_map<string, std::pair<string, string> > 
            TableRouter table_to_path;
            string table_name;
            while(table_list >> table_name) {
                string schema = path + table_name + "_schema.txt";
                string rows = path + table_name + "_rows.txt";
                std::pair<string, string> table_paths = make_pair(schema, rows);
                table_to_path.insert({table_name, table_paths});
            }
            router.insert({db_name, table_to_path});
        }
        databases.close();
    } // read_data()

    bool check_database_exists(string &db_name) {
        ifstream databases(database_list_path);
        string name_check;
        if(!databases.good()) {
            // throw()
        }
        while(databases >> name_check) {
            if(name_check == db_name) {
                return true;
            }
        }
        return false;
    }

    void create_database(string &db_name) {
        string path = path_to_database + db_name + "/";
        TableRouter tb_router = TableRouter(); 
        router.insert({db_name, tb_router});
        if(check_database_exists(db_name)) {
            // use runtime_error
            throw std::runtime_error("Database " + db_name + " already exists.");
        }

        ofstream append_db_list(database_list_path, std::ofstream::app);
        if(!append_db_list.good()) {
            throw out_of_range("Error: Missing file - " + database_list_path);
        }

        append_db_list << db_name << "\n";

        fs::create_directory(path);
        std::ofstream { path + "tables.txt" };
    }

    void delete_database(string &db_name) {
        string path = path_to_database + db_name + "/";
        ifstream old_db_list_stream(database_list_path);
        stringstream new_db_list;
        
        string input;
        while(old_db_list_stream >> input) {
            if(input == db_name) {
                continue;
            }
            new_db_list << input << "\n";
        }

        ofstream new_db_list_stream(database_list_path);
        new_db_list_stream << new_db_list.str();
        fs::remove_all(path);
    }
    
    void create_table(string &db_name, Table &table) {
        string path = path_to_database + db_name + "/";
        ofstream table_list(path + "tables.txt", std::ofstream::app);
        table_list << table.get_name() << "\n";
        table_list.close();

        string schema = path + table.get_name() + "_schema.txt";
        string rows = path + table.get_name() + "_rows.txt";
        
        std::pair<string, string> table_paths = make_pair(schema, rows);
        router[db_name].insert({table.get_name(), table_paths});
        
        ofstream schema_file(schema, std::ofstream::trunc);
        schema_file << table.schema();
        
        ofstream rows_file(rows, std::ofstream::trunc);
        if(!table.serialize(&rows_file)) {
            throw out_of_range("Cannot open or make file " + rows);
        }
    }

    void write_table(string &db_name, Table &table) {
        TableRouter database = router[db_name];
        auto table_to_table_paths = database.find(table.get_name());
        std::pair<string, string> table_paths = table_to_table_paths->second;

        ofstream schema(table_paths.first, std::ofstream::trunc);
        schema << table.schema();
        
        ofstream rows(table_paths.second, std::ofstream::trunc);
        if(!table.serialize(&rows)) {
            throw out_of_range("Cannot open or make file " + table_paths.second);
        }
    }

    Table read_table(string &db_name, string &table_name) {
        //auto database = router.find(db_name);
        // router.print();
        TableRouter database = router[db_name];
        auto table_to_table_paths = database.find(table_name);
        if(table_to_table_paths == database.end()) {
            cout << "NO TABLE EXISTS: " << table_name << endl;
            exit(0);
        }
        // cout << table_to_table_paths->first << endl;
        std::pair<string, string> table_paths = table_to_table_paths->second;
        ifstream schema(table_paths.first);
        vector<string> columns;
        vector<string> types;
        vector<bool> nullable_list;
        vector<int> indecies;

        string input;
        string type;
        string column;
        while(std::getline(schema, input)) {
            stringstream line_reader(input);
            bool nullable_column = true;
            line_reader >> type;
            line_reader >> column;
            if(line_reader >> input && input == "NOT") {
                line_reader >> input;
                nullable_column = false;
            }
            int index;
            line_reader >> index;
            types.emplace_back(type);
            columns.emplace_back(column);
            nullable_list.push_back(nullable_column);
            indecies.push_back(index);
            // cout << "here11111 " << type << " " << column << " " << nullable_column << " " << index << endl;
        }
        ifstream rows(table_paths.second);
        ::database::Table parse_table;
        parse_table.ParseFromIstream(&rows);
        
        // ADD NULLABLE ROWS
        return Table(table_name, columns, types, nullable_list, indecies, parse_table);
        // return Table();
    }
}

/* UNUSED CODE */
// Writes to database directory given a database
// Input: Database &db -> database being written to storage
/*void Storage::read_data(string &db_name) {
    string path = "/databases/" + db_name + "/";
        
    bool exists;
    string name_check;
    if(!databases.good()) {
        // throw()
    }
    while(databases >> name_check) {
        if(name_check == db_name) {
            exists = true;
            break;
        }
    }

    if(exists) {
        ifstream table_list(path + "tables.txt");
        string table_name;
        vector<string> names;
        vector<Table> tables;
        
        while(table_list >> table_name) {
            ifstream schema(path + table_name + "_schema.txt");
            // ADD NULLABLE ROWS
            vector<string> columns;
            vector<string> types;

            while(schema >> types) {
                schema >> columns;
            }

            ifstream rows(path + table_name + "_rows.txt");
            ::database::Table parse_table;
            parse_table.ParseFromIstream(&rows));
            
            // ADD NULLABLE ROWS
            Table table = Table(table_name, columns, types, parse_table);

            names.emplace_back(table_name);
            tables.emplace_back(table);
        }
        db = Database(db_name, names, tables);
    } else {
        db = Database(db_name);
    }

    return db;
}*/
/*static void Storage::write_data(Database &db) {
    // Add file to list databases inside of some collective database folder
    // Add file to list tables inside each individual database folder
    // Iterate throught files to get and use paths
    string file = "/databases/databases.txt";
    string path = "/databases/" + db.get_name() + "/";

    stringstream table_list;
    ifstream databases(file);

    bool exists;
    string name_check;
    if(!databases.good()) {
        // throw()
    }
    while(databases >> db_names) {
        if(name_check == db.get_name()) {
            exists = true;
            break;
        }
    }
    // If the directory with name exists
    if(!exists) {
        int dir = mkdir(path, 0777);
        if(dir == -1) {
            // throw()
        }
    } else { // Create Directory and write database to it
        // TODO: some creation code
        
    }
    for(auto it : *(db.get_tables())) {
        table_list << it.first << "\n";

        ofstream schema(path + it->first + "_schema.txt");
        schema << it->second->schema();
        
        ofstream rows(path + it->first + "_rows.txt");
        if(!it->second->serialize(rows)) {
            // throw()
        }
    }

    ofstream os(path + "tables.txt");
    os << table_list;
} // write_data()*/

// delete -> fs::remove_all("myDirectory");

/*static Table read_table(string &db_name, string &table_name) {
    string file = "/databases/databases.txt";
    ifstream databases(file);

    string path = "/databases/" + db_name + "/";
    
    bool exists;
    string name_check;
    if(!databases.good()) {
        // throw()
    }
    while(databases >> name_check) {
        if(name_check == db_name) {
            exists = true;
            break;
        }
    }

    if(!exists) {
        throw std::out_of_range("Error: Database " + db_name + " does not exist.");
    }

    ifstream table_list(path + "tables.txt");
    exists = false;

    while(table_list >> name_check) {
        if(name_check == table_name) {
            exists = true;
            break;
        }
    }

    if(!exists) {
        throw std::out_of_range("Error: Table " + table_name + " does not exist inside database " + db_name + ".");
    }

    ifstream schema(path + table_name + "_schema.txt");
    vector<string> columns;
    vector<string> types;

    while(schema >> types) {
        schema >> columns;
    }

    ifstream rows(path + table_name + "_rows.txt");
    ::database::Table parse_table;
    parse_table.ParseFromIstream(&rows));
    
    // ADD NULLABLE ROWS
    return Table(table_name, columns, types, parse_table);
}*/
