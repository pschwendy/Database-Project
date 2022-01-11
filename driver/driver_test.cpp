#include "driver.h"

using namespace std;

void preprocessor_test_select(Driver driver);
void preprocessor_test_update();
void preprocessor_test_insert();
void preprocessor_test_delete();

int main () {
    Driver driver = Driver();

    preprocessor_test_select(driver);
}

void preprocessor_test_select(Driver driver) {
    string select = "column1, column2,column3   FROM table_name WHERE column5 = 'hello', column2 =4;";
    string select_ = "  * FROM table_name WHERE column5='hello';";
    
    cout << driver.preprocess_input(select) << endl;
    cout << driver.preprocess_input(select_) << endl;
}
void preprocessor_test_update() {

}
void preprocessor_test_insert() {

}
void preprocessor_test_delete() {

}
