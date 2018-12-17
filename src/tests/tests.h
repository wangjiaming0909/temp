#ifndef _TESTS_TESTS
#define _TESTS_TESTS

#include <iostream>
#include <thread>
using namespace std;

namespace tests {
void test_double_add(const int& length){
    double d = 0;
    for(long i = 0; i < length; i++){
        d += 0.3;
        cout << d << endl;
    }
}

void test_double_add_not_const(int x, int& length){
    double d = 0;
    for(long i = 0; i < length; i++){
        d += 0.3;
        cout << d << endl;
    }
}

void passing_arguments_to_thread(){
    int a = 10;
    // thread thread1(test_double_add, a);
    // thread thread1(test_double_add_not_const, 1, a);
    thread thread1(test_double_add, std::ref(a));
    thread1.join();
}

    
} // tests

#endif // _TESTS_TESTS