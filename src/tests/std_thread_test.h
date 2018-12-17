#ifndef TESTS_STD_THREAD_H_
#define TESTS_STD_THREAD_H_

#include <thread>
#include <string>
#include <iostream>
using namespace std;
namespace tests{

void nonmem_thread_call_with_reference(int& s){
    s = 1;
    cout << "in nonmem_thread_call_with_reference: " << s << endl;
}

class std_thread_test{
public:
//every parameters that passed to thread constructor is copied 
    void test_that_all_parameters_passed_is_copied(){
        string s = "123";
        string& s_ref = s;
        // std::thread thread1{std::bind(&std_thread_test::thread_call_with_reference, this, s_ref)};
        //it seems that even though we passed a reference into the thread, it's a value instead
        std::thread thread1{&std_thread_test::thread_call_with_reference, this, std::ref(s_ref)};
        thread1.join();
        cout << s << endl;
        cout << "-----------------------" << endl;
        thread thread2{std::bind(&std_thread_test::thread_call_with_pointer, this, &s)};
        thread2.join();
        cout << s << endl;
        cout << "-----------------------" << endl;
        int a = 10;
        // thread thread4(tests::nonmem_thread_call_with_reference, a);
        thread thread3(tests::nonmem_thread_call_with_reference, std::ref(a));
        thread3.join();
        cout << a << endl;
        cout << "-----------------------" << endl;
    }   
public:
    void thread_call_with_reference(string& s){//pass as a reference will not change the original string 
        s = "thread_call";
        cout << "in reference: " << s << endl;
    }
    void thread_call_with_pointer(string* s_ptr){
        *s_ptr = "thread_call_with_pointer";
        cout << "in pointer: " << *s_ptr << endl;
    }
};
}
#endif // TESTS_STD_THREAD_H_