// test_utils.cpp
//
//
// utility functions to make running tests easier
//

#include "test_utils.h"

namespace test_utils {

// Set up filebuffer to load istream
// Called by tests to get allow driver to run on file istream
// Input: file_name -> name of test file being run on
extern std::filebuf set_up(string file_name) {
    std::filebuf fb;
    string path_to_test_file = path_to_utils + file_name;
    if(!fb.open(path_to_test_file, std::ios::in)) {
        throw runtime_error("Could not locate test file path: " + path_to_test_file);
    }

    return fb;
} // set_up()

// Given a column and entry, creates a basic EQUALs condition to allow for simple filtering
// "WHERE column=entry"
// Input: column -> column holding entry in row
// Input: entry -> comparison entry 

extern ::database::Condition create_equals_condition(string column, string entry) {
    ::database::Condition condition;
    condition.set_column(column);
    condition.set_comparator(::database::Condition::EQUALS);
    condition.set_entry(entry);
    return condition;
} // create_equals_condition()

} // test_utils