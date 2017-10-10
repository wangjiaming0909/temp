#include <iostream>
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
size_t left(size_t i)
{
    return i << 1;
}
size_t right(size_t i)
{
    return left(i) + 1;
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
void build_heap(int *arr, size_t heap_size)
{ //O(n)
    for (size_t i = heap_size / 2; i >= 1; i--)
        max_heapify(arr, i, heap_size);
}

void heap_sort(int *arr, size_t heap_size)
{                                           //O(nlgn)
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
    for (size_t i = 1; i < heap_size; i++)
        cout << std::right << setw(3) << arr[i];
}
//return the max element and pop the max 
int heap_extreact_max(int *arr, size_t &heap_size){//O(lgn)
    if(heap_size < 1)
        return -1;
    int max = arr[1];
    arr[1] = arr[heap_size];
    arr[heap_size] = max;
    heap_size--;
    max_heapify(arr, 1, heap_size);
    return max;
}

} //namespace coursera
