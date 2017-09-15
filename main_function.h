#include <iostream>
#include "template.h"
#include <vector>
#include <string>
#include <list>
using namespace std;

template class vector<JJ::NoDefault>;

void main_compare(){
    char buf1[] = "abcdfas";
    char buf2[] = "qwe";
    cout << compare(buf1, buf2);
}

void main_find(){
    using namespace JJ;
    vector<int> v1 = {0, 1, 2, 3, 4, 5, 6};
    auto it = JJ::find(v1.begin(), v1.end(), 5);
    cout << *(++it) << endl;

    list<string> l = {"qbc", "qwe", "pasd"};
    auto it2 = JJ::find(l.begin(), l.end(), "qwe");
    cout << *(++it2) << endl;
}


void main_begin_end(){
    int buf[3] = {1,2,3};
    auto it3 = JJ::begin(buf);
    auto it4 = JJ::end(buf);
    *it3 = 10;
    cout << *it3 << " " << *it4 << endl;
}

void main_array_size(){
    int buf[] = {1,2,3, 12,12, 123,1,24,12};
    cout << JJ::array_size(buf);
}

void main_visit_containers(){
    vector<int> v = {1,2,3,4,5};
    list<string> l = {"abc", "lop", "qwe", "lm2", "-0l,"};
    JJ::visit_containers(v);
    JJ::visit_containers2(v);
    JJ::visit_containers(l);
    JJ::visit_containers2(l);
}

void main_debug_delete(){
    // unique_ptr()
    shared_ptr<vector<string>> ptr(new vector<string>(), JJ::DebugDelete());
    ptr->push_back("asd");
    ptr->push_back("poqwe");
    JJ::visit_containers(*ptr);
}