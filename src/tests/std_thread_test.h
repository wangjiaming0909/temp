#ifndef TESTS_STD_THREAD_H_
#define TESTS_STD_THREAD_H_

#include <thread>
#include <string>
#include <iostream>
using namespace std;
namespace tests{
class std_thread_test{
public:
//every parameters that passed to thread constructor is copied 
    void test_that_all_parameters_passed_is_copied(){
        string s = "123";
        std::thread thread1{thread_call, s};
        thread1.join();
        cout << s << endl;
    }   
private:
    void thread_call_with_reference(string& s){
        s = "thread_call";
        cout << s << endl;
    }
    void thread_call_with_value(string s){
        s = "thread_call_with_value";
        cout << 
    }

};




}
#endif // TESTS_STD_THREAD_H_