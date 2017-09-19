#ifndef MAIN_FUNCTION_H_
#define MAIN_FUNCTION_H_
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <list>
#include <utility>
#include <memory>
#include <unordered_set>
#include <tuple>
#include <bitset>
#include <regex>
// #include <type_traits>
#include <fstream>

#include "template.h"
#include "exception.h"
#include "multiple_inheritance.h"
using namespace std;

// template class vector<JJ::NoDefault>;

void main_compare()
{
    char buf1[] = "abcdfas";
    char buf2[] = "qwe";
    cout << compare(buf1, buf2);
}

void main_find()
{
    using namespace JJ;
    vector<int> v1 = {0, 1, 2, 3, 4, 5, 6};
    auto it = JJ::find(v1.begin(), v1.end(), 5);
    cout << *(++it) << endl;

    list<string> l = {"qbc", "qwe", "pasd"};
    auto it2 = JJ::find(l.begin(), l.end(), "qwe");
    cout << *(++it2) << endl;
}

void main_begin_end()
{
    int buf[3] = {1, 2, 3};
    auto it3 = JJ::begin(buf);
    auto it4 = JJ::end(buf);
    *it3 = 10;
    cout << *it3 << " " << *it4 << endl;
}

void main_array_size()
{
    int buf[] = {1, 2, 3, 12, 12, 123, 1, 24, 12};
    cout << JJ::array_size(buf);
}

void main_visit_containers()
{
    vector<int> v = {1, 2, 3, 4, 5};
    list<string> l = {"abc", "lop", "qwe", "lm2", "-0l,"};
    JJ::visit_containers(v);
    JJ::visit_containers2(v);
    JJ::visit_containers(l);
    JJ::visit_containers2(l);
}

void main_debug_delete()
{
    // unique_ptr()
    shared_ptr<vector<string>> ptr(new vector<string>(), JJ::DebugDelete());
    ptr->push_back("asd");
    ptr->push_back("poqwe");
    JJ::visit_containers(*ptr);
}

void main_compare_template()
{
    //此处的类型推断是char 数组的引用
    char a = 'q';
    JJ::calc(a, 'a');
    // std::cout << JJ::compare("qwe", "asd") << " ";
    //编译错误template argument deduction/substitution failed
    //两个数组的类型不同
    // std::cout << JJ::compare("qwe", "asdf") << " ";
}

void main_max()
{
    int a = 0;
    double b = 1;
    // cout << JJ::my_max(a, b);
    cout << std::max<double>(a, b);
}

void main_return_type()
{
    set<int> s = {10, 2, 3, 4};
    JJ::visit_containers(s); //2,3,4,10 自动排序
    auto &&ref = JJ::return_r_ref(s.begin(), s.end());
    cout << ref << endl;
    ref = 1;                 //返回的是一个右值引用，因此与原set没有任何关系
    JJ::visit_containers(s); //2,3,4,10
}

void main_ref_ref()
{
    //定义一个引用的引用
    std::string s = "1bc", s2 = "abc";
    auto &ref_s = s;
    using ref = std::string &;
    ref &r = ref_s;
    r = s2;
    cout << ref_s << endl;
    cout << r << endl;
    // r = s2;
}

void main_l_r_ref()
{
    string s = "123";
    const string &r1 = s;
    string &r2 = s;
    string &&r3 = "qwe";
    const string &&r4 = "12345";

    //lrrl
    JJ::ref(r1); //const string&
    JJ::ref(r2); //string &
    JJ::ref(r3); //string &&
    JJ::ref(r4); //const string &&
    // std::forward
}

void main_debug_rep()
{
    string s("hi");
    const string *ps = &s;
    cout << JJ::debug_rep(&s) << endl;
    cout << JJ::debug_rep(s) << endl;
    cout << JJ::debug_rep(ps) << endl;
    cout << JJ::debug_rep("qwe") << endl;
}

void test_16_50()
{
    int i = 42;
    int *p = &i;
    const int ci = 0, *p2 = &ci;
    string s = "qwe";
    string *sp = &s;
    const string *s2 = sp;
    JJ::g(42);
    JJ::g(p); //
    JJ::g(ci);
    JJ::g(p2);
    JJ::f(42);
    JJ::f(p);
    JJ::f(ci);
    JJ::f(p2);
}

void main_g_()
{
    string s1, s2;
    int a1, a2;
    JJ::g(s1, a1, a2, s2);
}

void main_template_print()
{
    int i = 10;
    string s = "asd";
    // vector<int> v = {1,2,3,4};
    JJ::print(cout, i, s, 10);
}

void main_partial_specialization()
{
    string i = "asd";
    string *p = &i;
    JJ::template_C<int> t;
    t.print(); //调用原始版本
    JJ::template_C<decltype(42)> t2;
    t2.print(); //调用原始版本
    JJ::template_C<decltype(*p)> t3;
    t3.print(); //调用引用版本
    JJ::template_C<decltype(&i)> t4;
    t4.print();
    JJ::template_C<decltype(std::move(i))> t5;
    t5.print();
}

void main_hash_Sales_data()
{
    using JJ::Sales_data;
    Sales_data s1("abc", 12), s2("bcd", 13), s3("cde", 14);
    // using SD_multiset = unordered_multiset<Sales_data, hash<Sales_data>, decltype(JJ::eqOp)*>;
    // unordered_multiset<Sales_data> sDest;
    // sDest.insert(s1);
    // sDest.insert(s2);
    // sDest.insert(s3);
    // sDest.insert(s1);
    // JJ::visit_containers(sDest);//cde 14  bcd 13  abc 12  abc 12

    //unordered_set
    unordered_set<Sales_data> uset;
    uset.insert(s1);
    uset.insert(s2);
    uset.insert(s3);
    uset.insert(s1);
    JJ::visit_containers2(uset); //cde 14  bcd 13  abc 12
}

void main_regex()
{
    string pattern("[^c]ei");
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    regex r(pattern);
    smatch results;
    string test_str = "receipt friend theif receive";
    if (regex_search(test_str, results, r))
        cout << results.str() << endl;
}
void main_exception(){
    using EXCEPTION_H_::print;
    string s = "qwe";
    cout << noexcept(print(s));
}

namespace abc{
    void print(int x){cout << "int" << endl;}
    void print(const string &s){cout << "string" << endl;}
    void print(double d){cout << "double2" << endl;}


    class A{
    public:
        A(){}
        void print(){cout << "A" << endl;}
        void print(int){cout << "int" << endl;}
    };
    class B : public A{
    public:
        using A::print;//因为定义了自己的print()，因此就将A中的所有print函数都隐藏了，虽然隐藏了，但是还是存在的
        //使用using，将所有A中的print函数都引进当前作用域，可以直接调用
        void print(){cout << "B" << endl;}
        B() = default;
    };
}

void print(double d){
    cout << "double" << endl;
}

void main_multiple_inheritance(){
    using _MULTI_INHERITANCE::Inheritance;
    Inheritance in;
    cout << in.i << endl;
    in.print(cout, "ss");
}

void main_multiple_inheritance2(){

    using _MULTI_INHERITANCE2::VMI;
    VMI vmi;
    vmi.print();
    // cout << vmi.ival << " ";
    // cout << vmi.cval << " ";
    // vmi.bar(1);//父类的bar(int)被隐藏了
    // vmi.bar('q');
    // vmi.foo(1);
    // vmi.foo('q');
}

#endif //MAIN_FUNCTION_H_