// test_utils.h
//
//
// utility functions to make running tests easier
//

#include "driver.h"
#include <iostream>
#include <fstream>
#include <string>

#ifndef test_utils_h
#define test_utils_h

namespace test_utils {

typedef ::database::Condition Condition;

const string path_to_utils = "/Users/pschwendy/Database-Project/driver/test_utils/";

// Set up filebuffer to load istream
// Called by tests to get allow driver to run on file istream
// Input: file_name -> name of test file being run on
std::filebuf set_up(string file_name);

// Given a column and entry, creates a basic EQUALs condition to allow for simple filtering
// "WHERE column=entry"
// Input: column -> column holding entry in row
// Input: entry -> comparison entry 
Condition create_equals_condition(string column, string entry);

} // test_utils

#endif // test_utils