#include "e_algorithms.h"
#include "coursera_algorithms.h"
#include <string>
#include <initializer_list>
#include <functional>
void main_insertsort()
{
    using algorithms::insert_sort;
    int nums[10] = {2, 3, 1, 62, 12, 7, 95, 21, 6, 33};
    // int nums[4] = {2,3,1,0};
    int *p = insert_sort(nums, 10);
    for (int i = 0; i < 10; i++)
    {
        cout << *(p++) << " ";
    }
    cout << endl;
}

void main_quickfind(){
    using coursera::quickfind;
    quickfind qf(10);
    qf.union_(1,2);
    qf.union_(3,4);
    qf.union_(1,6);
    cout << qf.connected(2,6) << " ";
}


class A{
public:
    A(string s_) : s(s_){}
    A(initializer_list<string> il)
    const string& str()const {return s;}
private:
    int i;
    string s;
};

bool operator==(const A &lhs, const A &rhs){
    return lhs.str() == rhs.str();
}

size_t hasher(const A& a){
    return hash<string>()(a.str());
}

void main_multi_set_map(){
    using SD_multiset = unordered_set<A, decltype(hasher)*>;
    SD_multiset sd_set("q", hasher);

}

