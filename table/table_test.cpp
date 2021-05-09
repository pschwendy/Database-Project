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
    } else if (type == "BOOL") {
        entry.set_str(c);
    } else if (type == "STRING") {
        entry.set_boolean(d);   
    }
    return entry;
}

int main() {
    /* Creating Table */
    
    ::database::Row row = make_row(1, 0, 1.2, 3.0, "poop", "", true);
    ::database::Row row1 = make_row(-8347, 0, 11.2, 43.0, "hello", "", true);
    ::database::Row row2 = make_row(123, 0, 11.2, -12.0, "hello", "", true);
    ::database::Row row3 = make_row(-1, 0,  -298.2, 3.2, "nah", "", true);
    
    // row shouldn't be pushable
    ::database::Row bad_row = make_row(0, 0, -298.2, 3.2, "", "", true);

    vector<string> columns = {"int", "float1", "float2", "string", "boolean"};
    vector<string> types = {"int", "float", "float", "string", "bool"};
    Table table = Table(columns, types);

    table.insert(row);
    table.insert(row1);

    // catch the bad row insertion
    try {
        table.insert(bad_row);
    } catch (out_of_range) {
        cout << "PASSED BAD INSERTION TEST" << endl;
    }
    
    table.insert(row2);
    table.insert(row3);
    
    /* Creating Table */


    // Test Functionality

    /* Creating comparison columns and entries */
    vector<string> columns1 = {"float1", "string"};
    vector<string> columns2 = {"int", "string", "float2"};
    vector<string> columns3 = {"bool"};

    vector<::database::Entry> comparisons1;
    comparisons1.push_back(make_entry(&table, "float1", 15, 11.2, "kfdk", false));
    comparisons1.push_back(make_entry(&table, "string", 15, 11.2, "hello", false));

    vector<::database::Entry> comparisons2;
    comparisons2.push_back(make_entry(&table, "int", 1, 11.2, "kfdk", false));
    comparisons2.push_back(make_entry(&table, "string", 15, 11.2, "poop", false));
    comparisons2.push_back(make_entry(&table, "float2", 15, 3.0, "poop", false));

    vector<::database::Entry> comparisons3;
    comparisons2.push_back(make_entry(&table, "bool", 15, 3.0, "poop", true));

    vector<::database::Entry> comparisons4;
    comparisons2.push_back(make_entry(&table, "bool", 15, 3.0, "poop", false));
    /* Created comparison columns and entries */

    /* Filter Tests */
    assert(table.filter(columns1, comparisons1).size() == 2);
    assert(table.filter(columns1, comparisons1)[0].entries(2).flt() == 43.2);
    assert(table.filter(columns1, comparisons1)[1].entries(0).num() == 123);

    assert(table.filter(columns2, comparisons2).size() == 1);
    assert(table.filter(columns2, comparisons2)[0].entries(0).num() == 1);
    assert(table.filter(columns2, comparisons2)[0].entries(4).boolean() == true);
    assert(table.filter(columns2, comparisons2)[0].entries(1).flt() == 1.2);

    assert(table.filter(columns3, comparisons3).size() == 4);
    assert(table.filter(columns3, comparisons3)[0].entries(0).num() == 1);
    assert(table.filter(columns3, comparisons3)[0].entries(4).boolean() == true);
    assert(table.filter(columns3, comparisons3)[0].entries(1).flt() == 1.2);
    assert(table.filter(columns3, comparisons3)[1].entries(0).num() == -8347);
    assert(table.filter(columns3, comparisons3)[2].entries(0).num() == 123);
    assert(table.filter(columns3, comparisons3)[3].entries(0).num() == -1);
    
    assert(table.filter(columns3, comparisons4).size() == 0);
    cout << "Passed Filter Tests!" << endl;
    /* Passed Filter Tests */

    /* Update Test */
    table.edit_rows(columns1, comparisons1, columns2, comparisons2);
    assert(table.filter(columns2, comparisons2).size() == 2);
    table.edit_rows(columns2, comparisons2, columns1, comparisons1);
    assert(table.filter(columns1, comparisons1).size() == 2);
    //table.edit_rows(columns3, comparisons3, )

}