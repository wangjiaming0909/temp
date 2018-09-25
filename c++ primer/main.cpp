#include "main_function.h" //C++ primer ??
#include "cpp.h"           //??????
#include <cstring>

void c(char *p){
    cout << "*P" << endl;
}

void c(int i){
    cout << "int" << endl;
}

void c(double d){
    cout << "double" <<endl;
}


int main(){
    int i = 1;
    // typeof(i) j = 12;
    // using std::placeholders::_1;
    // vector<string> v = {"qwe", "", "asd", "", "", "qe"};
    // function<bool (const string&)> f = &string::empty;
    // int i = count_if(v.begin(), v.end(), bind(&string::empty, _1));
    // int j = count_if(v.begin(), v.end(), mem_fn(&string::empty));
    // int k = count_if(v.begin(), v.end(), f);
    // cout << i << " " << j << " " << k <<endl;
    // main_multiple_inheritance2();
    // main_type_info();
    return 0;
    // main_exception();
    // using namespace abc;
    // abc::print(1.1);
    // c(0);
    // abc::B b;
    // b.print();
    // b.print(1);
}

int main02()
{
    while (true)
    {
        cout << "$: ";
        main_linux();
    }
    // print();
}

int main01()
{
    // main_begin_end();
    // main_array_size();
    // main_visit_containers()；
    // main_debug_delete();
    // main_compare_template();
    // main_max();
    // main_return_type();
    // main_ref_ref();
    // main_l_r_ref();
    // main_debug_rep();
    // test_16_50();
    // enum string{
    //     x1,x2, x3=10, x4,x5
    // } x;
    // cout << x << endl;

    // char buf[100] = "qwe";
    // cout << sizeof(buf);
    // char buf2[] = "123";
    // cout << sizeof(buf2);
    // main_g_();
    // main_template_print();
    // main_partial_specialization();
    // main_hash_Sales_data();
    // main_regex();
    return 0;
}

void Composition::GetData(){
	switch(interval){
	case ByDay:
		aggregatorByDay.aggregate();
		break;
	case ByWeek:
		aggregatorByWeek.aggregate();
		break;
	}
}

void Composition::GetData(){
    aggregator.agregate();
}