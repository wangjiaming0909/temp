#include "e_algorithms.h"
#include <random>
#include "coursera_algorithms.h"
#include <string>
#include <algorithm>
#include <memory>
#include <functional>
#include "ds.h"
#include <vector>
#include <type_traits>
#include "stl.h"
#include <list>
// #include <windows.h>
// #include "microtime.h"

//定义一个函数可以计算一个函数调用所用的时间间隔
//return ms

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
    {
        cout << *(p++) << " ";
    }
    cout << endl;
}

void main_selectsort()
{
    int nums[10] = {2, 3, 1, 62, 12, 7, 95, 21, 6, 33};
    int *p = algorithms::selectsort2(nums, 10);
    for (int i = 0; i < 10; i++)
    {
        cout << *(p++) << " ";
    }
    cout << endl;
}

void main_merge_sort()
{
    int nums[10] = {2, 3, 1, 62, 12, 7, 95, 21, 6, 33};
    int *p = algorithms::merge_sort(nums, 0, 9);
    for (int i = 0; i < 10; i++)
    {
        cout << *(p++) << " ";
    }
    cout << endl;
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
    qf.connected(200, 703902); //O(1)
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

bool eqOp(const _A &lhs, const _A &rhs)
{
    return lhs.str() == rhs.str();
}

size_t hasher(const _A &a)
{
    return hash<string>()(a.str());
}

void main_multi_set_map()
{
    //unordered_set
    using SD_multiset = unordered_set<_A, decltype(hasher) *, decltype(eqOp) *>;
    SD_multiset sd_set(4, hasher, eqOp);                        //4代表容器中元素的个数
    SD_multiset sd_set2({_A("23"), _A("ds")}, 4, hasher, eqOp); //初始化列表中的元素不能实现隐式的类型转换，需要手动调用构造函数
    sd_set.insert(_A("qwe"));

    //unordered_multiset
    using msd_multiset = unordered_multiset<_A, decltype(hasher) *, decltype(eqOp) *>;
    msd_multiset msd_set(4, hasher, eqOp);
    msd_multiset msd_set2({_A("a"), _A("b")}, 4, hasher, eqOp);
    msd_set.insert(_A("qwe"));

    using sd_ms = unordered_map<_A, int, decltype(hasher) *, decltype(eqOp) *>;
    using md_ms = unordered_multimap<_A, int, decltype(hasher) *, decltype(eqOp) *>;
    sd_ms sd_map(4, hasher, eqOp);
    md_ms md_map(4, hasher, eqOp);
    sd_map.insert(make_pair<_A, int>(_A("asd"), 12)); //make_pair中不会进行类型自动转换
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
    cout << ds::fibonacci(10) << endl;
    cout << ds::fibonacci2(1, 2, 10) << endl;
}
void main_ds1_21()
{
    cout << ds::fx(5) << " " << ds::fx(7) << endl;
}
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
    int nums[16] = {13, -3, -5, 20, -13, -6, 13, 18, 20, -7, 12, -15, -22, 15, -4, 17};
    // int nums[3] = {-2,3,2};
    // int nums[16] = {-13, -3, -25, -20, -3, -16, -23, -18, -20, -7, -12, -5, -22, -15, -4, -7};
    // algorithms::Sum s = algorithms::find_maximum_subarray(nums, 0, 15);
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
typename I::value_type
func(I ite)
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
    root->element = "root";
    l1->element = "l1";
    l2->element = "l2";
    ll1->element = "ll1";
    root->leftChild = l1;
    root->rightChild = l2;
    l1->leftChild = ll1;

    ds::linkedBinaryTree<string> lbt(root);
    // ds::linkedBinaryTree<string> lbt2 = lbt;
    // // lbt.preOrder(ds::myvisit);
    // cout << endl;
    // lbt2.inOrder(ds::myvisit);
    // cout << (lbt == lbt2);
    lbt.inOrder(ds::myvisit);
    lbt.swap_trees();
    cout << endl;
    lbt.inOrder(ds::myvisit);
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
    cout << std::is_array<int>::value << endl;
    cout << std::is_array<int *>::value << endl;
    cout << std::is_array<int[10]>::value << endl;
}

void main_courera_max_heap()
{
    int arr[30] = {0, 3, 5, 6, 7, 20, 8, 2, 9, 12, 15, 30, 17};
    // coursera::build_heap(arr, 12);
    coursera::heap_sort(arr, 12);
    for (size_t i = 1; i <= 12; i++)
        cout << std::right << setw(3) << arr[i] << " ";
}

void main_priority_queue(){
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

//exams P92
void main_6_5_1(){
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

void main_min_heap(){
    int arr[30] = {0, 15, 13, 9, 5, 12, 8, 7, 4, 0, 6, 2, 1};
    size_t heap_size = 12;
    coursera::build_min_heap(arr, heap_size);
    coursera::levelOrder(arr, heap_size);
    cout << endl;
    int min = coursera::heap_extract_min(arr, heap_size);
    coursera::levelOrder(arr, heap_size);
    cout << endl << std::right << setw(3) << "min: " << min << endl;
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

void main_offer_1(){
    vector<vector<int>> arr = {
        {1, 2, 3, 4, 5},
        {2, 3, 4, 5, 6},
        {3, 4, 5, 6, 7},
        {4, 5, 6, 7, 8},
        {5, 6, 7, 8, 9}};
    cout << offer::offer_1(arr, 7) << endl;
    cout << offer::offer_1_2(arr, 7) << endl;
}

void main_merge_lists(){
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
    for(auto &it : l)
        cout << it << " ";
}

void main_build_maxheap2(){
    // int arr[30] = {0, 15, 13, 9, 5, 12, 8, 7, 4, 0, 6, 2, 1};
    int arr[30] = {0, 4, 3, 5, 6, 7};
    size_t heap_size = 5;
    // coursera::build_heap2(arr, heap_size);
    coursera::build_heap(arr, heap_size);
    coursera::levelOrder(arr, heap_size);
    cout << endl;
    
}

void main_template_(){
    // string *sp = ::new (nothrow) string;
    // vector<int, JJ::alloctor<int>> vp;
    // vp.push_back(1);
    list<int> l;
    // print(*sp);
}

void main_quicksort(){
    // int arr[30] = {30, 100, 19, 10, 5, 6, 2, 3, 1, 4, 9, 20};
    int arr[30] = {2, 3, 1, 5, 6, 4, 19, 10, 9, 30, 100, 20};
    // int arr[30] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    // int arr[30] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    algorithms::quicksort(arr, 0, 11);
    for (size_t i = 0; i < 12; i++)
        cout << arr[i] << " ";
    cout << endl
         << "compare: " << algorithms::num << endl
         << "partition: " << algorithms::num2 << endl;
}



void main_matrix_multiply(){
    vector<vector<int>> ma= {
        {1, 1, 1, 1, 1, 1},
        {2, 2, 2, 2, 2, 2},
        {3, 3, 3, 3, 3, 3},
        {4, 4, 4, 4, 4, 4},
        {5, 5, 5, 5, 5, 5}};

    vector<vector<int>> mb= {
        {1, 2, 3, 4},
        {1, 2, 3, 4},
        {1, 2, 3, 4},
        {1, 2, 3, 4},
        {1, 2, 3, 4},
        {1, 2, 3, 4}};
    vector<vector<int>> ret;
    ret.resize(5);
    for (int i = 0; i < 5; i++){
        ret[i].resize(4);
    }
        algorithms::square_matrix_multiply(ma, mb, 5, 4, 6, ret);
    algorithms::visitmatrix(ma);
    algorithms::visitmatrix(mb);
    algorithms::visitmatrix(ret);
}