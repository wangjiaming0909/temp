#ifndef _TESTS_TESTS
#define _TESTS_TESTS

#include <iostream>
using namespace std;

namespace tests {
void test_double_add(){
    double d = 0;
    for(long i = 0; i < 1000000; i++){
        d += 0.3;
        cout << d << endl;
    }
}
    
} // tests

#endif // _TESTS_TESTS