#include <iostream>
#include <vector>
#include "e_algorithms.h"
using namespace std;

namespace coursera
{
//union find
class unionfind
{
  public:
    explicit unionfind(int n) : nn(n) {}
    void union_(int p, int q);
    bool connected(int p, int q);

  private:
    int nn;
};

class quickfind
{
  public:
    //initialize id to its index
    explicit quickfind(int n) : size(n)
    { //初始化        O(N)
        id = new int[n];
        for (int i = 0; i < n; i++)
            *(id + i) = i;
    }
    //
    bool connected(int p, int q)
    { //find O(1)
        return id[p] == id[q];
    }
    //union p to q
    //set id[p] to id[q]
    void union_(int p, int q)
    { //  union   O(N)
        int x = id[p];
        for (int i = 0; i < size; i++)
            if (id[i] == x)
                id[i] = id[q];
    }
    ~quickfind()
    {
        if (id)
            delete[] id;
    }

  private:
    int *id;
    int size;
};

class quickunion
{
  public:
    explicit quickunion(int i) : size(i)
    { //初始化   O(N)
        id = new int[size];
        for (int i = 0; i < size; i++)
            id[i] = i;
    }
    bool connected(int p, int q)
    { //find worst is O(N)
        return root(p) == root(q);
    }
    void union_(int p, int q)
    { //union  O(N+)包括了find的复杂度
        id[root(p)] = id[root(q)];
    }
    ~quickunion()
    {
        if (id)
            delete[] id;
    }

  private:
    int root(int i)
    {
        while (id[i] != i)
            i = id[i];
        return i;
    }

  private:
    int *id;
    int size;
};

class weightedquickunion
{
  public:
    explicit weightedquickunion(int i) : size(i)
    { //初始化  O(N)
        id = new int[size];
        sz = new int[size];
        for (int i = 0; i < size; i++)
        {
            id[i] = i;
            sz[i] = 1;
        }
    }
    void union_(int p, int q)
    { //union的复杂度主要是root的复杂度
        //此法生成的树的高度最高为lg2(N)
        //因此  复杂度为 O(lg N)
        int i = root(p);
        int j = root(q);
        if (sz[i] < sz[j])
        {
            sz[j] += sz[i];
            id[i] = j;
        }
        else
        {
            sz[i] += sz[j];
            id[j] = i;
        }
    }
    bool connected(int p, int q)
    { //O(N)
        return root(p) == root(q);
    }
    ~weightedquickunion()
    {
        if (id)
            delete[] id;
    }

  private:
    int root(int i)
    {
        while (id[i] != i)
        {
            id[i] = id[id[i]];
            i = id[i];
        }
        return i;
    }

  private:
    int *id;
    int *sz;
    int size;
};

//max heap
//algorithms chapter 6
//left child
size_t left(size_t i){
    return i << 1;
}
size_t right(size_t i){
    return left(i) + 1;
}
size_t parent(size_t i){
    return i >> 1;
}
//initialize maxheap
//not really initialize the maxheap, just part of it
void max_heapify(int *arr, size_t i, size_t heap_size){ //O(logn)
    size_t l = left(i);
    size_t r = right(i);
    size_t largest = 0;
    if (l <= heap_size && arr[l] > arr[i])
        largest = l;
    else
        largest = i;
    if (r <= heap_size && arr[r] > arr[largest])
        largest = r;
    if (largest != i)
    {
        int temp = arr[largest];
        arr[largest] = arr[i];
        arr[i] = temp;
        max_heapify(arr, largest, heap_size);
    }
}

//from heap_size / 2 to 1 call max_heapify
void build_heap(int *arr, size_t heap_size){ //O(n)
    for (size_t i = heap_size / 2; i >= 1; i--)
        max_heapify(arr, i, heap_size);
}

void heap_sort(int *arr, size_t heap_size){//O(nlgn)
    build_heap(arr, heap_size);             //O(n)
    for (size_t i = heap_size; i >= 2; i--) //O(nlgn)
    {
        int temp = arr[1];
        arr[1] = arr[i];
        arr[i] = temp;
        heap_size -= 1;
        max_heapify(arr, 1, heap_size);
    }
}

//priority queue
//return the maximum element in the heap
int heap_maximum(int *arr){//O(1)
    return arr[1];
}

//levelOrder visit the heap
void levelOrder(int *arr, size_t heap_size){
    for (size_t i = 1; i <= heap_size; i++)
    cout << std::right << setw(3) << arr[i];
}

//return the max element and pop the max 
int heap_extreact_max(int *arr, size_t &heap_size){//O(lgn)
    if(heap_size < 1)
    return -1;
    int max = arr[1];
    arr[1] = arr[heap_size];//swap arr[1] and arr[heap-size]
    arr[heap_size] = max;
    heap_size--;
    max_heapify(arr, 1, heap_size);//heapify
    return max;
}

//set the arr[i] to key if key > arr[i]
void heap_increase_key(int *arr, size_t i, int key){
    if(key < arr[i])
    return;
    arr[i] = key;
    //in the worest, will swap for lgn times 
    while(arr[parent(i)] < key && parent(i) >= 1){//O(lgn)
        arr[i] = arr[parent(i)];
        arr[parent(i)] = key;
        i = parent(i);
    }
}

//insert a new element
//insert a new node in the heap
void max_heap_insert(int *arr, size_t &heap_size, int key){//O(lgn)
    heap_size++;
    int temp = key - 1;
    arr[heap_size] = temp;
    heap_increase_key(arr, heap_size, key);
}

void build_heap2(int *arr, size_t heap_size){//O(nlgn)
    int buf[heap_size];
    size_t size = 1;
    buf[1] = arr[1];
    for (size_t i = 2; i <= heap_size; i++){//O(n) * O(lgn)
        max_heap_insert(buf, size, arr[i]);//O(lgn)
    }
    for (size_t i = 1; i <= heap_size; i++){//O(n)
        arr[i] = buf[i];
    }
}

void max_heap_delete(int *arr, size_t i, size_t &heap_size){//O(lgn)
    int temp = arr[heap_size];
    arr[heap_size--] = arr[i];
    arr[i] = temp;
    max_heapify(arr, i, heap_size);
}

//-------------------------------------------min_heap
//assume that the left and right child tree of node i are min heap
void min_heapify(int *arr, size_t i, size_t heap_size){//O(lgn)
    size_t l = left(i);
    size_t r = right(i);
    size_t smallest = i;
    if (l <= heap_size && arr[l] < arr[i])
        smallest = l;
    if(r <= heap_size && arr[smallest ] > arr[r])
        smallest = r;
    if(i != smallest){
        int temp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp;
        min_heapify(arr, smallest, heap_size);
    }
}

void build_min_heap(int *arr, size_t heap_size){//O(n)
    for (size_t i = heap_size / 2; i >= 1; i--){
        min_heapify(arr, i, heap_size);
    }
}

int heap_minimum(int *arr){//O(1)
    return arr[1];
}

int heap_extract_min(int *arr, size_t &heap_size){
    int ret = arr[1];
    arr[1] = arr[heap_size];
    arr[heap_size--] = ret;
    min_heapify(arr, 1, heap_size);
    return ret;
}
void heap_decrease_key(int *arr, size_t i, int key){
    if(key >= arr[i])
        return;
    arr[i] = key;
    while(parent(i) && arr[parent(i)] > arr[i]){
        int temp = arr[i];
        arr[i] = arr[parent(i)];
        arr[parent(i)] = temp;
        i = parent(i);
    }
}

void min_heap_insert(int *arr, int key, size_t &heap_size){
    int temp = key + 1;
    arr[++heap_size] = temp;
    heap_decrease_key(arr, heap_size, key);
}

void min_heapify_with_index(int *arr, size_t i, size_t heap_size, size_t *index){//O(lgn)
    size_t l = left(i);
    size_t r = right(i);
    size_t smallest = i;
    if (l <= heap_size && arr[l] < arr[i])
        smallest = l;
    if(r <= heap_size && arr[smallest ] > arr[r])
        smallest = r;
    if(i != smallest){
        int temp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp;
        size_t tempindex = index[i-1];
        index[i-1] = index[smallest-1];
        index[smallest-1] = tempindex;
        min_heapify_with_index(arr, smallest, heap_size, index);
    }
}

void build_min_heap_with_index(int *arr, size_t heap_size, size_t *index){//O(n)
    for (size_t i = heap_size / 2; i >= 1; i--){
        min_heapify_with_index(arr, i, heap_size, index);
    }
}

int minheap_pop_with_index(int *arr, size_t &heap_size, size_t *index){
    int ret = arr[1];
    arr[1] = arr[heap_size--];
    index[0] = index[heap_size];
    min_heapify_with_index(arr, 1, heap_size, index);
    return ret;
}

//算法导论p93 6.5-9
//将k个有序链表重拍成1个有序链表，共n个元素
list<int> mergelists(vector<list<int>> &v){//O(nlgk)
    size_t k = v.size();
    size_t n = 0;
    for (size_t i = 0; i < k; i++){//O(k)
        n += v[i].size();
    }
        //取每一个list的最小元素创建最小堆
    list<int> ret;
    int minheap[k+1];//存最小堆
    int minheaptemp[k];
    size_t index[k];//存最小堆中每个元素对应的list索引
    for (size_t i = 0; i < k; i++){//O(k)
        minheap[i+1] = v[i].front();
        minheaptemp[i] = v[i].front();
        index[i] = i;
    }
    build_min_heap_with_index(minheap, k, index);//O(k)

    for (size_t i = 0; i < n; i++){//O(n) * O(lgk) = O(nlgk)
        ret.push_back(heap_minimum(minheap));//O(1)
        v[index[0]].pop_front();
        if(v[index[0]].size() != 0) {
            minheap[1] = v[index[0]].front();
            min_heapify_with_index(minheap, 1, k, index);//O(lgk)
        }else//此list中的元素都已经被pop了
            minheap_pop_with_index(minheap, k, index);//O(lgk)
    }
    return ret;
}

} //namespace coursera

//牛客网 剑指offer算法题 1
namespace offer{
//1
bool offer_1(vector<vector<int>> arr, int target){//O(mn)
    for (size_t i = 0; i < arr.size(); i++){
        for (size_t j = 0; j < arr[i].size(); j++){
            if(arr[i][j] == target)
                return true;
        }
    }
    return false;
}

bool offer_1_2(vector<vector<int>> array, int target){
    int i = array.size() - 1;
    size_t j = 0;
    while(i >= 0 && j < array[0].size()){
        if(array[i][j] == target)
            return true;
        else if(array[i][j] > target)
            i--;
        else if(array[i][j] < target)
            j++;
    }
    return false;
}


}//namespace offer
