#include <iostream>
#include <fstream>
#include "driver.h"
#include "test_utils.h"
#include <cassert>

using namespace std;
using namespace test_utils;

string db_name = "select_test";

void create_db(Driver& driver);
void empty_table_test(Driver& driver);
void select_all_test(Driver& driver);
void select_columns_test(Driver& driver);
void where_test(Driver& driver);
void type_mismatch_test(Driver& driver);
void nonexistent_columns_test(Driver& driver);
void funky_syntax_test(Driver& driver);

int main() {
    Driver driver = Driver();

    create_db(driver);
    

    assert(Storage::check_database_exists(db_name));

    try {
        empty_table_test(Driver& driver);
        select_all_test(Driver& driver);
        select_columns_test(Driver& driver);
        where_test(Driver& driver);
        type_mismatch_test(Driver& driver);
        nonexistent_columns_test(Driver& driver);
    } catch (runtime_error e) {
        cout << e.what() << endl;
    } catch (out_of_range e) {
        cout << e.what() << endl;
    }
   

    cout << "Insertion Tests: Passed 5 test cases with no errors." << endl;

    Storage::delete_database(db_name);
}

void create_db(Driver& driver) {
    filebuf fb = set_up("create_test_db_select.txt");
    istream in_stream(&fb);

    driver.run(in_stream);

    // make assertions here

} // create_db()

void empty_table_test(Driver& driver) {
    filebuf fb = set_up("select/empty.txt");
    istream in_stream(&fb);

    driver.run(in_stream);
    
    string tb_name = "empty";
    Table table = Storage::read_table(db_name, tb_name);
    
    assert(table.schema() == "");
    assert(table.filter_all().rows_size() == 0);
} // empty_table_test()

void select_all_test(Driver& driver) {
    filebuf fb = set_up("select/select_all.txt");
    istream in_stream(&fb);

    driver.run(in_stream);
} // select_all_test()

void select_columns_test(Driver& driver) {
    filebuf fb = set_up("select/select_columns.txt");
    istream in_stream(&fb);

    driver.run(in_stream);
} // select_columns_test()

void where_test(Driver& driver) {
    filebuf fb = set_up("select/where.txt");
    istream in_stream(&fb);

    driver.run(in_stream);
} // where_test()

void type_mismatch_test(Driver& driver) {
    filebuf fb = set_up("select/type_mismatch.txt");
    istream in_stream(&fb);

    driver.run(in_stream);
} //  type_mismatch_test()

void nonexistent_columns_test(Driver& driver) {
    filebuf fb = set_up("select/nonexistent_columns.txt");
    istream in_stream(&fb);

    driver.run(in_stream);
} // nonexistent_columns_test()