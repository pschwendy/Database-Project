// Peter Schwendeman
//
//
// table_test.cpp
//

#include "table.h"
#include "protos/table.pb.h"
#include <iostream>
#include <cassert>

using namespace std;

::database::Row make_row(int x = 0, int x1 = 0, float y = 0, float y1 = 0, string str = "", string str1 = "", bool b = false) {
    ::database::Row entries;
    
    if(x != 0) {
        ::database::Entry *entry = entries.add_entries();
        entry->set_num(x);
    }
    if(x1 != 0) {
        ::database::Entry *entry1 = entries.add_entries();
        entry1->set_num(x1);
    }
    if(y != 0) {
        ::database::Entry *entry2 = entries.add_entries();
        entry2->set_flt(y);
    }
    if(y1 != 0) {
        ::database::Entry *entry3 = entries.add_entries();
        entry3->set_flt(y1);
    }
    if(str != "") {
        ::database::Entry *entry4 = entries.add_entries();
        entry4->set_str(str);
    }
    if(str1 != "") {
        ::database::Entry *entry5 = entries.add_entries();
        entry5->set_str(str1);
    }
    if(b) {
        ::database::Entry *entry6 = entries.add_entries();
        entry6->set_boolean(b);
    }
    
    return entries;
}

::database::Entry make_entry(Table* table, string column, int a, float b, string c, bool d) {
    string type = table->get_type(column);
    ::database::Entry entry;
    if(type == "INT") {
        entry.set_num(a);
    } else if (type == "FLOAT") {
        entry.set_flt(b);
    } else if (type == "STRING") {
        entry.set_str(c);
    } else if (type == "BOOL") {
        entry.set_boolean(d);   
    }
    return entry;
}

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