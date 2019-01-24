#ifndef _DS_MAXHEAP_PRIORITY_QUEUE
#define _DS_MAXHEAP_PRIORITY_QUEUE

#include "max_priority_queue.h"
#include <vector>
namespace ds{
//完全二叉树用数组表示较为理想
//完全二叉堆
//最后的内部节点是n/2 - 1
template <class T>
class maxheap : public maxpriorityqueue<T>{
public:
    maxheap(int capacity = 0) : heap_(), capacity_(capacity), heapsize_(0){ 
        heap_.resize(capacity_);
    }
    void push(const T& theElement);
    T remove(int i);
    bool empty() const;
    int size() const;
    const T& top();
    void pop();
    ~maxheap(){}
private:
    std::vector<T>      heap_;
    int                 capacity_;//capacity of array heap_ 
    //heapsize no need
    //heapsize == heap_.size()
    int                 heapsize_;//nums of elements in heap_
};

template <class T>
T maxheap<T>::remove(int i){
    T ret = heap_[i];
    T lastelement = heap_[heapsize_--];//记住最后一个节点，删除最后一个节点
    int currentnode = i, child = 2 * currentnode;
    while(child <= heapsize_){
        if(child < heapsize_ && heap_[child] < heap_[child+1])//判断左右子节点哪个大
            child++;
        if(lastelement >= heap_[child])//判断最后一个节点与当前child节点大小
            break;
        //将child上移一层
        heap_[currentnode] = heap_[child];
        currentnode = child;
        child *= 2;
    }
    heap_[currentnode] = lastelement;
    return ret;
}

//O(logn), 期望的复杂度是O(1), 因为插入的节点期望上升2层就会停止
template <class T>
void maxheap<T>::push(const T& theElement){
    //no need to explicitly resize, use push_back instead
    if(heapsize_ == capacity_) heap_.resize(2*heapsize_);
    int currentnode = ++heapsize_;//新插入的节点index为heapsize+1
    while(currentnode != 1 && heap_[currentnode / 2] < theElement){//如果父节点小于新插入的节点
        heap_[currentnode] = heap_[currentnode / 2];//将currentnode向下移一层
        currentnode /= 2;//currentnode = parent of itself
    }
    //currentnode = 1 或者theElement < heap_[currentnode / 2]
    heap_[currentnode] = theElement;
}

template <class T>
bool maxheap<T>::empty() const{
    return heapsize_ == 0;
}

template <class T>
int maxheap<T>::size()const {
    return heapsize_;
}

template <class T>
const T& maxheap<T>::top(){
    return heap_[1];
}

//O(logn), 期望的复杂度也是O(logn)
//删除最大值
template <class T>
void maxheap<T>::pop(){//O(lgn)
//heapsize_ - 1  需要重排堆
//获取最后一位的元素
    T lastelement = heap_[heapsize_--];
    //从根开始重排 
    int root = 1;
    int child = 2 * root;
    while(child <= heapsize_){
        if(child < heapsize_ && heap_[child] < heap_[child+1])//右节点大
            child++;
        if(lastelement >= heap_[child])
            break;
        heap_[root] = heap_[child];
        root = child;
        child *= 2;
    }
    heap_[root] = lastelement;
}
}
#endif // _DS_MAXHEAP_PRIORITY_QUEUE