#ifndef _TESTS_TESTS
#define _TESTS_TESTS

#include <iostream>
#include <thread>
#include <vector>
using namespace std;

namespace tests {
void test_double_add(const int& length){
    double d = 0;
    for(long i = 0; i < length; i++){
        d += 0.3;
        cout << d << endl;
    }
}

int test_double_add_not_const(int& length){
    double d = 0;
    for(long i = 0; i < length; i++){
        d += 0.3;
        cout << d << endl;
    }
}

void passing_arguments_to_thread(){
    int a = 10;
    // thread thread1(test_double_add, a);
    // thread thread1(test_double_add_not_const, a);
    thread thread1(test_double_add, std::ref(a));
    thread1.join();
}

template <class Fun, typename... Args>
int result_of_Fun(Fun f, Args... args){
    typedef decltype(std::declval<Fun>()(std::declval<Args>()...)) Fun_type;
    cout << typeid(Fun_type).name();
}

void test_decltype(){
    int i = 10;
    std::add_lvalue_reference<typename std::remove_reference<int>::type>::type j = std::ref(i);
    result_of_Fun(test_double_add_not_const, std::ref(i));
}

void test_vector_with_reference(){
    int i = 1;
    vector<std::reference_wrapper<int>> v_int_ref{};
    v_int_ref.reserve(10);
    v_int_ref[0] = i;
    v_int_ref[0].get() = 12;
    cout << i << endl;
}
    
} // tests

#endif // _TESTS_TESTS