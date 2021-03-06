#include <algorithm>
#include <functional>
#include <memory>
#include <random>
#include <string>
#include "coursera_algorithms.h"
#include "e_algorithms.h"
// #include "ds.h"
#include <boost/pool/pool_alloc.hpp>
#include <exception>
#include <list>
#include <map>
#include <thread>
#include <type_traits>
#include <vector>
#include "bintree/bst_header.h"
#include "graph/graph_headers.h"
#include "stl.h"
#include <fstream>
#include <deque>
#include <set>
#include <unordered_set>
#include <numeric>
#include <ext/numeric>
#include "boost_tests/timer_tests.h"
#include "primer/template.h"
// #include <windows.h>
// #include "microtime.h"

//定义一个函数可以计算一个函数调用所用的时间间隔
// return ms

// template <typename T, typename... Args>
// using bool_fun_type = bool (T::*)(const Args&... args);
// template <typename T, typename... Args>
// using void_fun_type = void (T::*)(const Args&... args);

// template <typename T, typename... Args>
// double timeuse(T &t, (bool (T::*)(const Args&...)) f, const Args&... args){
//     SYSTEMTIME time1, time2;
//     GetLocalTime(&time1);
//     t.*f(args...);
//     GetLocalTime(&time2);
//     return time2.wMilliseconds - time1.wMilliseconds;
// }

// template <typename T, typename... Args>
// double timeuse(T &t, void_fun_type<T, Args...> f, const Args&... args){
//     SYSTEMTIME time1, time2;
//     GetLocalTime(&time1);
//     t.*f(args...);
//     GetLocalTime(&time2);
//     return time2.wMilliseconds - time1.wMilliseconds;
// }

void main_insertsort()
{
    using algorithms::insert_sort;
    int nums[10] = {2, 3, 1, 62, 12, 7, 95, 21, 6, 33};
    // int nums[4] = {2,3,1,0};
    int *p = algorithms::insert_sort3(nums, 10);
    for (int i = 0; i < 10; i++)
        cout << *(p++) << " ";
    cout << endl;
}

void main_selectsort()
{
    int nums[10] = {2, 3, 1, 62, 12, 7, 95, 21, 6, 33};
    int *p = algorithms::selectsort2(nums, 10);
    for (int i = 0; i < 10; i++)
        cout << *(p++) << " ";
    cout << endl;
}

void main_stl()
{
    vector<int, JJ::alloctor<int>> v;
    v.push_back(12);
    vector<string, JJ::alloctor<string>> v2;
    vector<int, std::allocator<int>> v3;
    // vector<string, std::alloc> v4;
    v2.push_back("qwe");
    cout << v[0] << " " << v2[0] << endl;
}

void main_merge_sort()
{
    int nums[10] = {2, 3, 1, 62, 12, 7, 95, 21, 6, 33};
    // int *p = algorithms::merge_sort(nums, 0, 9);
    algorithms::merge_sort3(nums, 0, 9);
    for (int i = 0; i < 10; i++)
        cout << nums[i] << " ";
    cout << endl
         << algorithms::mergetimes << endl;
}

void main_binary_search()
{
    int nums[10] = {2, 3, 1, 62, 12, 7, 95, 21, 6, 33};
    algorithms::merge_sort(nums, 0, 9);
    size_t index = algorithms::binary_search2(nums, 0, 9, 12);
    cout << index << endl;
}

void main_twosum()
{
    int nums[10] = {2, 3, 1, 62, 12, 7, 95, 21, 6, 33};
    int index1 = 0, index2 = 0;
    algorithms::two_sum(nums, 10, 76, &index1, &index2);
    cout << index1 << " " << index2 << endl;
}

void main_merge_inversions()
{
    int nums[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    size_t n = algorithms::count_inversions(nums, 0, 9);
    cout << n << endl;
}

void main_quickfind()
{
    using coursera::quickfind;
    // vector<unsigned> v;
    // uniform_int_distribution<unsigned> u(0, 1000000);
    // default_random_engine e;
    // for(int i = 0; i < 1000000; i++){
    // v.push_back(u(e));
    // }
    quickfind qf(1000000);
    // for(int i = 0; i < 40000; i++){

    // }
    for (int i = 0; i < 800000; i++)
    {
        uniform_int_distribution<unsigned> u(0, 800000);
        default_random_engine e;
        qf.union_(u(e), u(e));
    }
    // auto time1 = GetSysTimeMicros();
    qf.union_(2000, 890090);
    // auto time2 = GetSysTimeMicros();
    qf.connected(200, 703902); // O(1)
                               // cout << time2 << " " << time1 << endl;
}

void main_quickunion()
{
    coursera::quickunion qu(10);
    qu.union_(1, 2);
    qu.union_(3, 4);
    qu.union_(1, 6);
    cout << qu.connected(2, 6) << " " << endl;
}

void main_weighted_quickunion()
{
    coursera::weightedquickunion wqu(10);
    wqu.union_(1, 2);
    wqu.union_(3, 4);
    wqu.union_(1, 6);
    cout << wqu.connected(2, 6) << endl;
}

class _A
{
  public:
    _A(const string &s_) : s(s_), i(0) {}
    const string &str() const { return s; }

  private:
    string s;
    int i;
};

bool eqOp(const _A &lhs, const _A &rhs) { return lhs.str() == rhs.str(); }

size_t hasher(const _A &a) { return hash<string>()(a.str()); }

void main_multi_set_map()
{
    // unordered_set<_A, decltype(hasher), decltype(eqOp)> uq;

    // unordered_set
    using SD_multiset = unordered_set<_A, decltype(hasher) *, decltype(eqOp) *>;
    SD_multiset sd_set(4, hasher, eqOp); // 4代表容器中元素的个数
    SD_multiset sd_set2(
        {_A("23"), _A("ds")}, 4, hasher,
        eqOp); //初始化列表中的元素不能实现隐式的类型转换，需要手动调用构造函数
    sd_set.insert(_A("qwe"));

    // unordered_multiset
    using msd_multiset =
        unordered_multiset<_A, decltype(hasher) *, decltype(eqOp) *>;
    msd_multiset msd_set(4, hasher, eqOp);
    msd_multiset msd_set2({_A("a"), _A("b")}, 4, hasher, eqOp);
    msd_set.insert(_A("qwe"));

    using sd_ms = unordered_map<_A, int, decltype(hasher) *, decltype(eqOp) *>;
    using md_ms =
        unordered_multimap<_A, int, decltype(hasher) *, decltype(eqOp) *>;
    sd_ms sd_map(4, hasher, eqOp);
    md_ms md_map(4, hasher, eqOp);
    sd_map.insert(
        make_pair<_A, int>(_A("asd"), 12)); // make_pair中不会进行类型自动转换
    md_map.insert(make_pair<_A, int>(_A("asd"), 12));
    md_map.insert(make_pair<_A, int>(_A("qwe"), 11));
    sd_map[_A("asss")] = 11;
    for (auto &it : md_map)
        cout << it.first.str() << " " << it.second << endl;
    cout << "bucket_count: " << md_map.bucket_count() << endl;
    cout << "max_bucket_count: " << md_map.max_bucket_count() << endl;
    cout << "bucket_size(n): " << md_map.bucket_size(2) << endl;
    cout << "bucket_size(n): " << md_map.bucket_size(3) << endl;
    cout << "bucket: " << md_map.bucket(_A("qwe")) << endl;
    cout << "bucket: " << md_map.bucket(_A("asd")) << endl;
}

void main_ds1_2()
{
    using ds::count;
    int a[] = {1, 2, 3, 4};
    cout << count(a) << endl;
}

void main_ds1_3()
{
    int a[10] = {1, 2, 3, 4};
    ds::fill(a, 2, 11, 12);
    ds::visitarray(a);
}

void main_ds1_4()
{
    int a[10] = {1, 1, 4};
    int b[10] = {2, 3, 0};
    cout << ds::inner_product(a, b) << endl;
}

void main_ds1_19()
{
    int i = 2;
    cout << ds::jiecheng(i);
}

void main_ds1_20()
{
    for (int i = 0; i < 99; i++)
    {
        cout << ds::fibonacci2(1, 2, i) << endl;
    }
    for (int i = 0; i < 67; i++)
    {
        cout << "第" << i << "项: " << ds::fibonacci(i) << endl;
    }
}
void main_ds1_21() { cout << ds::fx(5) << " " << ds::fx(7) << endl; }
///*
template <class T, class Sequence>
class ABCD;

// template <class T, class Sequence>
// bool operator==(const ABCD<T, Sequence> &x, const ABCD<T, Sequence> &y);

// template <class T>
// bool operator==(const ABCD<T, vector<T>> &x, const ABCD<T, vector<T>> &y);
//*/
template <class T, class R = vector<T>>
class ABCD
{
    // friend bool operator==<>(const ABCD &, const ABCD &);
    // friend bool operator==(const ABCD &, const ABCD &);//只是警告
    // friend bool operator==<T>(const ABCD&, const ABCD&);
  public:
    explicit ABCD(const T &t) : i(t) {}

  private:
    T i;
};

void main_non_template_friend()
{
    // ABCD<int> a(1), b(2);
    // cout << (a == b) << endl;
    // sort
}

class nodefault
{
    // private:
    nodefault() = delete;
};

// template class vector<nodefault>;

void main_no_default()
{
    // vector<nodefault> v;
    cout << "qwe" << endl;
}

template <class T>
int compare(const T &t1, const T &t2)
{
    cout << "asd" << endl;
    cout << t1 << "  " << t2 << endl;
    cout << typeid(t1).name();
    cout << *t1 << endl;
    return 0;
}

template <class T>
T fcn(T, T)
{
    cout << "asd" << endl;
    return 'c';
}

void main_compare()
{
    // compare("qwe", "asd");
    char c = 'c';
    fcn(c, 'c');
}

void main_find_max_subarray()
{
    int nums[16] = {13, -3, -5, 20, -13, -6, 13, 18,
                    20, -7, 12, -15, -22, 15, -4, 17};
    // int nums[3] = {-2,3,2};
    // int nums[16] = {-13, -3, -25, -20, -3, -16, -23, -18, -20, -7, -12, -5,
    // -22, -15, -4, -7}; algorithms::Sum s =
    // algorithms::find_maximum_subarray(nums, 0, 15);
    algorithms::Sum s = algorithms::find_maximum_subarray(nums, 15);
    cout << s.left_max_index << " " << s.right_max_index << " " << s.sum << endl;
}

//关于位或与的问题
void main_or_and()
{
    enum
    {
        __ALIGN = 8
    };
    enum
    {
        MAX_BYTES = 128
    };
    size_t bytes = 73;
    size_t temp = ~(__ALIGN - 1);
    size_t tmp2 = (bytes + __ALIGN - 1) & temp;
    cout << temp << endl;
    cout << tmp2 << endl;
}

template <class T>
struct myiter
{
    myiter() : ptr(nullptr) {}
    typedef T value_type;
    T *ptr;
    T &operator*() const { return *ptr; }
};

template <class I>
typename I::value_type func(I ite)
{
    return *ite;
}

void mian_traits()
{
    // typedef int* value_type;
    // int i =- 12;
    // value_type p = &i;
    // cout << p << endl;
    myiter<int *> m;
    cout << func(m) << endl;
}

void main_array_BT()
{
    vector<pair<int, bool>> v = {
        make_pair(0, true),
        make_pair(1, true),
        make_pair(2, true),
        make_pair(3, true),
        make_pair(4, false),
        make_pair(5, true),
        make_pair(6, false),
        make_pair(7, true),
        make_pair(8, true),
    };
    ds::array_BT<int> abt(v);
    ds::array_BT<int> abt2 = abt;
    abt2.preOrder();
    // cout << &v << endl;
    // cout << abt.height() << endl;
    // abt.preOrder();
    // cout << endl;
    // abt.inOrder();
    // cout << endl;
    // abt.postOrder();
    // abt.levelOrder();
    cout << endl;
}

void main_binary_tree()
{
    ds::binaryTreeNode<string> *root = new ds::binaryTreeNode<string>;
    ds::binaryTreeNode<string> *l1 = new ds::binaryTreeNode<string>;
    ds::binaryTreeNode<string> *l2 = new ds::binaryTreeNode<string>;
    ds::binaryTreeNode<string> *ll1 = new ds::binaryTreeNode<string>;
    ds::binaryTreeNode<string> *ll2 = new ds::binaryTreeNode<string>;
    ds::binaryTreeNode<string> *ll3 = new ds::binaryTreeNode<string>;
    ds::binaryTreeNode<string> *ll4 = new ds::binaryTreeNode<string>;
    ds::binaryTreeNode<string> *ll5 = new ds::binaryTreeNode<string>;
    ds::binaryTreeNode<string> *ll6 = new ds::binaryTreeNode<string>;
    auto ll7 = new ds::binaryTreeNode<string>;
    auto ll8 = new ds::binaryTreeNode<string>;
    root->element = "1";
    l1->element = "2";
    l2->element = "3";
    ll1->element = "4";
    ll2->element = "5";
    ll3->element = "6";
    ll4->element = "7";
    ll5->element = "8";
    ll6->element = "9";
    ll7->element = "10";
    ll8->element = "11";
    ll4->rightChild = ll8;
    root->leftChild = l1;
    root->rightChild = l2;
    l1->leftChild = ll1;
    l1->rightChild = ll2;
    l2->rightChild = ll3;
    ll1->rightChild = ll4;
    ll4->leftChild = ll5;
    ll3->leftChild = ll6;
    ll2->rightChild = ll7;

    ds::linkedBinaryTree<string> lbt(root);
    cout << lbt.height();
    // lbt.postOrder(ds::myvisit);
    // ds::linkedBinaryTree<string> lbt2 = lbt;
    // lbt.preOrder(ds::myvisit);
    // lbt.levelOrder(ds::myvisit);
    cout << endl;
    // lbt.inOrder(ds::myvisit);
    // cout << (lbt == lbt2);
    // lbt.inOrder(ds::myvisit);
    // lbt.swap_trees();
    // lbt.inOrder(ds::myvisit);
}

void main_delete_noheap()
{
    int a = 12, *p = &a;
    delete p;
    cout << "asd" << *p << endl;
}

void main_max_heap()
{
    // int arr[20] = {0,2,4,7,3,5,9,6,1,10,0,0,0};
    int arr[30] = {0, 3, 5, 6, 7, 20, 8, 2, 9, 12, 15, 30, 17};
    algorithms::maxheap<int> mx;
    // mx.initialize2(arr, 9);
    mx.initialize(arr, 12);
    mx.levelOrder();
    cout << endl;
    // mx.push(11);
    // mx.levelOrder();
    // cout << endl;
    // mx.pop();
    // mx.levelOrder();
    // cout << endl << mx.m_size() << endl;
    // cout << mx.top() << endl;
}

void main_exams()
{
    int arr[30] = {0, 3, 5, 6, 7, 20, 8, 2, 9, 12, 15, 30, 17};
    algorithms::maxheap<int> mx;
    mx.initialize(arr, 12);
    mx.levelOrder();
    cout << endl;
    mx.remove(5);
    // mx.push(15);
    // mx.push(20);
    // mx.push(45);
    mx.levelOrder();
    // cout << endl;
    // mx.pop();
    // mx.pop();
    // mx.pop();
    // mx.pop();
    // mx.levelOrder();
}

void main_minheap()
{
    int arr[30] = {0, 3, 5, 6, 7, 20, 8, 2, 9, 12, 15, 30, 17};
    algorithms::minheap<int> mh;
    mh.initialize(arr, 12);
    mh.levelOrder();
    cout << endl;
    algorithms::minheap<int> mh2 = mh;
    mh.levelOrder();
    // mh.push(1);
    // mh.levelOrder();
    // cout << endl;
    // mh.pop();
    // mh.levelOrder();
}

void main_type_traits()
{
    // typedef int arr[10];  
    // typedef int arr2[];
//     cout << std::boolalpha << std::is_array<int>::value << endl;//false
//     cout << std::is_array<int *>::value << endl;//false
//     cout << std::is_array<int[10]>::value << endl;//true
//     cout << std::is_array<arr>::value << endl;//ture, 定长数组类型
//     cout << std::is_array<arr2>::value << endl;//ture, 不定数组类型
//     cout << std::is_array<arr2>() << endl;//ture,调用integral_constant的operator _Tp()
// #if __cplusplus > 201103L
//     auto  a = is_array<arr2>();
//     cout << a() << endl;
// #endif

    // typedef void f();
    // typedef void ff(f);
    // typedef void fff(ff, ff, f);
    // typedef void ffff(fff, fff);
    // int d = 12;
    // const volatile int& cv_ref = d;
//     cout << is_function<f>::value << " " 
//          << is_function<ff>::value << " " 
//          << is_function<fff>::value << " "
//          << is_function<ffff>::value << endl;

    //decay
    // cout << "const volatile: " << endl;
    // cout << typeid(cv_ref).name() << " "
    //      << typeid(decay<decltype(cv_ref)>::type).name() << endl;
    // //函数类型，返回函数指针
    // cout << "function: "<< endl << typeid(f).name() << " ";
    // cout << typeid(decay<f>::type).name() << endl;
    // //数组返回指针
    // cout << "array: " << endl << typeid(arr2).name() << " " 
    //      << typeid(decay<arr>::type).name() << endl;
    // cout << "is_enum: " << endl << is_enum<arr>::value << endl;
}

void main_courera_max_heap()
{
    int arr[30] = {0, 3, 5, 6, 7, 20, 8, 2, 9, 12, 15, 30, 17};
    // coursera::build_heap(arr, 12);
    coursera::heap_sort(arr, 12);
    for (size_t i = 1; i <= 12; i++)
        cout << std::right << setw(3) << arr[i] << " ";
}

void main_priority_queue()
{
    int arr[30] = {0, 3, 5, 6, 7, 20, 8, 2, 9, 12, 15, 30, 17};
    size_t heap_size = 12;
    // coursera::heap_sort(arr, heap_size);
    coursera::build_heap(arr, 12);
    coursera::levelOrder(arr, heap_size);
    cout << endl;
    coursera::heap_extreact_max(arr, heap_size);
    coursera::levelOrder(arr, heap_size);
    cout << endl;
    // coursera::heap_increase_key(arr, 4, 40);
    coursera::max_heap_insert(arr, heap_size, 30);
    coursera::levelOrder(arr, heap_size);
    cout << endl;
}

// exams P92
void main_6_5_1()
{
    int arr[30] = {0, 15, 13, 9, 5, 12, 8, 7, 4, 0, 6, 2, 1};
    size_t heap_size = 12;
    coursera::build_heap(arr, heap_size);
    coursera::levelOrder(arr, heap_size);
    cout << endl;
    // coursera::heap_extreact_max(arr, heap_size);
    coursera::max_heap_insert(arr, heap_size, 10);
    coursera::levelOrder(arr, heap_size);
    cout << endl;
}

void main_min_heap()
{
    int arr[30] = {0, 15, 13, 9, 5, 12, 8, 7, 4, 0, 6, 2, 1};
    size_t heap_size = 12;
    coursera::build_min_heap(arr, heap_size);
    coursera::levelOrder(arr, heap_size);
    cout << endl;
    int min = coursera::heap_extract_min(arr, heap_size);
    coursera::levelOrder(arr, heap_size);
    cout << endl
         << std::right << setw(3) << "min: " << min << endl;
    coursera::heap_decrease_key(arr, 3, 0);
    coursera::levelOrder(arr, heap_size);
    cout << endl;
    coursera::min_heap_insert(arr, -1, heap_size);
    coursera::levelOrder(arr, heap_size);
    cout << endl;
    coursera::max_heap_delete(arr, 6, heap_size);
    coursera::levelOrder(arr, heap_size);
    cout << endl;
}

void main_offer_1()
{
    vector<vector<int>> arr = {{1, 2, 3, 4, 5},
                               {2, 3, 4, 5, 6},
                               {3, 4, 5, 6, 7},
                               {4, 5, 6, 7, 8},
                               {5, 6, 7, 8, 9}};
    cout << offer::offer_1(arr, 7) << endl;
    cout << offer::offer_1_2(arr, 7) << endl;
}

void main_merge_lists()
{
    list<int> l1 = {1, 2, 3, 4, 5};
    list<int> l2 = {2, 4, 5, 7, 9};
    list<int> l3 = {3, 4, 5, 6, 8};
    list<int> l4 = {2, 3, 8, 9, 11};
    list<int> l5 = {5, 7, 12, 13, 20};
    list<int> l6 = {0, 2, 5, 9, 12};

    vector<list<int>> v;
    v.push_back(l1);
    v.push_back(l2);
    v.push_back(l3);
    v.push_back(l4);
    v.push_back(l5);
    v.push_back(l6);

    list<int> l = coursera::mergelists(v);
    for (auto &it : l)
        cout << it << " ";
}

void main_build_maxheap2()
{
    // int arr[30] = {0, 15, 13, 9, 5, 12, 8, 7, 4, 0, 6, 2, 1};
    int arr[30] = {0, 4, 3, 5, 6, 7};
    size_t heap_size = 5;
    // coursera::build_heap2(arr, heap_size);
    coursera::build_heap(arr, heap_size);
    coursera::levelOrder(arr, heap_size);
    cout << endl;
}

void main_template_()
{
    // string *sp = ::new (nothrow) string;
    // vector<int, JJ::alloctor<int>> vp;
    // vp.push_back(1);
    list<int> l;
    // print(*sp);
}

void main_quicksort()
{
    int arr[30] = {30, 100, 19, 10, 5, 6, 2, 3, 1, 4, 9, 20};
    // int arr[30] = {2, 3, 1, 5, 6, 4, 19, 10, 9, 30, 100, 20};
    // int arr[30] = {9, 3, 18, 5, 6, 12, 19, 10, 21, 7, 4, 20};

    // int arr[30] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    // int arr[30] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    // algorithms::quicksort(arr, 0, 11);
    // algorithms::randomized_quicksort(arr, 0, 11);
    algorithms::hoare_quicksort(arr, 0, 11);
    // algorithms::quicksort2(arr, 0, 11);
    // algorithms::tail_recursive_quicksort(arr, 0, 11);
    for (size_t i = 0; i < 12; i++)
        cout << arr[i] << " ";
    cout << endl
         << "compare: " << algorithms::num << endl
         << "partition: " << algorithms::num2 << endl;
}

void main_matrix_multiply()
{
    vector<vector<int>> ma = {{1, 1, 1, 1, 1, 1},
                              {2, 2, 2, 2, 2, 2},
                              {3, 3, 3, 3, 3, 3},
                              {4, 4, 4, 4, 4, 4},
                              {5, 5, 5, 5, 5, 5}};

    vector<vector<int>> mb = {{1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}};
    vector<vector<int>> ret;
    ret.resize(5);
    for (int i = 0; i < 5; i++)
    {
        ret[i].resize(4);
    }
    algorithms::square_matrix_multiply(ma, mb, 5, 4, 6, ret);
    algorithms::visitmatrix(ma);
    algorithms::visitmatrix(mb);
    algorithms::visitmatrix(ret);
}

void main_counting_sort()
{
    // int arr[30] = {2, 3, 20, 5, 6, 6, 19, 10, 20, 5, 3, 20};
    int arr[30] = {21, 12, 42, 123, 124, 42, 12, 32,
                   16, 86, 456, 33, 237, 886, 764};
    int B[30];
    algorithms::counting_sort(arr, B, 15, 886);
    for (size_t i = 1; i < 16; i++)
        cout << B[i] << " ";
    cout << endl;
    algorithms::radix_sort(arr, 3, 15);
    for (size_t i = 0; i < 15; i++)
        cout << arr[i] << " ";
    cout << endl;
}
class test_trivial
{
  public:
    test_trivial() { cout << "default constructor called" << endl; }
    test_trivial(int _a) : a(_a) { cout << "test_trivial called" << endl; }
    test_trivial(const test_trivial &)
    {
        cout << "copy constructor called" << endl;
    }
    test_trivial &operator=(const test_trivial &) = default;

  private:
    int a;
};
//关于vector的size与capacity
void main_vector_size_capacity()
{
    // vector<test_trivial> v2(2,2);
    // vector<test_trivial> v2(2);
    vector<int> v(3, 3);
    cout << v.size() << " " << v.capacity() << endl;
    int c = 12;
    v.push_back(c);
    cout << v.size() << " " << v.capacity() << endl;
    v.push_back(1);
    cout << v.size() << " " << v.capacity() << endl;
    v.push_back(1);
    cout << v.size() << " " << v.capacity() << endl;
    v.push_back(1);
    cout << v.size() << " " << v.capacity() << endl;
}

void main_vector_insert()
{
    // int buf[10] = {10};
    // int *ia = ::new(buf) int(1);
    //    vector<test_trivial> v2(2, test_trivial(2));
    // vector<test_trivial, boost::pool_allocator<test_trivial>> v3(2,
    // boost::pool_allocator<test_trivial>());
    vector<int, boost::pool_allocator<int>> v4(2, boost::pool_allocator<int>());
    // vector<int, boost::pool_allocator<>>
    vector<int> v1;
    v1.push_back(12);
    v1.insert(v1.begin() + 1, 2);
}

class Base
{
  public:
    void print() { cout << "asd" << endl; }
    virtual void print2() { cout << "virtual" << endl; }
    virtual ~Base() {}
};

class D : public Base
{
  public:
    virtual void print2() { cout << "D" << endl; }
};

void main_dynamic_cast()
{
    Base b, *bp = &b;
    // D d, *bp = &d;
    if (D *dp = dynamic_cast<D *>(bp))
    {
        dp->print2();
        cout << "cast success" << endl;
    }
    else
        cout << "cast fail" << endl;

    Base &br = b;
    try
    {
        D &dr = dynamic_cast<D &>(br);
        dr.print2();
        cout << "cast success" << endl;
    }
    catch (bad_cast)
    {
        cout << "bad_cast" << endl;
    }
}

void main_thread() { std::thread thr(main_delete_noheap); }

void main_shellsort()
{
    int arr[30] = {21, 12, 42, 123, 124, 42, 12, 32,
                   16, 86, 456, 33, 237, 886, 764};
    algorithms::shellsort(arr, 15);
    for (int i = 0; i < 15; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

template <typename T, typename V>
typename BST<T, V>::node_pointer set_tree()
{
    auto b2 =
        new binaryTreeNode<pair<T, V>>(pair<T, V>(2, "2"), nullptr, nullptr);
    auto b5 =
        new binaryTreeNode<pair<T, string>>(pair<T, V>(5, "5"), nullptr, nullptr);
    auto b7 =
        new binaryTreeNode<pair<T, V>>(pair<T, V>(7, "7"), nullptr, nullptr);
    auto b10 =
        new binaryTreeNode<pair<T, V>>(pair<T, V>(10, "10"), nullptr, nullptr);
    auto b3 = new binaryTreeNode<pair<T, V>>(pair<T, V>(3, "3"), b2, nullptr);
    auto b1 = new binaryTreeNode<pair<T, V>>(pair<T, V>(1, "1"), nullptr, b3);
    auto b6 = new binaryTreeNode<pair<T, V>>(pair<T, V>(6, "6"), b5, b7);
    auto b4 = new binaryTreeNode<pair<T, V>>(pair<T, V>(4, "4"), b1, b6);
    auto b9 = new binaryTreeNode<pair<T, V>>(pair<T, V>(9, "9"), nullptr, b10);
    auto b11 = new binaryTreeNode<pair<T, V>>(pair<T, V>(11, "11"), b9, nullptr);
    auto b8 = new binaryTreeNode<pair<T, V>>(pair<T, V>(8, "8"), b4, b11);

    b2->setparent(b3);
    b3->setparent(b1);
    b1->setparent(b4);
    b5->setparent(b6);
    b7->setparent(b6);
    b6->setparent(b4);
    b4->setparent(b8);
    b8->setparent(nullptr);
    b9->setparent(b11);
    b10->setparent(b9);
    b11->setparent(b8);
    return b8;
}

void main_BST()
{
    auto root = set_tree<int, string>();
    BST<int, string> bst(root);
    bst.insert(pair<int, string>(18, "18"));
    bst.insert(pair<int, string>(16, "16"));
    // bst.remove(5);
    auto p = bst.search(8);
    cout << p->height();
    cout << p->height2;
    // if(p)
    //     cout << p->element.first << " " << p->element.second << endl;
    // else
    //     cout << "not found" << endl;
    cout << endl;
    bst.inOrder(myvisit<int, string>);
    cout << endl;
    // bst.outputRange(0, 18);
    // bst.inOrder(myvisit<int, string>);
    // cout << endl;
    // bst.remove(11);
    // bst.remove(8);
    // bst.inOrder(myvisit<int, string>);
    // cout << endl;
    // auto n = bst.search(18);
    // auto n4 = bst.search(5);
    // auto n2 = bst.successor(n);
    // auto n3 = bst.predecessor(n4);
    // if(n3)
    //     myvisit<int, string>(n3);
    // if(n2)
    //     myvisit<int, string>(n2);
    // myvisit<int, string>(bst.min());
    // myvisit<int, string>(bst.max());
}

void main_AVL()
{
    auto b8 = new binaryTreeNode<pair<int, string>>(pair<int, string>(8, "8"),
                                                    nullptr, nullptr);
    // BST<int, string> bst(b8);
    // bst.insert(make_pair<int, string>(4, "4"));
    // bst.insert(make_pair<int, string>(11, "11"));
    // bst.insert(make_pair<int, string>(9, "9"));
    // bst.insert(make_pair<int, string>(10, "10"));
    // bst.insert(make_pair<int, string>(6, "6"));
    // bst.insert(make_pair<int, string>(7, "7"));
    // bst.insert(make_pair<int, string>(1, "1"));
    // bst.insert(make_pair<int, string>(3, "3"));
    // bst.insert(make_pair<int, string>(2, "2"));
    // bst.insert(make_pair<int, string>(5, "5"));
    AVL<int, string> avl(b8);
    avl.insert(make_pair<int, string>(5, "5"));
    // auto p = avl.search(4);
    // cout << p->height2 << endl;
    avl.insert(make_pair<int, string>(11, "11"));
    avl.insert(make_pair<int, string>(3, "3"));
    avl.insert(make_pair<int, string>(4, "4"));
    avl.insert(make_pair<int, string>(0, "0"));
    avl.insert(make_pair<int, string>(2, "2"));
    avl.insert(make_pair<int, string>(15, "15"));
    avl.insert(make_pair<int, string>(20, "20"));
    avl.insert(make_pair<int, string>(50, "50"));
    avl.insert(make_pair<int, string>(30, "30"));
    avl.insert(make_pair<int, string>(13, "13"));
    avl.remove(5);
    avl.remove(3);
    avl.remove(0);
    avl.inOrder(myvisit<int, string>);
    cout << endl;
    // cout << p->height2 << endl;
    // auto p2 = bst.search(2);
    // cout << p2->height2 << endl;
}

void main_splay()
{
    auto b8 = new binaryTreeNode<pair<int, string>>(pair<int, string>(8, "8"),
                                                    nullptr, nullptr);
    Splay<int, string> sp(b8);
    sp.insert(make_pair<int, string>(4, "4"));
    sp.insert(make_pair<int, string>(5, "5"));
    sp.remove(5);
}

template <typename T>
void myvisit(const T &t)
{
    cout << t << " ";
}

void main_btree()
{
    BTree<string> bt(3);
    bt.insert("1");
    bt.insert("5");
    bt.insert("2");
    bt.insert("3");
    bt.insert("0");
    bt.insert("7");
    bt.insert("8");
    bt.insert("4");
    bt.insert("6");
    bt.insert("99");
    bt.insert("43");

    bt.inOrder(myvisit);
    cout << endl;
    bt.remove("7");
    bt.inOrder(myvisit);
    cout << endl;
    bt.remove("8");
    bt.inOrder(myvisit);
    cout << endl;
    bt.remove("6");
    bt.inOrder(myvisit);
    cout << endl;

    // BTree<int> bt2(10);
    // for(int i = 0; i < 50; i++){
    //     bt2.insert(rand());
    //     bt2.inOrder(myvisit);
    //     cout << endl;
    //     cout << endl;
    // }

    // cout << endl;
}

void main_map() { 
    map<int, string> m; 
    m.insert({1, "1"});
    m.insert({2, "2"});
    cout << m.at(1);
}

void main_redblack()
{
    auto b8 = new binaryTreeNode<pair<int, string>>(
        pair<int, string>(8, "8"), RB_BLACK, -1, nullptr, nullptr);
    RedBlack<int, string> rb(b8);
    rb.inOrder(myvisit);
    cout << endl;
    rb.insert(make_pair<int, string>(1, "1"));
    rb.inOrder(myvisit);
    cout << endl;
    cout << endl;
    rb.insert(make_pair<int, string>(6, "6"));
    rb.inOrder(myvisit);
    cout << endl;
    rb.insert(make_pair<int, string>(4, "4"));
    rb.inOrder(myvisit);
    cout << endl;
    rb.insert(make_pair<int, string>(13, "13"));
    rb.inOrder(myvisit);
    cout << endl;
    rb.insert(make_pair<int, string>(22, "22"));
    rb.inOrder(myvisit);
    cout << endl;
    rb.insert(make_pair<int, string>(16, "16"));
    rb.inOrder(myvisit);
    cout << endl;
    rb.insert(make_pair<int, string>(9, "9"));
    rb.inOrder(myvisit);
    cout << endl;
    rb.insert(make_pair<int, string>(14, "14"));
    rb.inOrder(myvisit);
    cout << endl;
    rb.insert(make_pair<int, string>(7, "7"));
    rb.inOrder(myvisit);
    cout << endl;
    rb.insert(make_pair<int, string>(15, "15"));
    rb.inOrder(myvisit);
    cout << endl;
    rb.remove(13);
    rb.inOrder(myvisit);
    cout << endl;
    rb.remove(22);
    rb.inOrder(myvisit);
    cout << endl;
}

/*
void main_graph()
{
  Graph_Matrix<Vertex<int>, Edge<int>> graph;
  graph.insert(0);
  graph.insert(1);
  graph.insert(2);
  graph.insert(3);
  graph.insert(4);
  graph.insert(5);
  graph.insert(6);
  graph.insert(7);
  graph.insert(8);
  graph.insert(9);
  graph.insert(10);
  graph.insert(11);
  graph.insert(Edge<int>(0), 0, 1);
  graph.insert(Edge<int>(1), 1, 2);
  graph.insert(Edge<int>(2), 2, 10);
  graph.insert(Edge<int>(2), 2, 5);
  graph.insert(Edge<int>(3), 3, 11);
  graph.insert(Edge<int>(4), 4, 8);
  //   graph.insert(Edge<int>(5), 5, 2);
  graph.insert(Edge<int>(6), 6, 4);
  graph.insert(Edge<int>(7), 7, 3);
  graph.insert(Edge<int>(8), 8, 3);
  graph.insert(Edge<int>(9), 9, 1);
  graph.insert(Edge<int>(10), 10, 1);
  graph.insert(Edge<int>(11), 11, 2);
  graph.remove(0);
  graph.bfs(6);
}
*/

void main_graph2()
{
    ifstream is;
    // int s = 0; //顶点
    is.open("./graph/graphs/tinyG.txt", _S_in);
    if (!is)
    {
        cout << "open failed" << endl;
    }
    // gra::graph g(is);
    // gra::dfs df(g, s, g.V());
    // gra::dfs df2(g, 7, g.V());
    // gra::dfs df3(g, 9, g.V());
    // cout << endl;

    //dfs
    // gra::dfspath dfsp(g, s, g.V());
    // if (dfsp.haspathto(3))
    // {
    //     stack<int> path = dfsp.pathto(3);
    //     while (!path.empty())
    //     {
    //         cout << path.top() << " " << std::flush;
    //         path.pop();
    //     }
    // }

    //bfs
    // gra::bfs bfssss(g, s, g.V());
    // if(bfssss.haspathto(3)){
    //     stack<int> path = bfssss.pathto(3);
    //     while(!path.empty()){
    //         cout << path.top() << " " << std::flush;
    //         path.pop();
    //     }
    // }

    // gra::CC connected_conponents(g);
    // cout << connected_conponents.connected(s, 6) << endl;
    // cout << connected_conponents.connected(s, 9) << endl;
    // gra::cycle cyc(g);
    // cout << cyc.hascycle() << endl;


    // cout << df.marked(s) << endl;
}

void main_digraph(){
    ifstream is;
    int s = 0; //顶点
    is.open("./graph/graphs/tinyDG.txt", _S_in);
    if (!is)
    {
        cout << "open failed" << endl;
    }
    gra::digraph dig(is);
    gra::digraph reversed_dipraph = dig.reverse();
    gra::directedDFS ddfs(dig, s);
    cout << ddfs.marked(5) << endl;
    cout << ddfs.marked(9) << endl;
    cout << ddfs.marked(2) << endl;
    gra::directedCycle directedC(dig);
    if(directedC.hasCycle()){
        stack<int> cycle = directedC.cycle();
        while(!cycle.empty()){
            cout << cycle.top() << " ";
            cycle.pop();
        }
    }
}

void main_deque(){
    deque<int> deq(2);
    cout << _Deque_iterator<int, int&, int*>::_S_buffer_size() << endl;
    cout << deq.size() << " ";
    cout << deq.max_size() << endl;
    auto ref = deq[127];
    auto it = deq.begin();
    cout << it._S_buffer_size() << endl;
    it++;
    // cout << deq._M_impl._M_map_size() << endl;
    cout << ref << endl;
}

void main_stl_rb_tree(){
    // _Rb_tree<int, string, >
}

template <typename T>
class test_template;

/*
template <typename T>
class test_template<T (T, T)>{
public:
    test_template(){}
    T print(){
        cout << 123 << endl;
    }
};
*/

void main_count_if(){
    vector<int> v = {1,2,3,4,5,6,7,8,9};
    // auto n = count_if(v.begin(), v.end(), bind2nd(less<int>(), 2));
    // auto n1 = count_if(v.begin(), v.end(), not1(bind2nd(less<int>(), 2)));
    // auto n = count_if(v.begin(), v.end(), bind(less<int>(), std::placeholders::_1, 12));
    // typedef int func(int, int);
    // test_template<func> f;
    // f.print();

    string s = "abcdefg";
    vector<string> v2;
    v2.push_back(s);
    v2.push_back("");
    function<bool (const string&)> f = &string::empty;
    auto n = find_if(v2.begin(), v2.end(), f);
    // auto fp = &string::empty;
    // auto n3 = find_if(v2.begin(), v2.end(), mem_fn(fp));
    // auto n4 = find_if(v2.begin(), v2.end(), bind(&string::empty, placeholders::_1));
    cout << *n << endl;
}

void print_bind(int a, string s){
    cout << a << " " << s << endl;
}

void print_bind2(string s, int a){
    cout << a << " " << s << endl;
}

void print_bind3(double d, int a){
    cout << d << a << endl;
}
class WJM{
public:
    bool PRINT(int d){
        cout << 123 << endl;
        return d;
    }
    int a;
};

void main_bind(){
    vector<string> v = {"12", "sd", "ge"};
    // function<void (double, int)> func = &print_bind3;
    function<bool (WJM&, int)> funcs = &WJM::PRINT;
    function<bool (const string&)> funcstring = &string::empty;
    // auto bd = bind(print_bind3, placeholders::_1, 2);
    // auto bd2 = bind(&string::empty, placeholders::_1);
    for_each(v.begin(), v.end(), bind(print_bind2, placeholders::_1, 2));
    for_each(v.begin(), v.end(), bind(print_bind, 2, placeholders::_1));

    // auto f_mem_fn = mem_fn(&WJM::PRINT);
}

void main_set(){
    // set<int> setint = {1,3,4,5,6};
    // auto p = setint.lower_bound(1);
    // cout << *p << endl;
    // auto p2 = setint.upper_bound(1);
    // cout << *p2 << endl;

    cout << typeid(decltype(main_bind)).name() << endl;
    cout << typeid(decltype(main_bind)*).name() << endl;
}

template <typename _Tp>
struct eqop{};

template <>
struct eqop<string>{
    bool operator()(const string &lh, const string &rh) const{
        return lh == rh;
    }
};
template <typename _Tp>
struct hash_func{};

template <>
struct hash_func<int>{
    size_t operator()(const int a) const {return a;}
};

template <>
struct hash_func<string>{
    size_t operator()(const string& s) const{return s.size();}
};

template <typename _Tp>
class INIT_SET{};

template <>
struct INIT_SET<int>{
    void init_set_insert(unordered_set<int, hash_func<int>> &s, int i){
        s.insert(i);
    }
};

template <>
struct INIT_SET<string>{
    void init_set_insert(unordered_set<string, hash_func<string>, eqop<string>> &s, int i){
        s.insert(to_string(i));
    }
};

template <typename _Set_type>
void init_us(_Set_type &us){
    typedef typename _Set_type::key_type value_type;
    for(int i = 0; i < 1000; i++){
        INIT_SET<value_type>().init_set_insert(us, i);
    }
}

size_t f_hash_string(const string &s){
    return s.size();
}

bool eq_string(const string& s1, const string& s2){
    return s1 == s2;
}

void main_hash_set_map(){
    //unordered_set<int>
    unordered_set<int, hash_func<int>> us_int(10);
    init_us(us_int);
    auto it_int = us_int.find(100);
    cout << *it_int << endl;

    //unordered_set<string>
    unordered_set<string, hash_func<string>, eqop<string>> us_string(10);
    init_us(us_string);
    auto it_string = us_string.find("100");
    cout << *it_string << endl << typeid(*it_string).name() << endl;

    // //使用函数指针类型的模板参数
    using us_set_hash_type = unordered_set<string, decltype(f_hash_string)*, decltype(eq_string)*>;
    us_set_hash_type us_f(12, f_hash_string, eq_string);
    us_f.insert("12");
    us_f.insert("13");
    us_f.insert("11");

    auto it_us123 = us_f.find("12");
    cout << *it_us123 << endl;
}

int accu_f(int a, int b){
    return a + b;
}
void main_stl_algorithms(){
    vector<int> v = {2,65,12,62,12,512,121,25124,12};
    // std::sort(v.begin(), v.end());
    auto i1 = accumulate(v.begin(), v.end(), 0);
    auto i2 = accumulate(v.begin(), v.end(), 0, accu_f);
    cout << i1 - i2 << endl;
    auto i3 = __gnu_cxx::power(2, 10);
        cout << i3 << endl;
    // fill_n
    iter_swap(v.begin(), v.end());
}

namespace cpp_inside{
class Base{
public:
    virtual void print(){cout << 123 << endl;}
    int _base;   
};

class A1 : virtual public Base{
public:
    virtual void print(){cout << 12 << endl;}
    int _a1;
};

class A2 : virtual public Base{
public:
    virtual void print(){cout << 34<< endl;}
    int _a2;
};

class D : public A1, public A2{
public:
    virtual void print(){cout << 6 << endl;}
    int _d;
};
}

void main_cpp_(){
    // cpp_inside::Base base, *pbase = &base;
    // cpp_inside::A1 a1, *pa1 = &a1;
    // cpp_inside::A2 a2, *pa2 = &a2;
    // cpp_inside::D d, *pd = &d;
    // base.print();
}

namespace opt_new{
template <typename T>
class Base{
public:
    Base(int base = 0) : _base(base){}
    void *operator new(size_t s) throw() {
        if(s != sizeof(Base))
            return ::operator new(s);
        return nullptr;
    }
    void print(){cout << 123 << endl;}
    int _base;
    T _t;
};
}

void main_opt_new(){
    opt_new::Base<double> *pbase = new opt_new::Base<double>;
    pbase->print();
}


void main_hello(){
    using namespace boost_test;
    hello(1);
}

void main_timer(){
    using namespace boost_test;
    // test_timer::test();
    // test_timer::test2();
    // test_timer::test3();
    test_timer::test4();
    getchar();
}

void main_multi_param_of_template_param(){
    JJ::g(1, 2, 2,2);
}