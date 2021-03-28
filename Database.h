// Peter Schwendeman
//
//
// Database.h
//

#ifndef Database_h
#define Database_h

#include <unordered_map>
#include <string>
#include <vector>
#include "Table.h"

using namespace std;

class Database {
    public:
        void update(string &table_name, 
                    vector<string> &edit_columns, 
                    vector<::database::Entry> &entries, 
                    vector<string> &columns, 
                    vector<::database::Entry> &comparisons);
        
        void insert(string &table_name, 
                    ::database::Row row);
        
        vector<::database::Row> select(string &table_name, 
                                    vector<string> &columns, 
                                    vector<::database::Entry> &comparisons);
        
        void drop_table(string &table_name);
        
        void create_table(string &table_name, 
                        vector<string> &column_names, 
                        vector<string> &column_types);
    
    private:
        unordered_map<string, Table*> tables;

        Table* get_table(string& table_name);
};
#endif // Database_h