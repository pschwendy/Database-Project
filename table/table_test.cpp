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

int main() {
    /* Creating Table */
    
    ::database::Row row = make_row(1, 0, 1.2, 3.0, "friend", "", true);
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

    // Catch the bad row insertion
    cout << "Checking Bad Insertion Test..." << endl;
    
    try {
        table.insert(bad_row);
    } catch (out_of_range e) {
        cout << e.what() << endl;
    }

    cout << "Passed Bad Insertion Test!" << endl;

    table.insert(row2);
    table.insert(row3);
    
    /* Table Created */
    cout << "---Finished Creating Table---" << endl;

    // Test Functionality

    /* Creating comparison columns and entries */
    vector<string> columns1 = {"float1", "string"};
    vector<string> columns2 = {"int", "string", "float2"};
    vector<string> columns3 = {"boolean"};

    vector<::database::Entry> comparisons1;
    comparisons1.push_back(make_entry(&table, "float1", 15, 11.2, "kfdk", false));
    comparisons1.push_back(make_entry(&table, "string", 15, 11.2, "hello", false));

    vector<::database::Entry> comparisons2;
    comparisons2.push_back(make_entry(&table, "int", 1, 11.2, "kfdk", false));
    comparisons2.push_back(make_entry(&table, "string", 15, 11.2, "friend", false));
    comparisons2.push_back(make_entry(&table, "float2", 15, 3.0, "friend", false));

    vector<::database::Entry> comparisons3;
    comparisons3.push_back(make_entry(&table, "boolean", 15, 3.0, "friend", true));

    vector<::database::Entry> comparisons4;
    comparisons4.push_back(make_entry(&table, "boolean", 15, 3.0, "friend", false));
    /* Created comparison columns and entries */

    /* Filter Tests */
    cout << "Starting Filter Tests..." << endl;
    assert(table.filter(columns1, comparisons1).size() == 2);
    assert(table.filter(columns1, comparisons1)[0].entries(2).flt() == 43.0);
    assert(table.filter(columns1, comparisons1)[1].entries(0).num() == 123);
    
    assert(table.filter(columns2, comparisons2).size() == 1);
    assert(table.filter(columns2, comparisons2)[0].entries(0).num() == 1);
    assert(table.filter(columns2, comparisons2)[0].entries(4).boolean() == true);
    assert((float)table.filter(columns2, comparisons2)[0].entries(1).flt() == (float)1.2);

    assert(table.filter(columns3, comparisons3).size() == 4);
    assert(table.filter(columns3, comparisons3)[0].entries(0).num() == 1);
    assert(table.filter(columns3, comparisons3)[0].entries(4).boolean() == true);
    assert(table.filter(columns3, comparisons3)[0].entries(1).flt() == (float)1.2);
    assert(table.filter(columns3, comparisons3)[1].entries(0).num() == -8347);
    assert(table.filter(columns3, comparisons3)[2].entries(0).num() == 123);
    assert(table.filter(columns3, comparisons3)[3].entries(0).num() == -1);
    
    assert(table.filter(columns3, comparisons4).size() == 0);
    cout << "Passed Filter Tests!" << endl;
    /* Passed Filter Tests */

    /* Update Test */
    cout << "Starting Update Tests..." << endl;
    table.edit_rows(columns1, comparisons1, columns2, comparisons2);
    assert(table.filter(columns2, comparisons2).size() == 3);
    assert(table.filter(columns2, comparisons2)[0].entries(2).flt() == 3.0);
    assert(table.filter(columns2, comparisons2)[1].entries(1).flt() == (float)11.2);
    assert(table.filter(columns2, comparisons2)[1].entries(3).str() == table.filter(columns2, comparisons2)[2].entries(3).str());
    assert(table.filter(columns2, comparisons2)[1].entries(3).str() == "friend");

    table.edit_rows(columns2, comparisons2, columns1, comparisons1);
    assert(table.filter(columns1, comparisons1).size() == 3);
    assert(table.filter(columns1, comparisons1)[0].entries(2).flt() == (float)3.0);
    assert(table.filter(columns1, comparisons1)[0].entries(0).num() == 1);
    
    table.edit_rows(columns3, comparisons3, columns3, comparisons4);
    assert(table.filter(columns3, comparisons4).size() == 4);
    
    cout << "Passed Update Tests!" << endl;
    /* Passed Update Tests */

    /* Deletion Tests */
    cout << "Starting Deletion Tests..." << endl;
    
    table.delete_rows(columns3, comparisons3);
    assert(table.filter(columns3, comparisons3).size() == 0);

    cout << "Passed Deletion Tests!" << endl;
    /* Passed Deletion Tests */
}