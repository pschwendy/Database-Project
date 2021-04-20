// Peter Schwendeman
//
//
// table_test.cpp
//

#include "Table.h"
#include <iostream>
#include <casset>

using namespace std;

::database::Row make_row(int x = 0, int x1 = 0, float y = 0, float y1 = 0, string str = "", string str1 = "", bool b = false) {
    ::database::Row entries;
    
    if(x != 0) {
        ::database::Entry entry;
        entry.set_num(x);
        entries.add_entries() = entry;
    }
    if(x1 != 0) {
        ::database::Entry entry1;
        entry.set_num(x1);
        entries.add_entries() = entry1;
    }
    if(y != 0) {
        ::database::Entry entry2;
        entry.set_num(y);
        entries.add_entries() = entry2;
    }
    if(y1 != 0) {
        ::database::Entry entry3;
        entry.set_num(y1);
        entries.add_entries() = entry3;
    }
    if(str != "") {
        ::database::Entry entry4;
        entry.set_num(str);
        entries.add_entries() = entry4;
    }
    if(str1 != "") {
        ::database::Entry entry5;
        entry.set_num(x);
        entries.add_entries() = entry5;
    }
    if(b) {
        ::database::Entry entry6;
        entry.set_num(b);
        entries.add_entries() = entry6;
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
    
    ::database::Row row = make_row(1, 1.2, 3.0, "poop", true);
    ::database::Row row1 = make_row(-8347, 11.2, 43.0, "hello", true);
    ::database::Row row2 = make_row(123, 11.2, -12.0, "hello", true);
    ::database::Row row3 = make_row(-1, -298.2, 3.2, "nah", true);
    
    // row shouldn't be pushable
    ::database::Row bad_row = make_row(0, -298.2, 3.2, true);

    vector<string> columns = {"int", "float1", "float2", "string", "boolean"};
    vector<string> types = {"int", "float", "float", "string", "bool"};
    Table table = Table(columns, types);

    table.insert(&row);
    table.insert(&row1);

    // catch the bad row insertion
    try {
        table.insert(&bad_row);
    } catch {
        cout << "PASSED BAD INSERTION TEST" << endl;
    }
    
    table.insert(&row2);
    table.insert(&row3);
    
    /* Creating Table */


    // Test Functionality

    /* Creating comparison columns and entries */
    vector<string> columns1 = {"float1", "string"};
    vector<string> columns2 = {"int", "string", "float2"};
    vector<string> columns3 = {"bool"};

    vector<::database::Entry> comparisons1;
    comparisons1.push_back(make_entry(&table, "float1", 15, 11.2, "kfdk", false)));
    comparisons1.push_back(make_entry(&table, "string", 15, 11.2, "hello", false)));

    vector<::database::Entry> comparisons2;
    comparisons2.push_back(make_entry(&table, "int", 1, 11.2, "kfdk", false)));
    comparisons2.push_back(make_entry(&table, "string", 15, 11.2, "poop", false)));
    comparisons2.push_back(make_entry(&table, "float2", 15, 3.0, "poop", false)));

    vector<::database::Entry> comparisons3;
    comparisons2.push_back(make_entry(&table, "bool", 15, 3.0, "poop", true)));

    vector<::database::Entry> comparisons4;
    comparisons2.push_back(make_entry(&table, "bool", 15, 3.0, "poop", false)));
    /* Created comparison columns and entries */

    /* Filter Tests */
    assert(table.filter(columns1, comparisons1).size() == 2);
    assert(table.filter(columns1, comparisons1)[0].getEntries(2).get_flt() == 43.2);
    assert(table.filter(columns1, comparisons1)[1].getEntries(0).get_num() == 123);

    assert(table.filter(columns2, comparisons2).size() == 1);
    assert(table.filter(columns2, comparisons2)[0].getEntries(0).get_num() == 1);
    assert(table.filter(columns2, comparisons2)[0].getEntries(4).get_bool() == true);
    assert(table.filter(columns2, comparisons2)[0].getEntries(1).get_flt() == 1.2);

    assert(table.filter(columns3, comparisons3).size() == 4);
    assert(table.filter(columns3, comparisons3)[0].getEntries(0).get_num() == 1);
    assert(table.filter(columns3, comparisons3)[0].getEntries(4).get_bool() == true);
    assert(table.filter(columns3, comparisons3)[0].getEntries(1).get_flt() == 1.2);
    assert(table.filter(columns3, comparisons3)[1].getEntries(0).get_num() == -8347);
    assert(table.filter(columns3, comparisons3)[2].getEntries(0).get_num() == 123);
    assert(table.filter(columns3, comparisons3)[3].getEntries(0).get_num() == -1);
    
    assert(table.filter(columns3, comparisons4).size() == 0);
    cout << "Passed Filter Tests!" << endl;
    /* Passed Filter Tests */

    /* Update Test */
    //table.edit_rows()

}