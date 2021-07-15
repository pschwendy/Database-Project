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

void edit_test_standard(Table table);
void edit_test_on_empty_table(Table table);
void edit_test_no_rows_found(Table table);
void edit_all_test(Table table);
void edit_test_type_mismatch(Table table);

void deletion_test_standard(Table table);
void deletion_test_type_mismatch(Table table);
void remove_all_test(Table table);

int main() {
    /* Creating Table */
    
    ::database::Row row1 = make_row(1, 0, 1.2f, 3.0f, "friend", "", true);
    ::database::Row row2 = make_row(-8347, 0, 11.2f, 43.0f, "hello", "", true);
    ::database::Row row3 = make_row(123, 0, 11.2f, -12.0f, "hello", "", true);
    ::database::Row row4 = make_row(-1, 0,  -298.2f, 3.2f, "nah", "", true);
    ::database::Row row5 = make_row(20, 0,  11.2f, -1.2f, "abcdef", "", false);
    
    vector<string> columns = {"int", "float1", "float2", "string", "boolean"};
    vector<string> types = {"int", "float", "float", "string", "bool"};
    
    Table table = Table(columns, types);
    Table empty_table = Table(columns, types);

    table.insert(row1);
    table.insert(row2);

    cout << "---Starting Insertion Tests---" << endl;
    bad_insertion_test_wrong_size(table);
    bad_insertion_test_type_mismatch(table);
    cout << "---Passed Insertion Tests!---" << endl;

    table.insert(row3);
    table.insert(row4);
    table.insert(row5);
    
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

    // Filter Tests
    cout << "---Starting Edit Tests---" << endl;
    edit_test_standard(table);
    edit_test_on_empty_table(empty_table);
    edit_test_no_rows_found(table);
    edit_test_type_mismatch(table);
    edit_all_test(table);
    cout << "---Passed Edit Tests---" << endl;

    // Delete Tests
    cout << "---Starting Delete Tests---" << endl;
    deletion_test_standard(table);
    deletion_test_type_mismatch(table);
    remove_all_test(table);
    cout << "---Passed Delete Tests---" << endl;
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
    ::database::Entry *entry6 = entries.add_entries();
    entry6->set_boolean(b);

    
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
    // Row shouldn't be pushable
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
    vector<string> columns1 = {"float1"};

    // Setting up lists of entries to compare each entry at the corresponding column to
    /* --- Columns 1, Comparisons 1 ---
        boolean: false                   */
    vector<::database::Entry> comparisons1;
    comparisons1.push_back(make_entry(&table, "float1", 15, 132.f, "friend", false));

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
void edit_test_standard(Table table) {
    vector<string> compare_columns = {"float1", "string"};
    vector<string> edit_columns = {"float1", "int", "string"};

    // Setting up lists of entries to compare each entry at the corresponding column to
    /* --- Columns 1, Comparisons 1 ---
        float1: 11.2
        string: hello                    */
    vector<::database::Entry> comparisons;
    comparisons.push_back(make_entry(&table, "float1", 15, 11.2, "kfdk", false));
    comparisons.push_back(make_entry(&table, "string", 15, 11.2, "hello", false));

    // Setting up lists of entries to compare each entry at the corresponding column to
    /* --- Columns 1, Comparisons 1 ---
        float1: 11.2
        string: hello                    */
    vector<::database::Entry> updations;
    updations.push_back(make_entry(&table, "float1", 15, -7.6f, "kfdk", false));
    updations.push_back(make_entry(&table, "int", 27, 11.2, "hello", false));
    updations.push_back(make_entry(&table, "string", 15, -22.1, "no", false));

    table.edit_rows(compare_columns, comparisons, edit_columns, updations);

    vector <::database::Row> filtered_rows = table.filter(edit_columns, updations);
    size_t size = filtered_rows.size();
    float first_row_float2 = filtered_rows[0].entries(2).flt(); 
    float second_row_float2 = filtered_rows[1].entries(2).flt(); 
    float second_row_float1 = filtered_rows[1].entries(1).flt();
    string first_row_string = filtered_rows[0].entries(3).str(); 
    string second_row_string = filtered_rows[1].entries(3).str();
    int first_row_int = filtered_rows[0].entries(0).num();
    bool second_row_bool = filtered_rows[1].entries(4).boolean();
    
    assert(size == 2);
    assert(first_row_float2 != second_row_float2);
    assert(second_row_float2 == -12.f);
    assert(second_row_float1 == -7.6f);
    assert(first_row_string == "no");
    assert(first_row_string == second_row_string);
    assert(first_row_int == 27);
    assert(second_row_bool == true);
}

void edit_test_on_empty_table(Table table) {
    // Arranging Test
    // Setting up column lists for filters
    vector<string> compare_columns = {"float1", "string"};
    vector<string> edit_columns = {"boolean"};

    // Setting up lists of entries to compare each entry at the corresponding column to
    /* --- compare_columns, comparisons ---
        float1: 11.2
        string: hello                    */
    vector<::database::Entry> comparisons;
    comparisons.push_back(make_entry(&table, "float1", 15, 11.2, "kfdk", false));
    comparisons.push_back(make_entry(&table, "string", 15, 11.2, "hello", false));

    /* --- Columns 3, Comparisons 3 ---
        boolean: false                   */
    vector<::database::Entry> updations;
    updations.push_back(make_entry(&table, "boolean", 15, 3.0, "friend", false));

    table.edit_rows(compare_columns, comparisons, edit_columns, updations);
    
    size_t size1 = table.filter(edit_columns, updations).size();
    size_t size2 = table.filter(compare_columns, comparisons).size();

    assert(size1 == 0);
    assert(size2 == 0);
}

void edit_all_test(Table table) {
    vector<string> edit_columns = {"float1", "int"};
    
    // Setting up lists of entries to compare each entry at the corresponding column to
    /* --- Columns 1, Comparisons 1 ---
        float1: 11.2
        string: hello                    */
    vector<::database::Entry> updations;
    updations.push_back(make_entry(&table, "float1", 15, 82.f, "kfdk", false));
    updations.push_back(make_entry(&table, "int", 52, 11.2, "hello", false));

    table.edit_all(edit_columns, updations);

    vector<::database::Row> edited_rows = table.filter(edit_columns, updations);

    size_t size = edited_rows.size();
    int row1_int = edited_rows[0].entries(0).num();
    int row3_int = edited_rows[2].entries(0).num();
    int row4_int = edited_rows[3].entries(0).num();
    float row4_float2 = edited_rows[3].entries(2).flt();
    float row3_float2 = edited_rows[2].entries(2).flt();
    float row2_float1 = edited_rows[1].entries(1).flt();
    string row3_string = edited_rows[2].entries(3).str();
    bool row1_bool = edited_rows[0].entries(4).boolean();
    string row1_string = edited_rows[0].entries(3).str();

    assert(size == 5);
    assert(row1_int == row4_int);
    assert(row3_int == 52);
    assert(row1_int == 52);
    assert(row4_float2 == 3.2f);
    assert(row3_float2 == -12.f);
    assert(row2_float1 == 82.f);
    assert(row3_string == "hello");
    assert(row1_bool == true);
    assert(row1_string == "friend");
}

void edit_test_no_rows_found(Table table) {
    // Arranging Test
    // Setting up column and comparison lists for filters
    vector<string> compare_columns = {"float1"};

    // Setting up lists of entries to compare each entry at the corresponding column to
    /* --- Columns 1, Comparisons 1 ---
        boolean: false                   */
    vector<::database::Entry> comparisons;
    comparisons.push_back(make_entry(&table, "float1", 15, 132.f, "friend", false));

    vector<string> edit_columns = {"float1", "int"};
    
    // Setting up lists of entries to compare each entry at the corresponding column to
    /* --- Columns 1, Comparisons 1 ---
        float1: 11.2
        string: hello                    */
    vector<::database::Entry> updations;
    updations.push_back(make_entry(&table, "float1", 15, 82.f, "kfdk", false));
    updations.push_back(make_entry(&table, "int", 52, 11.2, "hello", false));

    table.edit_rows(compare_columns, comparisons, edit_columns, updations);
    size_t size = table.filter(edit_columns, updations).size();

    assert(size == 0);
}

void edit_test_type_mismatch(Table table) {
    // Arranging Test
    // Setting up column and comparison lists for filters
    vector<string> compare_columns = {"boolean"};
    ::database::Entry fake_bool_entry;
    fake_bool_entry.set_num(23);
    vector<::database::Entry> fake_comparisons = {fake_bool_entry};
    
    ::database::Entry real_bool_entry;
    real_bool_entry.set_boolean(true);
    vector<::database::Entry> real_comparisons = {real_bool_entry};
    
    vector<string> edit_columns = {"float1", "string"};
    ::database::Entry fake_float_entry;
    fake_float_entry.set_str("oops");
    ::database::Entry fake_string_entry;
    fake_string_entry.set_flt(-2.0f);
    vector<::database::Entry> fake_updations = {fake_float_entry, fake_string_entry};
    
    ::database::Entry real_float_entry;
    real_float_entry.set_flt(-2.0f);
    ::database::Entry real_string_entry;
    real_string_entry.set_str("oops");
    vector<::database::Entry> real_updations = {fake_float_entry, fake_string_entry};

    try {
        table.edit_rows(compare_columns, fake_comparisons, edit_columns, real_updations);
        cout << "Update Test Failed! Did not catch comparison type mismatch."  << endl;
    } catch(Table::type_mismatch e) {
        cout << e.what() << endl;
    }

    try {
        table.edit_rows(compare_columns, real_comparisons, edit_columns, fake_updations);
        cout << "Update Test Failed! Did not catch updation type mismatch."  << endl;
    } catch(Table::type_mismatch e) {
        cout << e.what() << endl;
    }
}

void deletion_test_standard(Table table) {
    // Arranging Test
    // Setting up column lists for filters
    vector<string> columns1 = {"float1"};
    vector<string> columns2 = {"int", "float1", "string", "boolean", "float2"};
    vector<string> columns3 = {"float1", "string"};

    /* --- Columns 1, Comparisons 1 ---
        float1: -298.2f                    */
    vector<::database::Entry> comparisons1;
    comparisons1.push_back(make_entry(&table, "float1", 15, -298.2f, "friend", true));

    // Setting up lists of entries to compare each entry at the corresponding column to
    /* --- Columns 2, Comparisons 2 ---
    -8347 | 11.2 | 43.0 | hello | true
        int: -8347
        float1: 11.2f
        string: hello
        boolean: true
        float2: 43.f                      */
    vector<::database::Entry> comparisons2;
    comparisons2.push_back(make_entry(&table, "int", -8347, 11.2f, "hello", true));
    comparisons2.push_back(make_entry(&table, "float1", -8347, 11.2f, "hello", true));
    comparisons2.push_back(make_entry(&table, "string", -8347, 11.2f, "hello", true));
    comparisons2.push_back(make_entry(&table, "boolean", -8347, 11.2f, "hello", true));
    comparisons2.push_back(make_entry(&table, "float2", -8347, 43.f, "friend", true));
    
    /* --- Columns 3, Comparisons 3 ---
        float1: 11.2
        string: hello                    */
    vector<::database::Entry> comparisons3;
    comparisons3.push_back(make_entry(&table, "float1", 15, 11.2, "kfdk", false));
    comparisons3.push_back(make_entry(&table, "string", 15, 11.2, "hello", false));

    size_t size1_before = table.filter(columns1, comparisons1).size();
    size_t size2_before = table.filter(columns2, comparisons2).size();
    size_t size3_before = table.filter(columns3, comparisons3).size();

    table.remove_rows(columns1, comparisons1);
    table.remove_rows(columns2, comparisons2);
    table.remove_rows(columns3, comparisons3);
    
    size_t size1 = table.filter(columns1, comparisons1).size();
    size_t size2 = table.filter(columns2, comparisons2).size();
    size_t size3 = table.filter(columns3, comparisons3).size();

    assert(size1_before != 0);
    assert(size2_before != 0);
    assert(size3_before != 0);

    assert(size1 == 0);
    assert(size2 == 0);
    assert(size3 == 0);
}

void deletion_test_type_mismatch(Table table) {
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
        table.remove_rows(columns1, comparisons1);
        cout << "filter Test Failed! Did not catch type mismatch."  << endl;
    } catch(Table::type_mismatch e) {
        cout << e.what() << endl;
    }

    try {
        table.remove_rows(columns2, comparisons2);
        cout << "filter Test Failed! Did not catch type mismatch."  << endl;
    } catch(Table::type_mismatch e) {
        cout << e.what() << endl;
    }
}

void remove_all_test(Table table) {
    vector<string> columns1 = {"boolean"};
    ::database::Entry bool_entry;
    bool_entry.set_boolean(true);
    vector<::database::Entry> comparisons1 = {bool_entry};

    vector<string> columns2 = {"float1", "string"};
    /* --- Columns 2, Comparisons 2 ---
        float1: 11.2
        string: hello                    */
    vector<::database::Entry> comparisons2;
    comparisons2.push_back(make_entry(&table, "float1", 15, 11.2, "kfdk", false));
    comparisons2.push_back(make_entry(&table, "string", 15, 11.2, "hello", false));

    size_t size1_before = table.filter(columns1, comparisons1).size();
    size_t size2_before = table.filter(columns2, comparisons2).size();

    table.remove_all();

    size_t size1_after = table.filter(columns1, comparisons1).size();
    size_t size2_after = table.filter(columns2, comparisons2).size();

    assert(size1_before != 0);
    assert(size2_before != 0);

    assert(size1_after == 0);
    assert(size2_after == 0);
}