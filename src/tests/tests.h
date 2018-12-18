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

void process(const string& s){
    cout << "process Lvalue: " << s << endl;
}
void process(string&& s){
    cout << "process Rvalue: " << s << endl;
}
template <typename T>
void doProcess(T&& param){
    //无论最终推倒出的param是一个左值还是一个右值，直接调用的都是 void process(const string& s);
    //因为右值引用其本身也是一个左值.
    process(param);
    //利用forward可以保持原来的左右值属性，调用对应的左右值版本
    process(std::forward<T>(param));
    //无论param是左值还是右值，调用forward的版本都是左值引用的版本，除非你forward再forward才会调用右值的版本
    //let's have a try
    //第一个forward(右边的)先调用左值的版本，第二个才调用右值的版本
    process(std::forward<T>(std::forward<T>(param)));
}

//remenber one thing: 右值引用本身时一个左值引用
void rl_value_test(){
    string s = "123";
    doProcess(s);
    //invoke the lvalue version
    //because rvalue_reference itself is a lvalue_reference
    doProcess(std::move(s));
}
    
} // tests

#endif // _TESTS_TESTS