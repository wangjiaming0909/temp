#ifndef _TESTS_TESTS
#define _TESTS_TESTS

#include <iostream>
#include <thread>
#include <vector>
#include <memory>
#include <bitset>
#include <string>
#include <string.h>
#include "../recipes/bytebuf/bytebuf.h"
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

void debug_shared_ptr_and_reference_count(){
    shared_ptr<int> p{new int(10)};
    shared_ptr<int> p2 = p;
    p.~shared_ptr<int>();//主动调用析构函数
    p2.~shared_ptr<int>();
}//在程序结束时还会再调用一次析构函数，因此析构函数被调用了四次

void weak_ptr_test(){
    //初始化时, ref_count的use_count和weak_count会初始化为1
    shared_ptr<int> sp = make_shared<int>(10);
    //每将一个新的shared_ptr绑定到指针上, ref_count的use_count会加1, weak_count不会加1
    //每将一个新的weak_ptr绑定到指针上, ref_count的use_count不会加1, weak_count会加1
    //因此绑定在当前指针上的weak_ptr的数量 = weak_count - 1 (初始化为1)
    //每当一个shared_ptr从当前指针解绑时, ref_count的use_count会减1, weak_count不会减1 
    //每当一个weak_ptr从当前指针解绑时, ref_count的use_count不会变, weak_count会减1
    //当所有weak_ptr都解绑了, weak_count为1, use_count是绑定在当前指针上的shared_pr个数
    //当最后一个shared_ptr解绑时, 首先调用release, delete 指针, 之后destroy, delete this(delete 自己) 
    shared_ptr<int> sp2 = sp;
    cout << sp.use_count() << endl;//1
    weak_ptr<int> wp = sp;
    cout << sp.use_count() << endl;//1
    cout << wp.use_count() << endl;//1
}

class constructor_no_throwing_class {
public:
	constructor_no_throwing_class(int i) : i_(i){

	}
    ~constructor_no_throwing_class(){
        cout << "constructor_no_throwing_class destructor called.. " << i_ << endl;
    }

private:
    int i_;
};

class constructor_throwing_class {
public:
	constructor_throwing_class() {
		throw runtime_error("error");
	}
};

class memoryleak_when_throwing {
public:
	memoryleak_when_throwing() : p_(0), p2_(0), e_(2){
		try {
			name_ = "wangjiaming";
			p2_ = new constructor_no_throwing_class(1);
			p_ = new constructor_throwing_class();
		}
		catch (...) {
			clean_up();
			throw;
		}
	}
	~memoryleak_when_throwing() {
		cout << "in destructor..." << endl;
		clean_up();
		cout << "in destructor..." << endl;
	}

private:
	void clean_up() {
		delete p2_;
		delete p_;
		cout << "deleting" << endl;
	}
private:
	constructor_throwing_class* p_;
	constructor_no_throwing_class* p2_;
    constructor_no_throwing_class e_;
	string name_;
};

void constructor_throwing_test(){
	try {
		memoryleak_when_throwing _{};
	}
	catch (...) {
		cout << "catched.." << endl;
	}
}

class base_class_constructor_with_param{
public:
    base_class_constructor_with_param(int i) : i_(i){}
    virtual void pure_virtual_function() = 0;
private:
    int i_;
};

//如果derived_class不是template class 那么在编译这个类的时候， 需要检查其父类， 发现没有给父类构造函数传递参数, 因此编译不会通过
//然而如果使用了template， 此时，编译时只会进行很简单的检查语法， 并不会去检查其父类， 因此是可以编译通过的
template <typename T>
class derived_class : public base_class_constructor_with_param{
public:
    derived_class(T* p) : p_(p){}//未传递参数给父类
    virtual void pure_virtual_function () override {
        cout << "pure_virtual_function" << endl;
    }
private:
    T* p_;
};

void test_base_class_constructor_with_param(){
    //当你构造对象的时候， 他就会报错了，因为确实不存在父类的默认构造函数,尽管在编译时并没有进行很具体的检查
    // derived_class _{};
    // derived_class.pure_virtual_function();
}

//TODO bitset 的实现, 校验环的实现, 初始化效率很高
//? 选择排序，有交换和平移(把当前元素提出来, 放到最后)两种
//? 交换适合数组和链表， 但是平移只适合链表
//? cycle 是什么？ 一个长度为n的随机序列的cycle的个数的期望值是ln(n)
    //? 交换时其实不需要交换的次数就是cycle的个数


void test_strcpy(char* dest, const char* source){
    while((*(dest++) = *(source++))){
        ;
    }
}

void test_strcpy2(char* dest, const char* source){
    do{
        *dest = *source;
        dest++;
        source++;
    }while(*source != '\0');
}

void test_test_strcpy(){
    std::string str = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
    const char* p = str.c_str();
    char* dest = new char[100];
    memset(dest, 0, 100);
    al::timer _{__func__};
    for(int i = 0; i < 10000000; i++){
        test_strcpy(dest, p);
        assert(strncmp(dest, p, strlen(p)) == 0);
    }
    delete dest;
}

void test_test_strcpy2(){
    std::string str = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
    const char* p = str.c_str();
    char* dest = new char[100];
    memset(dest, 0, 100);
    al::timer _{__func__};
    for(int i = 0; i < 10000000; i++){
        test_strcpy2(dest, p);
        assert(strncmp(dest, p, strlen(p)) == 0);
    }
    delete dest;
}

class abstract_class{
public:
    virtual void func1() = 0;
    void func2(){
        cout << 456 << endl;
    }
};

class concrete_class : private abstract_class{
public:
    //虽然func1是private继承, 但是将它声明为public override 就可以使其变为public
    virtual void func1() override {
        cout << 123 << endl;
        func2();
    }
};

void test_private_inhertence(){
    concrete_class _{};
    _.func1();
    //_.func2();//private function 
}

void test_bytebuf(){
    bytebuf buf{};

}


} // tests

#endif // _TESTS_TESTS