#include "main_functions.h"
#include "stl.h"
#include <vector>
#include <string>
#include <sstream>
#include "boost_test.h"
using namespace std;
bool hasdigit(const string &s){
    for (size_t i = 0; i < s.size(); i++)
        if(isdigit(s[i]))
            return true;
    return false;
}

bool hasupper(const string &s){
    for (size_t i = 0; i < s.size(); i++)
        if(isupper(s[i]))
            return true;
    return false;
}

bool hasprint(const string &s){
    for (size_t i = 0; i < s.size(); i++)
        if(isprint(s[i]))
            return true;
    return false;
}

bool haslower(const string &s){
    for (size_t i = 0; i < s.size(); i++){
        if(islower(s[i]))
            return true;
    }
    return false;
}

bool alldigit(const string &s){
    for (size_t i = 0; i < s.size(); i++){
        if(!isdigit(s[i]))
            return false;
    }
    return true;
}

bool allupper(const string &s){
    for (size_t i = 0; i < s.size(); i++)
        if(!isupper(s[i]))
            return false;
    return true;
}

bool alllower(const string &s){
    for(size_t i = 0; i < s.size(); i++)
        if(!islower(s[i]))
            return false;
    return true;
}

bool allprint(const string &s){
    for (size_t i = 0; i < s.size(); i++)
        if(!isprint(s[i]))
            return false;
    return true;
}

size_t types(const string &s){
    size_t i = 0;
    if(hasprint(s))
        i++;
    if(hasdigit(s))
        i++;
    if(haslower(s))
        i++;
    if(hasprint(s))
        i++;
    return i;
}

bool digit_and_lower_or_digit_and_upper(const string &s){
    if(types(s) == 2 && hasdigit(s) && haslower(s))
        return true;
    if(types(s) == 2 && hasdigit(s) && hasupper(s))
        return true;
    return false;
}

void main_stl(){
    vector<int, JJ::alloctor<int>> v;
    v.push_back(12);
    vector<string, JJ::alloctor<string>> v2;
    vector<int, std::allocator<int>> v3;
    // vector<string, std::alloc> v4;
    v2.push_back("qwe");
    cout << v[0] << " " << v2[0] << endl;
}

void ajd(){
    cout << "ajd" << endl;
}

void main_function_pointer(){
    JJ::abc(ajd);
}

int main()
{
    // main_ds1_21();
    // main_ds1_20();
    // main_ds1_20();
    // main_ds1_2();
    // main_multi_set_map();
    // main_insertsort();
    // main_merge_sort();
    // main_binary_search();
    // main_twosum();
    // main_merge_inversions();
    // main_find_max_subarray();
    // main_or_and();

    // main_quickfind();
    // main_quickunion();
    // main_weighted_quickunion();
    // cout << "asd" << endl;
    // ABCD<int> abcd;
    // main_selectsort();
    // main_non_template_friend();
    // main_no_default();
    // main_compare();
    // main_stl();
    // main_function_pointer();
    // main_array_BT();
    // main_vector_move();
    // main_binary_tree();
    // main_delete_noheap();
    // main_max_heap();
    // main_exams();
    // main_minheap();
    // main_type_traits();
    // main_courera_max_heap();
    // main_priority_queue();
    // main_6_5_1();
    // main_min_heap();
    // main_offer_1();
    // main_merge_lists();
    // main_build_maxheap2();
    // main_template_();
    // main_scoped_ptr();
    // main_quicksort();
    // main_counting_sort();
    // main_matrix_multiply();
    main_vector_size_capacity();

    // string s;
    // vector<string> v;
    // cin >> s;
    // char sep[1];
    // cin >> sep;
    // size_t begin = 0;
    // for (size_t i = 0; i < s.size(); i++){
    //     if(s[i] == sep[0]){
    //         v.push_back(string(s, begin, i-begin));
    //         begin = i + 1;
    //     }
    // }
    // v.push_back(string(s, begin, s.size() - begin));
    // for (size_t i = 0; i < v.size(); i ++){
    //     cout << v[i] << endl;
    // }
    // return 0;

    // string username, passwd;
    // cin >> username;
    // cin >> passwd;
    // string tmp = passwd;
    // reverse(tmp.begin(), tmp.end());
    // if(passwd.size() < 8 || 
    //     username == passwd || 
    //     username == tmp || 
    //     alldigit(passwd) || 
    //     alllower(passwd) ||
    //     allupper(passwd) ||
    //     allprint(passwd) ){
    //     cout << 0;
    // }
    // if(passwd.size() >= 8 &&
    //     digit_and_lower_or_digit_and_upper()
    //     cout << 1;
    // if()
    /*
    * asdasdasdasda12
    * asda1s2da2s1d2a2sd2as2d
    * */
}
