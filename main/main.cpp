// Database-Project
//
//
// Peter Schwendeman
// main.cpp


#include "driver/driver.h"
#include <iostream>

using namespace std;

int main() {
    Driver driver = Driver();
    driver.run(cin, cout);
}

// USE DATABASE DB_NAME
// DESERIALIZE(Database w/ DB_NAME)