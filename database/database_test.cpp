// Peter Schwendeman
//
//
// table_test.cpp
//

#include "database.h"
#include "table_test.h"
#include "protos/table.pb.h"
#include <iostream>
#include <cassert>

using namespace std;

Table create_table1() {
    ::database::Row row = make_row(1, 0, 1.2, 3.0, "friend", "", true);
    ::database::Row row1 = make_row(-8347, 0, 11.2, 43.0, "hello", "", true);
    ::database::Row row2 = make_row(123, 0, 11.2, -12.0, "hello", "", true);
    ::database::Row row3 = make_row(-1, 0,  -298.2, 3.2, "nah", "", true);

    vector<string> columns = {"int", "float1", "float2", "string", "boolean"};
    vector<string> types = {"int", "float", "float", "string", "bool"};
    Table table = Table(columns, types);

    table.insert(row);
    table.insert(row1); 
    table.insert(row2);
    table.insert(row3);

    return table;
}

Table create_table2() {
    ::database::Row row = make_row(0, 0, 1.2, 0, "friend");
    ::database::Row row1 = make_row(0, 0, 1.3, 0, "leg");
    ::database::Row row2 = make_row(0, 0, 1.4, 0, "friend");
    ::database::Row row3 = make_row(0, 0, -0.1, 0, "leg");
    ::database::Row row4 = make_row(0, 0, -0.2, 0, "friend");
    ::database::Row row5 = make_row(0, 0, 22.8, 0, "you");
    ::database::Row row6 = make_row(0, 0, -1.0, 0, "you");
    ::database::Row row7 = make_row(0, 0, 9.3, 0, "friend");

    vector<string> columns = {"number", "word"};
    vector<string> types = {"float", "string"};
    
    Table table = Table(columns, types);

    table.insert(row);
    table.insert(row1); 
    table.insert(row2);
    table.insert(row3);

    return table;
}

int main() {
    Table table1 = create_table1();
    Table table2 = create_table2();
}