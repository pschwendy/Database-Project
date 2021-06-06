// Peter Schwendeman
//
//
// driver.cpp
//

#include "driver.h"
#include <iostream>
#include <exception>
#include <sstream>

using namespace std;


/************
 *  PUBLIC  *
 ************/

// Opens shell for input database commands
void run() {
    string input;
    cout << "#" << endl;
    while(getline(cin, input)) {
        parse_input(input);
    }
}

/*************
 *  PRIVATE  *
 *************/

void parse_input(string &input) {
    stringstream ss(input);

    string command;
    ss >> command;

    if(command == "SELECT") {
        // parse_select(stringstream &input)
    } else if(command == "INSERT") {
        // parse_insert(stringstream &input)
    } else if(command == "UPDATE") {
        // parse_update(stringstream &input)
    }
}