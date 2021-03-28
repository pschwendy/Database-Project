// Peter Schwendeman
//
//
// Row.h
//

#ifndef Row_h
#define Row_h

#include <unordered_map>
#include <string>
#include <vector>
#include "Entry.h"

using namespace std;

class Row {
    private:
        vector<Entry> entries;

    public:
        // Default Constructor
        Row() { }

        // Constructor
        // Copies input entries into entries
        Row(vector<Entry> &input_entries) {
            entries = input_entries;
        } // Row()

        // returns entry given a column
        Entry get(int column) {
            return entries[column];
        } // get()

        // edits entry given a column and new entry
        void set(int column, Entry entry) {
            entries[column] = entry;
        } // set()

        // returns entry given a column
        Entry operator[]() {
            return entries[column];
        } // operator[]()

};

#endif // Row_h