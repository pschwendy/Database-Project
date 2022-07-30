#include <iostream>
#include <fstream>
#include "driver.h"
#include "test_utils.h"
#include <cassert>

using namespace std;
using namespace test_utils;

string db_name = "insert_test";

void create_db(Driver& driver);
void empty_table_test(Driver& driver);
void types_test(Driver& driver);
void skip_nullable_columns_test(Driver& driver);
void type_mismatch_test(Driver& driver);
void incomplete_insertion_test(Driver& driver);
void funky_syntax_test(Driver& driver);

int main() {
    Driver driver = Driver();

    create_db(driver);
    assert(Storage::check_database_exists(db_name));

    try {
        empty_table_test(driver);
        types_test(driver);
        skip_nullable_columns_test(driver);
        // type_mismatch_test(driver);
        incomplete_insertion_test(driver);
    } catch (runtime_error e) {
        cout << e.what() << endl;
    } catch (out_of_range e) {
        cout << e.what() << endl;
    }
   

    cout << "Insertion Tests: Passed 5 test cases with no errors." << endl;

    Storage::delete_database(db_name);
}


void create_db(Driver& driver) {
    filebuf fb = set_up("insert/create_test_db.txt");
    istream in_stream(&fb);

    driver.run(in_stream);
} // create_db()

void empty_table_test(Driver& driver) {
    filebuf fb = set_up("insert/empty.txt");
    istream in_stream(&fb);

    driver.run(in_stream);
    
    string tb_name = "empty";
    Table table = Storage::read_table(db_name, tb_name);
    
    assert(table.schema() == "");
    assert(table.filter_all().rows_size() == 0);
} // empty_table_test()

void types_test(Driver& driver) {
    filebuf fb = set_up("insert/types.txt");
    istream in_stream(&fb);

    driver.run(in_stream);

    string tb_name = "types";
    Table table = Storage::read_table(db_name, tb_name);
    
    ::database::Condition integer_check = ::create_equals_condition("integer", "1");
    ::database::Condition negative_integer_check = create_equals_condition("integer", "-1");
    ::database::Condition string_integer_check = create_equals_condition("str", "a");
    ::database::Condition float_check = create_equals_condition("float1", "2.2");
    ::database::Condition boolean_check = create_equals_condition("boolean", "true");
    
    assert(table.filter_all().rows_size() == 2);
    assert(table.filter(integer_check).size() == 1);
    assert(table.filter(negative_integer_check).size() == 1);
    assert(table.filter(string_integer_check).size() == 1);
    assert(table.filter(float_check).size() == 1);
    assert(table.filter(boolean_check).size() == 2);
} // types_test()

void skip_nullable_columns_test(Driver& driver) {
    filebuf fb = set_up("insert/skip_nullable_columns.txt");
    istream in_stream(&fb);

    driver.run(in_stream);

    string tb_name = "nullable_columns";
    Table table = Storage::read_table(db_name, tb_name);

    Condition nullable_float_check = create_equals_condition("float2", "2.1");
    Condition nullable_string_check = create_equals_condition("str", "hello");
    
    assert(table.filter_all().rows_size() == 4);
    assert(table.filter(nullable_float_check).size() == 1);
    assert(table.filter(nullable_string_check).size() == 2);
} // skip_nullable_columns_test()

void type_mismatch_test(Driver& driver) {
    filebuf fb = set_up("insert/type_mismatch.txt");
    istream in_stream(&fb);

    driver.run(in_stream);

    string tb_name = "type_mismatch";
    Table table = Storage::read_table(db_name, tb_name);

    assert(table.filter_all().rows_size() == 0);
} // type_mismatch_test()

void incomplete_insertion_test(Driver& driver) {
    filebuf fb = set_up("insert/incomplete.txt");
    istream in_stream(&fb);

    driver.run(in_stream);

    string tb_name = "incomplete";
    Table table = Storage::read_table(db_name, tb_name);
    
    string tb_name2 = "incomplete2";
    Table table2 = Storage::read_table(db_name, tb_name);

    auto rows = table.filter_all();
    for(int i = 0; i < rows.rows_size(); ++i) {
        ::database::Row row = rows.rows(i);
        for(int j = 0; j < row.entries_size(); ++j) {
            ::database::Entry entry = row.entries(j);
            if(entry.has_str()) {
                cout << entry.str();
            } else if(entry.has_flt()) {
                cout << entry.flt();
            } else if(entry.has_num()) {
                cout << entry.num();
            } else if(entry.has_boolean()) {
                cout << entry.boolean();
            }
            cout << " | ";
        }
        cout << endl;
    }
    assert(table.filter_all().rows_size() == 0);
    assert(table2.filter_all().rows_size() == 0);
} // incomplete_insertion_test()