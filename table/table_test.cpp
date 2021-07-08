// Peter Schwendeman
//
//
// table_test.cpp
//

#include "table.h"
#include "protos/table.pb.h"
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

::database::Row make_row(int x = 0, int x1 = 0, float y = 0, float y1 = 0, string str = "", string str1 = "", bool b = false);
::database::Entry make_entry(Table* table, string column, int a, float b, string c, bool d);

void bad_insertion_test_wrong_size(Table &table);
void bad_insertion_test_type_mismatch(Table &table);

void filter_test_standard(Table &table);
void filter_test_on_empty_table(Table &table);
void filter_test_no_rows_found(Table &table);
void filter_test_type_mismatch(Table &table);

void edit_test_standard(Table &table);
void edit_test_on_empty_table(Table &table);
void edit_test_no_rows_found(Table &table);
void edit_all_test(Table &table);
void edit_test_type_mismatch(Table &table);

void deletion_test_standard(Table &table);
void deletion_test_on_empty_table(Table &table);
void deletion_test_no_rows_found(Table &table);
void deletion_test_type_mismatch(Table &table);
void delete_all_test(Table &table);

int main() {
    /* Creating Table */
    
    ::database::Row row = make_row(1, 0, 1.2f, 3.0f, "friend", "", true);
    ::database::Row row1 = make_row(-8347, 0, 11.2f, 43.0f, "hello", "", true);
    ::database::Row row2 = make_row(123, 0, 11.2f, -12.0f, "hello", "", true);
    ::database::Row row3 = make_row(-1, 0,  -298.2f, 3.2f, "nah", "", true);
    
    vector<string> columns = {"int", "float1", "float2", "string", "boolean"};
    vector<string> types = {"int", "float", "float", "string", "bool"};
    
    Table table = Table(columns, types);
    Table empty_table = Table(columns, types);

    table.insert(row);
    table.insert(row1);

    cout << "---Starting Insertion Tests---" << endl;
    bad_insertion_test_wrong_size(table);
    bad_insertion_test_type_mismatch(table);
    cout << "---Passed Insertion Tests!---" << endl;

    table.insert(row2);
    table.insert(row3);
    
    /* --- Table Created ---
        1 | 1.2 | 3.0 | friend | true
        -8347 | 11.2 | 43.0 | hello | true
        123 | 11.2 | -12.0 | hello | true
        -1 | -298.2f | 3.2 | nah | true   
    */
    
    cout << "---Finished Creating Table---" << endl;
    
    // Functionality test
    // Filter Tests
    cout << "---Starting Filter Tests---" << endl;
    filter_test_standard(table);
    filter_test_on_empty_table(empty_table);
    filter_test_no_rows_found(table);
    filter_test_type_mismatch(table);
    cout << "---Passed Filter Tests---" << endl;
}

::database::Row make_row(int x, int x1, float y, float y1, string str, string str1, bool b) {
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

void bad_insertion_test_wrong_size(Table &table) {
    // Catch the bad row insertion
    
    
    // row shouldn't be pushable
    ::database::Row bad_row = make_row(0, 0, -298.2f, 3.2f, "", "", true);
    
    try {
        table.insert(bad_row);
    } catch (out_of_range e) {
        cout << e.what() << endl;
    }

    
}

void bad_insertion_test_type_mismatch(Table &table) {
    ::database::Row bad_row;
    ::database::Entry *entry = bad_row.add_entries();
    entry->set_flt(1.0f);
    ::database::Entry *entry1 = bad_row.add_entries();
    entry1->set_flt(1.0f);
    ::database::Entry *entry2 = bad_row.add_entries();
    entry2->set_flt(1.0f);
    ::database::Entry *entry3 = bad_row.add_entries();
    entry3->set_str("string");
    ::database::Entry *entry4 = bad_row.add_entries();
    entry4->set_boolean(true);

    ::database::Row bad_row2;
    ::database::Entry *entry5 = bad_row2.add_entries();
    entry5->set_num(1);
    ::database::Entry *entry6 = bad_row2.add_entries();
    entry6->set_flt(1.0f);
    ::database::Entry *entry7 = bad_row2.add_entries();
    entry7->set_num(2);
    ::database::Entry *entry8 = bad_row2.add_entries();
    entry8->set_str("string");
    ::database::Entry *entry9 = bad_row2.add_entries();
    entry9->set_boolean(true);

    try {
        table.insert(bad_row);
        cout << "Failed Bad Insertion Test. Did not catch type mismatch." << endl;
    } catch (Table::type_mismatch e) {
        cout << e.what() << endl;
    }

    try {
        table.insert(bad_row2);
        cout << "Failed Bad Insertion Test. Did not catch type mismatch." << endl;
    } catch (Table::type_mismatch e) {
        cout << e.what() << endl;
    }
}

// 1 - Arrange test
// 2 - Calling methods
// 3 - Make assertions
// Standard tests for the filter method
void filter_test_standard(Table &table) {
    // Arranging Test
    // Setting up column lists for filters
    vector<string> columns1 = {"float1", "string"};
    vector<string> columns2 = {"int", "string", "float2"};
    vector<string> columns3 = {"boolean"};

    // Setting up lists of entries to compare each entry at the corresponding column to
    /* --- Columns 1, Comparisons 1 ---
        float1: 11.2
        string: hello                    */
    vector<::database::Entry> comparisons1;
    comparisons1.push_back(make_entry(&table, "float1", 15, 11.2, "kfdk", false));
    comparisons1.push_back(make_entry(&table, "string", 15, 11.2, "hello", false));
    
    /* --- Columns 2, Comparisons 2 ---
        int: 1
        string: friend
        float2: 3.0                      */
    vector<::database::Entry> comparisons2;
    comparisons2.push_back(make_entry(&table, "int", 1, 11.2, "kfdk", false));
    comparisons2.push_back(make_entry(&table, "string", 15, 11.2, "friend", false));
    comparisons2.push_back(make_entry(&table, "float2", 15, 3.0, "friend", false));
    
    /* --- Columns 3, Comparisons 3 ---
        boolean: true                    */
    vector<::database::Entry> comparisons3;
    comparisons3.push_back(make_entry(&table, "boolean", 15, 3.0, "friend", true));
    
    // Calling Methods
    size_t pair1_size = table.filter(columns1, comparisons1).size(); // == 2
    float pair1_check1 = table.filter(columns1, comparisons1)[0].entries(2).flt(); // == 43.0f);
    int pair1_check2 = table.filter(columns1, comparisons1)[1].entries(0).num(); // == 123);
    
    size_t pair2_size = table.filter(columns2, comparisons2).size(); // == 1);
    int pair2_check1 = table.filter(columns2, comparisons2)[0].entries(0).num(); // == 1);
    bool pair2_check2 = table.filter(columns2, comparisons2)[0].entries(4).boolean(); // == true);
    float pair2_check3 = table.filter(columns2, comparisons2)[0].entries(1).flt(); // == 1.2f);

    size_t pair3_size = table.filter(columns3, comparisons3).size(); // == 4);
    int pair3_check1 = table.filter(columns3, comparisons3)[0].entries(0).num(); // == 1);
    bool pair3_check2 = table.filter(columns3, comparisons3)[0].entries(4).boolean(); // == true);
    float pair3_check3 = table.filter(columns3, comparisons3)[0].entries(1).flt(); // == 1.2f);
    int pair3_check4 = table.filter(columns3, comparisons3)[1].entries(0).num(); // == -8347);
    int pair3_check5 = table.filter(columns3, comparisons3)[2].entries(0).num(); // == 123);
    int pair3_check6 = table.filter(columns3, comparisons3)[3].entries(0).num(); // == -1);
    
    // Assertions
    assert(pair1_size == 2);
    assert(pair2_size == 1);
    assert(pair3_size == 4);

    assert(pair1_check1 == 43.f);
    assert(pair1_check2 == 123);
    assert(pair2_check1 == 1);
    assert(pair2_check2 == true);
    assert(pair2_check3 == 1.2f);
    
    assert(pair3_check1 == 1);
    assert(pair3_check2 == true);
    assert(pair3_check3 == 1.2f);
    assert(pair3_check4 == -8347);
    assert(pair3_check5 == 123);
    assert(pair3_check6 == -1);
}

// Standard tests for the filter method
void filter_test_on_empty_table(Table &table) {
    // Arranging Test
    // Setting up column lists for filters
    vector<string> columns1 = {"float1", "string"};
    vector<string> columns2 = {"boolean"};

    // Setting up lists of entries to compare each entry at the corresponding column to
    /* --- Columns 1, Comparisons 1 ---
        float1: 11.2
        string: hello                    */
    vector<::database::Entry> comparisons1;
    comparisons1.push_back(make_entry(&table, "float1", 15, 11.2, "kfdk", false));
    comparisons1.push_back(make_entry(&table, "string", 15, 11.2, "hello", false));

    /* --- Columns 3, Comparisons 3 ---
        boolean: false                   */
    vector<::database::Entry> comparisons2;
    comparisons2.push_back(make_entry(&table, "boolean", 15, 3.0, "friend", false));

    size_t size1 = table.filter(columns1, comparisons1).size();
    size_t size2 = table.filter(columns2, comparisons2).size();

    assert(size1 == 0);
    assert(size2 == 0);
}

void filter_test_no_rows_found(Table &table) {
    // Arranging Test
    // Setting up column lists for filters
    vector<string> columns1 = {"boolean"};

    // Setting up lists of entries to compare each entry at the corresponding column to
    /* --- Columns 1, Comparisons 1 ---
        boolean: false                   */
    vector<::database::Entry> comparisons1;
    comparisons1.push_back(make_entry(&table, "boolean", 15, 3.0, "friend", false));

    size_t size1 = table.filter(columns1, comparisons1).size();

    assert(size1 == 0);
}

void filter_test_type_mismatch(Table &table) {
    // Arranging Test
    // Setting up column and comparison lists for filters
    vector<string> columns1 = {"boolean"};
    ::database::Entry fake_bool_entry;
    fake_bool_entry.set_num(23);
    vector<::database::Entry> comparisons1 = {fake_bool_entry};
    
    vector<string> columns2 = {"float1", "string"};
    ::database::Entry fake_float_entry;
    fake_float_entry.set_str("oops");
    ::database::Entry fake_string_entry;
    fake_string_entry.set_flt(-2.0f);
    vector<::database::Entry> comparisons2 = {fake_float_entry, fake_string_entry};

    try {
        vector<::database::Row> bad_rows = table.filter(columns1, comparisons1);
        cout << "filter Test Failed! Did not catch type mismatch."  << endl;
    } catch(Table::type_mismatch e) {
        cout << e.what() << endl;
    }

    try {
        vector<::database::Row> bad_rows2 = table.filter(columns2, comparisons2);
        cout << "filter Test Failed! Did not catch type mismatch."  << endl;
    } catch(Table::type_mismatch e) {
        cout << e.what() << endl;
    }
}

// Stardard tests for the edit method
void edit_test_standard(Table &table) {
    /*cout << "Starting Update Tests..." << endl;
    
    vector<string> columns1 = {"float1", "string"};
    vector<string> columns2 = {"int", "string", "float2"};
    vector<string> columns3 = {"boolean"};


    table.edit_rows(columns1, comparisons1, columns2, comparisons2);
    assert(table.filter(columns2, comparisons2).size() == 3);
    assert(table.filter(columns2, comparisons2)[0].entries(2).flt() == 3.0);
    assert(table.filter(columns2, comparisons2)[1].entries(1).flt() == 11.2f);
    assert(table.filter(columns2, comparisons2)[1].entries(3).str() == table.filter(columns2, comparisons2)[2].entries(3).str());
    assert(table.filter(columns2, comparisons2)[1].entries(3).str() == "friend");

    table.edit_rows(columns2, comparisons2, columns1, comparisons1);
    assert(table.filter(columns1, comparisons1).size() == 3);
    assert(table.filter(columns1, comparisons1)[0].entries(2).flt() == 3.0f);
    assert(table.filter(columns1, comparisons1)[0].entries(0).num() == 1);
    
    table.edit_rows(columns3, comparisons3, columns3, comparisons4);
    assert(table.filter(columns3, comparisons4).size() == 4);
    
    cout << "Passed Update Tests!" << endl;*/
}