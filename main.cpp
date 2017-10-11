#include "main_functions.h"
#include "stl.h"
#include <vector>
#include <string>
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
    main_min_heap();

    return 0;
}