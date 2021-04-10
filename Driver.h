// Peter Schwendeman
//
//
// Driver.h
//

#ifndef Driver_h
#define Driver_h

#include "Storage.h"

class Driver {
    public:
        // TODO: implement with storage system
        Driver();

        // Gets input and calls functions accordingly
        void run();

        // Closes program and tells storage class store data
        void finish();

    private:
        Database* db;
};

#endif // Driver_h