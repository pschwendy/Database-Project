// Database-Project
//
//
// Peter Schwendeman
// main.cpp


#include "driver/driver.h"
#include <iostream>

using namespace std;

int main() {
    cout << "-------STUFF--------" << endl;
    Driver driver = Driver();
    cout << "-------STUFF--------" << endl;
    driver.run(cin);
}

// USE DATABASE DB_NAME
// DESERIALIZE(Database w/ DB_NAME)