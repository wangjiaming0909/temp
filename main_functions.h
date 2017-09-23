#include "e_algorithms.h"
#include "coursera_algorithms.h"
#include <string>
#include <functional>
#include "ds.h"
void main_insertsort()
{
    using algorithms::insert_sort;
    int nums[10] = {2, 3, 1, 62, 12, 7, 95, 21, 6, 33};
    // int nums[4] = {2,3,1,0};
    int *p = algorithms::insert_sort2(nums, 10);
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
    A(const string &s_) : s(s_){}
    const string& str()const {return s;}
private:
    int i;
    string s;
};

bool eqOp(const A &lhs, const A &rhs){
    return lhs.str() == rhs.str();
}

size_t hasher(const A& a){
    return hash<string>()(a.str());
}

void main_multi_set_map(){
    //unordered_set
    using SD_multiset = unordered_set<A, decltype(hasher)*, decltype(eqOp)*>;
    SD_multiset sd_set(4, hasher, eqOp);//4代表容器中元素的个数
    SD_multiset sd_set2({A("23"), A("ds")}, 4, hasher, eqOp);//初始化列表中的元素不能实现隐式的类型转换，需要手动调用构造函数
    sd_set.insert(A("qwe"));

    //unordered_multiset
    using msd_multiset = unordered_multiset<A, decltype(hasher)*, decltype(eqOp)*>;
    msd_multiset msd_set(4, hasher, eqOp);
    msd_multiset msd_set2({A("a"), A("b")}, 4, hasher, eqOp);
    msd_set.insert(A("qwe"));

    using sd_ms = unordered_map<A, int, decltype(hasher)*, decltype(eqOp)*>;
    using md_ms = unordered_multimap<A, int, decltype(hasher)*, decltype(eqOp)*>;
    sd_ms sd_map(4, hasher, eqOp);
    md_ms md_map(4, hasher, eqOp);
    sd_map.insert(make_pair<A, int>(A("asd"), 12));//make_pair中不会进行类型自动转换
    md_map.insert(make_pair<A, int>(A("asd"), 12));
    md_map.insert(make_pair<A, int>(A("qwe"), 11));
    sd_map[A("asss")] = 11;
    for(auto &it : md_map)
        cout << it.first.str() << " " << it.second << endl;
    cout << "bucket_count: " << md_map.bucket_count() << endl;
    cout << "max_bucket_count: " << md_map.max_bucket_count() << endl;
    cout << "bucket_size(n): " << md_map.bucket_size(2) << endl;
    cout << "bucket_size(n): " << md_map.bucket_size(3) << endl;
    cout << "bucket: " << md_map.bucket(A("qwe")) << endl;
    cout << "bucket: " << md_map.bucket(A("asd")) << endl;
}

void main_ds1_2(){
    using ds::count;
    int a[] = {1,2,3,4};
    cout << count(a) << endl;
}

void main_ds1_3(){
    int a[10] = {1,2,3,4};
    ds::fill(a, 2, 11, 12);
    ds::visitarray(a);
}

void main_ds1_4(){
    int a[10] = {1,1,4};
    int b[10] = {2,3,0};
    cout << ds::inner_product(a, b) << endl;
}

void main_ds1_19(){
    int i = 2;
    cout << ds::jiecheng(i);
}

void main_ds1_20(){
    cout << ds::fibonacci(10) << endl;
    cout << ds::fibonacci2(1, 2, 10) << endl;
}