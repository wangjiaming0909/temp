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
    length = 2;
    return length;
}

void passing_arguments_to_thread(){
    int a = 10;
    // thread thread1(test_double_add, a);
    // thread thread1(test_double_add_not_const, a);
    thread thread1(test_double_add, std::ref(a));
    thread1.join();
}

// template <class Fun, typename... Args>
// int result_of_Fun(Fun&& f, Args&&... args){
//     (void)f;
//     typedef decltype(std::declval<Fun>()(std::declval<Args>()...)) Fun_type;
//     cout << typeid(Fun_type).name() << endl;;
//     return 1;
// }
template <class Fun, class... Args>
struct result_of_func{
    // using result_type = decltype(std::forward<Func>())
    // std::result_of<int>
};

void test_decltype(){
    // int i = 10;
    // std::add_lvalue_reference<typename std::remove_reference<int>::type>::type j = std::ref(i);
    // std::remove_reference<int>::type&& j2 = 1;
    // result_of_Fun(test_double_add_not_const, j2);
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

//doProcess_before 的行为和forward一样
//不做forward都会调用左值引用的版本 
template <typename T>
void doProcess_before(T& param){
    cout << "doProcess_before, lvaue " << param << endl;
}
template <typename T>
void doProcess_before(T&& param){
    cout << "doProcess_before, rvalue " << param << endl;
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

    doProcess_before(param);//调用左值引用的版本
}

// template <typename T>
// void doProcess(T& param){
//     cout << "doProcess: " << "lvalue" << param << endl;
// }

//remenber one thing: 右值引用本身是一个左值引用
void rl_value_test(){
    string s = "123";
    //虽然说你定义为右值引用，但是当你把它当作参数传递出去的时候,
    //别人接受到的参数其实还是左值引用，因为右值引用自己就是一个左值引用
    //因此除非你做特殊的转型，才能把右值引用传递出去，like, move, forward, 或者static_cast
    string&& s_rref = "123";
    doProcess(s);
    //invoke the lvalue version
    //because rvalue_reference itself is a lvalue_reference

    //别人还是把他当左值引用哦，虽然你定义成了右值引用
    //你想要别人把他当作右值引用，就只能move，forward，或者cast了
    doProcess(s_rref);
    doProcess(std::move(s));
    doProcess(static_cast<string&&>(s_rref));
}

void lambda_and_auto_and_universal_reference(){
    auto timeFuncInvocation = [] (auto&& func, auto&&... param){
        al::timer _{__func__};
        return std::forward<decltype(func)>(func)(std::forward<decltype(param)>(param)...);
    };
    int i = 0;
    auto ret = timeFuncInvocation(test_double_add_not_const, i);//i will be changed by the function
    cout << ret << endl;
}

template <typename T>
void test_std_ref(T&& t){
    t++;
}

void test_std_ref2(int& i){
    i++;
}

void test_std_ref2_with_pointer(int *ip){
    (*ip)++;
    (void)ip;
}
void std_ref(){
    int i = 10;
    auto f = std::bind(test_std_ref2, i);
    f();
    cout << i << endl;
    auto f2 = std::bind(test_std_ref2, std::ref(i));
    f2();
    cout << i << endl;
    auto f3 = std::bind(test_std_ref2_with_pointer, &i);
    f3();
    cout << i << endl;
}

static string _name = "";
template <typename T>
void setName(T&& name){
    _name = std::move(name);
}

void setName_no_template(const string& name){
    _name = name;
}

void setName_no_template(string&& name){
    _name = std::move(name);
}

void test_string_literal(){
    //传的是一个char的数组, 因此setName收到的是一个数组的引用
    //name这个universal ref 就会被初始化为数组的左值引用
    //之后进行move操作，再调用string的move constructor
    setName("wangjiaming");
    //传递是一个char的数组，但是其实setName_no_template函数接受的是一个string的右值引用
    //因此需要据这个char数组构造一个string临时对象，再进行move
    setName_no_template("wangjiaming");
}

} // tests

#endif // _TESTS_TESTS