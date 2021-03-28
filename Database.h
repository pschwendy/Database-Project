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
#include "Entry.h"
#include "Row.h"
#include "Table.h"

using namespace std;

class Database {
    public:
        void update();
        void insert();
        void select();
        void drop_table();
        void create_table();
    
    private:
        unordered_map<string, Table> tables;
};
#endif // Database_h