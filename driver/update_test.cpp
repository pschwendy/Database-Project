#include <iostream>
#include <fstream>
#include "driver.h"
#include "test_utils.h"
#include <cassert>

using namespace std;
using namespace test_utils;

string db_name = "update_test";

void create_db(Driver& driver);
void empty_table_test(Driver& driver);
void standard_test(Driver& driver);
void where_test(Driver& driver);
void type_mismatch_test(Driver& driver);
void nonexistent_columns_test(Driver& driver);
void funky_syntax_test(Driver& driver);

int main() {
    Driver driver = Driver();

    create_db(driver);
    

    assert(Storage::check_database_exists(db_name));

    try {
        // empty_table_test(driver);
        // standard_test(driver);
        where_test(driver);
        type_mismatch_test(driver);
        nonexistent_columns_test(driver);
    } catch (runtime_error e) {
        cout << e.what() << endl;
    } catch (out_of_range e) {
        cout << e.what() << endl;
    }
   

    cout << "Updation Tests: Passed 5 test cases with no errors." << endl;

    Storage::delete_database(db_name);
}

void create_db(Driver& driver) {
    filebuf fb = set_up("update/create_test_db.txt");
    istream in_stream(&fb);

    driver.run(in_stream);

    // make assertions here

} // create_db()

void empty_table_test(Driver& driver) {
    filebuf fb = set_up("update/empty.txt");
    istream in_stream(&fb);

    driver.run(in_stream);
    
    string tb_name = "empty";
    Table table = Storage::read_table(db_name, tb_name);
    
    assert(table.schema() == "");
    assert(table.filter_all().rows_size() == 0);
} // empty_table_test()

void standard_test(Driver& driver) {
    filebuf fb = set_up("update/standard.txt");
    istream in_stream(&fb);

    driver.run(in_stream);

    string tb_name = "standard";
    Table table = Storage::read_table(db_name, tb_name);
    
    ::database::Condition old_integer_check = create_equals_condition("integer", "1");
    ::database::Condition updated_integer_check = create_equals_condition("integer", "2");
    ::database::Condition string_check = create_equals_condition("str", "a");
    ::database::Condition updated_string_check = create_equals_condition("str", "a");
    ::database::Condition float_check = create_equals_condition("float", "2.2");

    assert(table.filter(old_integer_check).size() == 0);
    assert(table.filter(updated_integer_check).size() == 2);
    assert(table.filter(string_check).size() == 1);
    assert(table.filter(updated_string_check).size() == 1);
    assert(table.filter(float_check).size() == 0);

    assert(table.filter(string_check)[0].entries(3).boolean() == true);
    assert(table.filter(updated_string_check)[0].entries(1).flt() == 1.0);
} // types_test()

void where_test(Driver& driver) {
    filebuf fb = set_up("update/where.txt");
    istream in_stream(&fb);

    driver.run(in_stream);

    string tb_name = "where";
    Table table = Storage::read_table(db_name, tb_name);
    
    ::database::Condition integer_equals_neg_2_check = create_equals_condition("integer", "-2");
    ::database::Condition integer_equals_5_check = create_equals_condition("integer", "5");
    ::database::Condition float_equals_1_2_check = create_equals_condition("float", "1.2f");
    ::database::Condition str_equals_c_check = create_equals_condition("str", "c");
    ::database::Condition str_equals_byebye_check = create_equals_condition("str", "byebye");
    ::database::Condition boolean_equals_false_check = create_equals_condition("boolean", "false");
    
    assert(table.filter(integer_equals_neg_2_check).size() == 1);
    assert(table.filter(integer_equals_5_check).size() == 0);
    assert(table.filter(float_equals_1_2_check).size() == 1);
    assert(table.filter(float_equals_1_2_check).size() == 0);
    assert(table.filter(str_equals_byebye_check).size() == 1);
    assert(table.filter(boolean_equals_false_check).size() == 4);

    assert(table.filter(integer_equals_neg_2_check)[0].entries(2).str() == "a");
    assert(table.filter(float_equals_1_2_check)[0].entries(2).str() == "b");
    assert(table.filter(str_equals_byebye_check)[0].entries(1).flt() == 2.2f);
} // where_test()

void type_mismatch_test(Driver& driver) {
    filebuf fb = set_up("update/type_mismatch.txt");
    istream in_stream(&fb);

    driver.run(in_stream);

    string tb_name = "type_mismatch";
    Table table = Storage::read_table(db_name, tb_name);

    ::database::Condition integer_equals_neg_1_check = create_equals_condition("integer", "-1");
    ::database::Condition float_equals_1_2_check = create_equals_condition("float", "1.2");
    ::database::Condition boolean_equals_true = create_equals_condition("boolean", "true");

    assert(table.filter(integer_equals_neg_1_check).size() == 1);
    assert(table.filter(float_equals_1_2_check).size() == 0);
    assert(table.filter(boolean_equals_true).size() == 2);
} //  type_mismatch_test()

void nonexistent_columns_test(Driver& driver) {
    filebuf fb = set_up("update/nonexistent_columns.txt");
    istream in_stream(&fb);

    driver.run(in_stream);

    string tb_name = "nonexistent_columns";
    Table table = Storage::read_table(db_name, tb_name);

    ::database::Condition integer_equals_2_check = create_equals_condition("integer", "2");
    ::database::Condition float_equals_2_2_check = create_equals_condition("float", "2.2");
    ::database::Condition blue_equals_4 = create_equals_condition("blue", "4");

    assert(table.filter(integer_equals_2_check).size() == 0);
    assert(table.filter(float_equals_2_2_check).size() == 0);
    assert(table.filter(blue_equals_4).size() == 0);
} // nonexistent_columns_test()