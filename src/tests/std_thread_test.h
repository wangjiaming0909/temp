#ifndef TESTS_STD_THREAD_H_
#define TESTS_STD_THREAD_H_

#include <thread>
#include <string>
#include <iostream>
#include <functional>
#include <type_traits>
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
        //although passed a reference into result_of, but it duduced into the value type
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

        // using func_type = decltype(&nonmem_thread_call_with_reference);
        // using param_type = decltype(*(&s));
        // using param_type2 = decltype(s);
        // using result_type = typename std::result_of<func_type(int&)>::type;//ok
        // using result_type = typename std::result_of<func_type(param_type)>::type;//not ok
        // using result_type = typename std::result_of<func_type(param_type2)>::type;//not ok
        // using result_type = typename std::result_of<func_type()>::type;
        // using result_type = typename std::result_of<func_type(reference_wrapper<int>)>::type;//ok  std::ref
        // typedef typename std::result_of<decltype(nonmem_thread_call_with_reference)(decltype(s))>
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