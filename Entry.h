// Peter Schwendeman
//
//
// Entry.h
//

// USE PROTOCOL BUFFER INSTEAD
#ifndef Entry_h
#define Entry_h

#include <unordered_map>
#include <string>
#include <vector>
#include "entry.pb.h"

using namespace std;

template <typename T>
class Entry  {
    protected:
        enum type {
            bool,
            char,
            int,
            float,
            string
        };
        T val;
    public:
        Entry(::database::Entry proto) {
            if(val.has_str()) {

            }
        }
        Entry(char character) {
            val = character;
        }
        T get_value(){
            if(val.has_str()) {

            }
        }
        void set_value() {

        }
};

template <typename T>
class Int : public Entry {
    public:
        int get_value() {
            return val.num;
        }
        
}

#endif // Entry_h