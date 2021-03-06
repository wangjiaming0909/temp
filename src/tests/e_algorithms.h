#ifndef E_ALGORITHMS_H_
#define E_ALGORITHMS_H_

#include <iostream>
#include <unordered_map>
#include <iomanip>
#include <utility>
#include <unordered_set>
#include <vector>
#include <list>
#include <random>
using namespace std;
namespace algorithms
{

//
/*--------------------1-insertsort-------------------O(n2)-------------*/
//对序列中的逆序对敏感, 序列越乱,则时间更多
//当序列位完全有序时,O(n)
//并且插入排序是online算法,不需要知道全部的数据就可以一步一步排序
//升序排序
//**插入排序, 抓扑克牌, 每次抓到牌都是 在已有的牌中,从大到小(从后向前)查找插入的位置
int *insert_sort(int *nums, int n)
{
    for (int j = 1; j < n; j++)
    {
        int key = nums[j];              //从第二个元素开始，与前一个比较
        int i = j - 1;                  //取得前一个位置的index
        while (i >= 0 && nums[i] > key) //从i开始，分别与key比较，大于key就后移
        {
            nums[i + 1] = nums[i]; //向右移动元素
            i--;
        }
        nums[i + 1] = key; //最后将空出来的位置留给key
    }
    return nums;
}
//降序排序
int *insert_sort2(int *nums, int n)
{
    for (int j = 1; j < n; j++)
    {
        int key = nums[j];
        int i = j - 1;
        while (i >= 0 && nums[i] < key)
        {
            nums[i + 1] = nums[i];
            i--;
        }
        nums[i + 1] = key;
    }
    return nums;
}
//insert 的递归形式
int *insert_sort3(int *nums, int n){
    if(n >= 2){
        insert_sort3(nums, n-1);
        int last = nums[n-1];
        int i = n-2;//i为最后一个的前一个元素
        while(nums[i] > last && i >= 0){
            nums[i+1] = nums[i];//右移一格
            i--;//从最后一个的前一个元素一直比较到 当前元素 不比 保存的最后一个元素 大 时结束
        }
        nums[i+1] = last;//再把之前保存的last的值填入i+1
    }
    return nums;
}

/*--------------------1-insertsort-------------------*/
/*--------------------2-selectsort-------------------*/
//*选择排序,遍历一遍,找到最大的或者最小的,往前或者往最后扔,重新遍历剩下的部分
int* selectsort(int *nums, size_t n){//及时终止
    bool sorted = false;;
    for(size_t i = n-1; (i > 0) && !sorted; i--){//从后往前排，最大的往后扔
        sorted = true;
        int max = nums[0];
        size_t maxindex = 0;
        for(size_t j = 1; j <= i; j++){//找出0-i中的最大值, 0和1， 0大：sorted=false，然后0和2，1大1和2
            if(nums[j] > nums[maxindex])
                maxindex = j;
            else//如果在整个for循环中，都是nums[j]>nums[maxindex]，说明从0-j都是排完序的（J++， maxindex=j）
                sorted = false;
        }
        max = nums[maxindex];
        nums[maxindex] = nums[i];
        nums[i] = max;
    }
    return nums;
}

//没有及时终止
int * selectsort2(int *nums, size_t n){
    for(size_t i = n - 1; i > 0; i--){//为什么不需要=1，因为只有一个元素的时候，就不需要找最大值了
        int max = nums[0];
        size_t maxindex = 0;
        for(size_t j = 1; j <= i; j++){
            maxindex = nums[maxindex] < nums[j] ? j : maxindex;
        }
        max = nums[maxindex];
        nums[maxindex] = nums[i];
        nums[i] = max;
    }
    return nums;
}
/*---------------------shellsort--------------------O(n)-*/
void shellsort(int *nums, int size){
    //选取h-sort 序列有多种，3x + 1
    int h = 1;
    while(h < size / 3)//序列是：1， 4， 13， 40， 121， 364
        h = 3 * h + 1;
    while(h >= 1){//对每个h间隔的数组进行插入排序
        for (int i = h; i < size; i++){//从第h个开始，一直到最后，一个一个的连续和前面相隔h个元素进行比较
            for (int j = i; j >= h && nums[j] < nums[j - h]; j-=h){//小的话，就交换，一直交换到比前面的大
                int temp = nums[j];
                nums[j] = nums[j - h];
                nums[j - h] = temp;
            }
        }
        h = h / 3;//一轮完成将h/3
    }
}
/*---------------------shellsort--------------------O(n)-*/

/*--------------------3-mergesort--------------------O(n)-*/
//将数组A[p..q] 和A[q+1...r]合并
//其中这两个数组是已经排完序的

int mergetimes = 0;
void merge(int *nums, size_t p, size_t q, size_t r){
    size_t n1 = q-p+1;
    size_t n2 = r-q;

    int L[n1+1];
    int R[n2+1];
/*-------------------------------------------*/           //------------2n次拷贝   O(n)
    for(size_t i = 0; i < n1; i++)
        L[i] = nums[p+i];
    for(size_t i = 0; i < n2; i++)
        R[i] = nums[q+1+i];

    size_t i = 0, j = 0, k = p;
/*----------------------------------------------*/  //-----------------最坏情况循环2n次，O(n)
    while((i != n1) && (j != n2)){
        if(L[i] < R[j])
            nums[k++] = L[i++];
        else
            nums[k++] = R[j++];
    }
    while(i != n1)
        nums[k++] = L[i++];
    while(j != n2)
        nums[k++] = R[j++];
/*-----------------------------------------G-----*/
    mergetimes++;
}

//优缺点:
/* */
int *merge_sort(int *nums, size_t p, size_t r){//-------------------加上merge   O(nlgn)stable
    if(p < r){
        size_t q = (p+r) / 2;
        merge_sort(nums, p, q);
        merge_sort(nums, q+1, r);
        merge(nums, p ,q, r);
    }
    return nums;
}

//new insertion sort
void insertion_sort_new(int *nums, int p, int r){
    int i, j, temp;
    for(i = p+1; i <= r; i++){
        temp = nums[i];
        for(j = i - 1; j >= p && nums[j] > temp; j--)
            nums[j+1] = nums[j];
        nums[j+1] = temp;
    }
}
//merge sort optimization
//1,when the size of the array is smaller than 4 we use insertion sort
//but the insertion sort need to use the index of the array as the parm, not the size
void merge_sort2(int *nums, int p, int r){
    if(r - p < 4){//insertion sort
        insertion_sort_new(nums, p, r);
        return;
    }
    int q = (p+r) / 2;
    merge_sort2(nums, p, q);
    merge_sort2(nums, q+1, r);
    merge(nums, p, q, r);
} 
//2,
void merge_sort3(int *nums, int p, int r){
    if(r - p < 4){//insertion sort
        insertion_sort_new(nums, p, r);
        return;
    }
    int q = (p+r) / 2;
    merge_sort3(nums, p, q);
    merge_sort3(nums, q+1, r);
    //when the max of left is smallest than the min of right so we step over the merge
    if(nums[q] < nums[q+1])
        return;
    merge(nums, p, q, r);
} 
//3,reduce the times of copy array P175

//自底向上的merge sort
void merge_sort4(int *nums, int p, int r){
    int N = r-p+1;
    for(int sz = 1; sz < N; sz = sz*2){//外层循环，从1, 2, 4, 8, 16
        for(int i = 0; i < N - sz; i += sz*2){
            //内层循环，sz = 1, i从0, 2, 4, 8
            //sz = 2, i 0, 4, 8
            //sz = 4, i 0, 8, 16
            merge(nums, i, i+sz-1, std::min(i+2*sz-1, N-1));//merge i-i+sz和 i+sz+1-2*sz
        }
    }
}
/*--------------------3-mergesort-------------------*/
/*--------------------4-binaryserarch-------------------*/
//返回一个数组索引,递归
int binary_search(int *nums, const size_t p, const size_t r, const int target){//--------O(lgn)
    if(p <= r){
        size_t q = (r + p) / 2;
        if(nums[q] == target)
            return q;
        else if((p != r) && (nums[q] < target)){
            return binary_search(nums, q+1, r, target);
        }else if((p != r) && (nums[q] > target)){//当 使用twosum时，可能target被减成负数，如果不加p != r，则无限循环
            return binary_search(nums, p, q-1, target);
        }
    }
    return -1;
}

//二分查找迭代版本
int binary_search2(int *nums, size_t p, size_t r, int target){
    while(p <= r){
        size_t q = (r + p) /2;
        if(nums[q] == target)
            return q;
        else if(target > nums[q])
            p = q + 1;
        else if(target < nums[q])
            r = q - 1;
    }
    return -1;
}

/*--------------------4-binaryserarch-------------------*/
/*--------------------5-two sum -------------------------*/
//算法导论p39 练习2.3-7
//复杂度为O(nlgn) -----使用merge_sort
void two_sum(int *nums, size_t n, int target, int *index1, int *index2){//不返回index，直接返回值
    merge_sort(nums, 0, n-1);//O(nlgn)
    int arr[n];
    for(size_t i = 0; i < n; i++){
        // if()        
        arr[i] = target - nums[i];
    }
    for(size_t i = 0; i < n; i++){//O(n)
        int in1 = binary_search(nums, 0, n-1, arr[i]);//O(lgn)
        if(in1 != -1){
            *index1 = nums[i];
            *index2 = nums[in1];
            return ;
        }
    }
    *index1 = 0;
    *index2 = 0;
}

/*--------------------5-two sum -------------------------*/
/*--------------------6-找出数组中inversions对的个数 -------------------------*/
// i < j  but A[i] > A[j]
//方法：
/** 
 * 使用merge方法， L中的元素index肯定小于R中元素index，从L和R中取出所有的值，如果L[i] > L[j]，则inversions++ir
 * */
size_t merge_inversions(int *nums, size_t p, size_t q, size_t r);
size_t count_inversions(int *nums, size_t p, size_t r){
    size_t inversions = 0;
    if(p < r){
        size_t q = (r + p) / 2;
        inversions += count_inversions(nums, p, q);
        inversions += count_inversions(nums, q+1, r);
        inversions += merge_inversions(nums, p, q, r);        
    }
    return inversions;
}
//return inversions
//每当从右侧拿出元素时,左侧还剩下的元素个数就是横跨左右两个序列的逆序对
size_t merge_inversions(int *nums, const size_t p, const size_t q, const size_t r){
    size_t n1 = q - p + 1;
    size_t n2 = r - q;
    int L[n1+1];
    int R[n2+1];
    for(size_t i = 0; i < n1; i++){
        L[i] = nums[p+i];
    }
    for(size_t i = 0; i < n2; i++){
        R[i] = nums[q+1+i];
    }
    size_t i = 0, j = 0, inversions = 0, k = p;
    while((i < n1) && (j < n2)){//---------------------------------------------最坏情况下O(n)，且此时下面的两个while循环中的一个只执行一次
        if(L[i] > R[j]){
            inversions += n2-j;//左值大，右侧剩余几个都加到inversions上
            nums[k++] = L[i++];//还是一样进行排序
        }else
            nums[k++] = R[j++];
    }
    while(i != n1)
        nums[k++] = L[i++];
    while(j != n2)
        nums[k++] = R[j++];
    return inversions;
}
/*--------------------6-找出数组中inversions对的个数 -------------------------*/
/*--------------------7-找最大子数组问题 -------------------------*/

class Node{
public:
    size_t low;
    size_t mid;
    size_t high;
};
class Sum{
public:
    size_t left_max_index;
    size_t right_max_index;
    int sum;
};
//寻找跨越中点的子数组
Sum find_max_crossing_subarray(int *nums, const Node &nd){
    //将nums分为L, R, 
    //对于L, 从右向左求最大值
    //对于R, 从左到右求最大值
    int sum = 0, 
        left_max = 0, 
        right_max = 0;
    size_t left_max_index = nd.mid, right_max_index = nd.mid+1;
    bool thefirsttime = true;
    for(int i = nd.mid; i >= (int)nd.low; i--){//leftside, size_t 的问题，如果nd.mid是0, i-1就是size_t的最大整数
        sum = sum + nums[i];
        if((sum > left_max) || (thefirsttime)){
            left_max = sum;
            thefirsttime = false;
            left_max_index = i;
        }
    }
    thefirsttime = true;
    sum = 0;
    for(size_t i = nd.mid+1; i <= nd.high; i++){//right side
        sum = sum + nums[i];
        if((sum > right_max) || (thefirsttime)){
            thefirsttime = false;
            right_max = sum;
            right_max_index = i;
        }
    }
    return {left_max_index, right_max_index, right_max + left_max};
}

Sum find_maximum_subarray(int *nums, const size_t low, const size_t high){
    if(low == high)//only one element
        return {low, high, nums[low]};
    size_t mid = (high + low) / 2;
    Sum left, right, cross;
    if(low < high){
        left = find_maximum_subarray(nums, low, mid);
        right = find_maximum_subarray(nums, mid+1, high);
        cross = find_max_crossing_subarray(nums, {low, mid, high});
    }
    if((left.sum >= right.sum) && (left.sum >= cross.sum))
        return left;
    else if((right.sum >= left.sum) &&(right.sum >= cross.sum))
        return right;
    else
        return cross;
}
void print_2darray(int **nums, size_t M, size_t N){
    for(size_t i = 0; i < M; i++){
        for(size_t j = 0; j < i; j++){
            cout << std::right << setw(4) << "___";
        }
        for(size_t k = i; k < N; k++){
            cout << std::right << std::setw(4) << nums[i][k];
        }
        cout << endl;
    }
}
//暴力求解方法
Sum find_maximum_subarray(int *nums, size_t N){
    size_t left, right[N];
    int** sum = new int*[N];
    for(size_t i = 0; i < N; i++){
        sum[i] = new int[N];
    }
    for(size_t i = 0; i < N; i++){
        sum[i][i] = nums[i];
        for(size_t j = i; j < N; j++){
            sum[i][j] = (j == i) ? sum[i][j] : (nums[j] + sum[i][j-1]);
        }
    }
    print_2darray(sum, N, N);
    int max[N];
    for(size_t i = 0; i < N; i++){
        max[i] = sum[i][i];
        for(size_t j = i; j < N; j++){
            if(sum[i][j] > max[i]){
                max[i] = sum[i][j];
                right[i] = j;   
            }
        }
    }
    cout << endl;
    for(size_t i = 0; i < N; i++){
        cout << max[i] << endl;
    }
    int max_value = max[0];
    left = 0;
    for(size_t i = 0; i < N; i++){
        if(max[i] > max_value){
            max_value = max[i];
            left = i;
        }
    }
    for(size_t i = 0; i < N; i++){
        delete[] sum[i];
    }
    delete[] sum;
    return {left, right[left], max_value};
}

/*--------------------7-找最大子数组问题 -------------------------*/
/*--------------------1-maxpriorityqueue-------------------*/
//数据结构p299练习1
//使用数组线性表实现最大优先级队列
template <class T>
class maxpriorityqueue
{
  public:
    virtual ~maxpriorityqueue() {}
    virtual bool empty() const = 0;
    virtual int m_size() const = 0;
    virtual const T &top() = 0;
    virtual void pop() = 0;
    virtual void push(const T &element) = 0;
};

//max heap
template <class T>
class maxheap : public maxpriorityqueue<T>{
public:
    maxheap() : heap(nullptr), arraylength(0), heapsize(0){}
    // maxheap(T *t, size_t capacity, size_t size) : heap(t), arraylength(capacity), heapsize(size){}
    void initialize(T *theHeap, int theSize);
    void initialize2(T *theheap, int thesize);
    void push(const T& theElement);
    T remove(int i);
    bool empty() const;
    int m_size() const;
    const T& top();
    void pop();
    ~maxheap(){}
    void levelOrder(){
        for(int i = 1; i <= heapsize; i++)
            cout << std::right << setw(3) << heap[i] << " ";
    }
private:
    T       *heap;
    int  arraylength;//capacity of array heap 
    int  heapsize;//nums of elements in heap
};

template <class T>
T maxheap<T>::remove(int i){
    T ret = heap[i];
    T lastelement = heap[heapsize--];//记住最后一个节点，删除最后一个节点
    int currentnode = i, child = 2 * currentnode;
    while(child <= heapsize){
        if(child < heapsize && heap[child] < heap[child+1])//判断左右子节点哪个大
            child++;
        if(lastelement >= heap[child])//判断最后一个节点与当前child节点大小
            break;
        //将child上移一层
        heap[currentnode] = heap[child];
        currentnode = child;
        child *= 2;
    }
    heap[currentnode] = lastelement;
    return ret;
}

template <class T>
void maxheap<T>::push(const T& theElement){
    int currentnode = ++heapsize;//新插入的节点index为heapsize+1
    while(currentnode != 1 && heap[currentnode / 2] < theElement){//如果父节点小于新插入的节点
        heap[currentnode] = heap[currentnode / 2];//将currentnode向下移一层
        currentnode /= 2;
    }
    //currentnode = 1 或者theElement < heap[currentnode / 2]
    heap[currentnode] = theElement;
}

template <class T>
bool maxheap<T>::empty() const{
    return heapsize == 0;
}

template <class T>
int maxheap<T>::m_size()const {
    return heapsize;
}

template <class T>
const T& maxheap<T>::top(){
    return heap[1];
}

//删除最大值
template <class T>
void maxheap<T>::pop(){//O(lgn)
//heapsize - 1  需要重排堆
//获取最后一位的元素
    T lastelement = heap[heapsize--];
    //从根开始重排 
    int root = 1;
    int child = 2 * root;
    while(child <= heapsize){
        if(child < heapsize && heap[child] < heap[child+1])//右节点大
            child++;
        if(lastelement >= heap[child])
            break;
        heap[root] = heap[child];
        root = child;
        child *= 2;
    }
    heap[root] = lastelement;
}
//此为编号从1-size的版本
template <class T>
void maxheap<T>::initialize(T *theHeap, int theSize){
    delete [] heap;
    heap = theHeap;
    heapsize = theSize;

    for(int root = heapsize / 2; root >= 1; root--){
        T rootElement = heap[root];
        int child = 2 * root;//leftchild
        while(child <= heapsize){
            if(child < heapsize && heap[child] < heap[child+1])//child is not the last element, and right child > left child
                child++;    
            if(rootElement >= heap[child])
                break;
            heap[child/2] = heap[child];//子节点大于rootElement, 因此，将子节点上移一层
            child *= 2;
        }
        heap[child/2] = rootElement;
    }
}

//此为编号从0-size-1的版本
template <class T>
void maxheap<T>::initialize2(T *theheap, int thesize){
    delete [] heap;
    heap = theheap;
    heapsize = thesize;
    int root = heapsize / 2 - 1;
    for(; root >= 0; root--){
        T rootElement = heap[root];
        int leftchild = 2*root + 1;
        int rightchild = leftchild + 1;
        while(leftchild < heapsize){
            //判断左右子节点哪个大
            if(leftchild < heapsize && heap[leftchild] < heap[leftchild+1]){//如果右节点大
                if(rootElement >= heap[rightchild])//比较根与右节点
                    break;//root is larger, break
                else{//否则右节点上移一层
                    heap[rightchild/2 - 1] = heap[rightchild];
                    leftchild = rightchild * 2 + 1;
                    rightchild = leftchild + 1;
                }
            }
            else{//如果还是左节点大
                if(rootElement >= heap[leftchild])//比较跟与左节点
                    break;
                else{//否则左节点上移一层
                    heap[leftchild/2] = heap[leftchild];
                    leftchild = leftchild * 2 + 1;
                    rightchild = leftchild + 1;
                }
            }
        }
            heap[leftchild/2] = rootElement;
    }
}

//minheap
template <class T>
class minheap : public maxpriorityqueue<T>{
 public:
    minheap() : heap(nullptr), arraylength(0), heapsize(0){}
    // maxheap(T *t, size_t capacity, size_t size) : heap(t), arraylength(capacity), heapsize(size){}
    minheap(const minheap &mh) : heap(mh.heap), arraylength(mh.arraylength), heapsize(mh.heapsize){}
    void initialize(T *theHeap, int theSize);
    void push(const T& theElement);
    bool empty() const;
    int m_size() const;
    const T& top();
    void pop();
    ~minheap(){}
    void levelOrder(){
        for(int i = 1; i <= heapsize; i++)
            cout << std::right << setw(3) << heap[i] << " ";
    }
private:
    T       *heap;
    int  arraylength;//capacity of array heap 
    int  heapsize;//nums of elements in heap   
};
//此为编号从1-size的版本
template <class T>
void minheap<T>::initialize(T *theHeap, int theSize){
    delete [] heap;
    heap = theHeap;
    heapsize = theSize;

    for(int root = heapsize / 2; root >= 1; root--){
        T rootElement = heap[root];
        int child = 2 * root;//leftchild
        while(child <= heapsize){
            if(child < heapsize && heap[child] > heap[child+1])//child is not the last element, and right child > left child
                child++;    
            if(rootElement <= heap[child])
                break;
            heap[child/2] = heap[child];//子节点大于rootElement, 因此，将子节点上移一层
            child *= 2;
        }
        heap[child/2] = rootElement;
    }
}

template <class T>
void minheap<T>::push(const T& theElement){
    int currentnode = ++heapsize;//新插入的节点index为heapsize+1
    while(currentnode != 1 && heap[currentnode / 2] > theElement){//如果父节点小于新插入的节点
        heap[currentnode] = heap[currentnode / 2];//将currentnode向下移一层
        currentnode /= 2;
    }
    //currentnode = 1 或者theElement < heap[currentnode / 2]
    heap[currentnode] = theElement;
}

template <class T>
bool minheap<T>::empty() const{
    return heapsize == 0;
}

template <class T>
int minheap<T>::m_size()const {
    return heapsize;
}

template <class T>
const T& minheap<T>::top(){
    return heap[1];
}

template <class T>
void minheap<T>::pop(){
//heapsize - 1  需要重排堆
//获取最后一位的元素
    T lastelement = heap[heapsize--];
    //从根开始重排 
    int root = 1;
    int child = 2 * root;
    while(child <= heapsize){
        if(child < heapsize && heap[child] > heap[child+1])//右节点大
            child++;
        if(lastelement <= heap[child])
            break;
        heap[root] = heap[child];
        root = child;
        child *= 2;
    }
    heap[root] = lastelement;
}

/*--------------------1-maxpriorityqueue-------------------*/

/*--------------------quicksort-----------------------------*/

int num = 0;//记录比较了多少次
int num2 = 0;//记录partition调用多少次
int partition(int *arr, int begin, int end){
    num2++;
    int mid = end;//partition中间的元素，首先定位于最后
    int i = begin - 1;//begin----i all < arr[mid]-----------i是size_t类型，初始值i = 4294967295
    for (int j = begin; j <= end - 1; j++){//i+1------j all > arr[mid]-----------------O(n)--|n = end - begin - 1|
        num++;
        if(arr[j] >= arr[mid]){//swap arr[i++] and arr[j], set the element in arr[i+1] which < arr[mid] 
            int temp = arr[j];
            arr[j] = arr[++i];
            arr[i] = temp;
        }
    }
    int temp = arr[++i];
    arr[i] = arr[mid];
    arr[mid] = temp;
    return i;
}
void quicksort(int *arr, int begin, int end){//O(nlgn) -----O(n2)
    if(begin < end){
        int mid = partition(arr, begin, end);
        quicksort(arr, begin, mid - 1);
        quicksort(arr, mid + 1, end);
    }
}

//能够对重复元素进行处理，返回一个q和一个t
//arr[begin----q-1]都小于arr[q]
//arr[q----t]都等arr[q]
//arr[t+1----r]都大于arr[q]
struct q_t{
    int q;
    int t;
};
q_t partition2(int *arr, int begin, int end){//------O(end-begin)
    int mid = end;
    int i = begin - 1;
    int t = i;
    for (int j = begin; j < end; j++){
        if(arr[j] > arr[mid]){
            int tempi = arr[++i];
            int tempt = arr[++t];
            arr[t] = tempi;
            arr[i] = arr[j];
            arr[j] = tempt;
        }else if(arr[j] == arr[mid]){
            int temp = arr[++t];
            arr[t] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[++t];
    arr[t] = arr[mid];
    arr[mid] = temp;
    return {++i, t};
}

void quicksort2(int *arr, int begin, int end){
    if(begin < end){
        q_t qt = partition2(arr, begin, end);
        quicksort2(arr, begin, qt.q - 1);
        quicksort2(arr, qt.t + 1, end);
    }
}

//快速排序的随机化版本
static default_random_engine e2;
int randomized_partition(int *arr, int begin, int end){
    uniform_int_distribution<unsigned> u(begin, end);
    default_random_engine e;
    e.seed(e2());
    int mid = u(e);
    int temp = arr[end];
    arr[end] = arr[mid];
    arr[mid] = temp;
    return partition(arr, begin, end);
}

void randomized_quicksort(int *arr, int begin, int end){
    if(begin < end){
        int mid = randomized_partition(arr, begin, end);
        randomized_quicksort(arr, begin, mid - 1);
        randomized_quicksort(arr, mid + 1, end);
    }
}
//hoare-partition
int hoare_partition(int *arr, int begin, int end){
    int x = arr[begin];
    int i = begin;
    int j = end+1;
    while(true){
        while(arr[--j] > x)
            ;
        while(arr[++i] < x)
            ;
        if(i < j){
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }else{//最终的时候交换key与最后一个小于key的值
            arr[begin] = arr[j];
            arr[j] = x;
            return j;
        }
    }
}
void hoare_quicksort(int *arr, int begin, int end){
    if(begin < end){
        int mid = hoare_partition(arr, begin, end);
        hoare_quicksort(arr, begin, mid - 1);
        hoare_quicksort(arr, mid + 1, end);
    }
}

//尾递归
void tail_recursive_quicksort(int *arr, int begin, int end){//最坏情况下栈深度是O(n)
    while(begin < end){
        int mid = partition(arr, begin, end);
        tail_recursive_quicksort(arr, begin, mid - 1);
        begin = mid + 1;
    }
}

//尾递归减少最坏情况下栈深度
//上一个版本的尾递归，存在的问题：可能存在每次递归都与前一次的范围很接近，只是减去了mid
//因此在此版本中，每次递归选择较小的一个范围进行递归，此时partition中的代码调用次数会较少
void tail_recursive_quicksort2(int *arr, int begin, int end){
    while(begin < end){
        int mid = partition(arr, begin, end);
        if(mid - begin < end - mid){//选择较小的一边进行递归
            tail_recursive_quicksort2(arr, begin, mid - 1);
            begin = mid + 1;
        }else{
            tail_recursive_quicksort2(arr, mid + 1, end);
            end = mid - 1;
        }
    }
}

/*--------------------quicksort-----------------------------*/
/*--------------------矩阵计算-----------------------------*/
void visitmatrix(vector<vector<int>> &m){
    int row = m.size();
    int column = m[0].size();
    for (int i = 0; i < row; i++){
        for (int j = 0; j < column; j++){
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

//multiply
void square_matrix_multiply(vector<vector<int>> & ma, 
    vector<vector<int>> &mb, 
    int m, int n, int q, 
    vector<vector<int>> &ret){
        for (int i = 0; i < m; i++){
            for (int j = 0; j < q; j++){
                for (int k = 0; k < n; k++){
                    ret[i][k] += ma[i][j] * mb[j][k];
                }
            }
        }
    }
    //maxtrix multiply 分治算法
    /*--------------------矩阵计算-----------------------------*/

/*----------------------counting-sort--------------------*/
//此算法是稳定的
void counting_sort(int *arr, int *B, int length, int k){
    int C[k + 1];
    for (int i = 0; i < k + 1; i++)
        C[i] = 0;
    for (int i = 0; i < length; i++)
        C[arr[i]]++;
    for (int i = 1; i < k + 1; i++)
        C[i] = C[i] + C[i - 1];
    /*对于每一个arr[i]中的元素来说
      C[arr[i]]中存储了 <= arr[i]的元素的个数
    */
    for (int i = length; i >= 0; i--){//从后往前
        B[C[arr[i]]] = arr[i];//arr[i]的位置应该是C[arr[i]]
        C[arr[i]]--;//减一，下一个与arr[i]相同的元素会放在前一个位置
                        //因为是从后往前，因此它是稳定的原本元素的顺序不变
    }
}
/*----------------------counting-sort--------------------*/
/*----------------------radix-sort--------------------*/

void get_sort_data(int *arr, int *sort_data, int length, int radix){
    if(radix == 1)
        for (int i = 0; i < length; i++)//-----------O(length)
            sort_data[i] = (arr[i] % 100) % 10;
    else if(radix == 2)
        for (int i = 0; i < length; i++)
            sort_data[i] = (arr[i] % 100) / 10;
    else if(radix == 3)
        for (int i = 0; i < length; i++)
            sort_data[i] = arr[i] / 100;
}

void counting_sort_radix(int *in, int *B, int length, int k, int radix){//-----O(k+length)
    int arr[length];
    for (int i = 0; i < length; i++)//------------O(length)
        arr[i] = in[i];
    get_sort_data(in, arr, length, radix);//--------O(length)
    int C[k + 1];
    for (int i = 0; i < k + 1; i++)//-------------O(k)
        C[i] = 0;
    for (int i = 0; i < length; i++)//--------O(length)
        C[arr[i]]++;
    for (int i = 1; i < k + 1; i++)//-------------O(k)
        C[i] = C[i] + C[i - 1];
    /*对于每一个arr[i]中的元素来说
      C[arr[i]]中存储了 <= arr[i]的元素的个数
    */
    for (int i = length-1; i >= 0; i--){//从后往前------------------O(length)
        B[C[arr[i]]] = in[i];//arr[i]的位置应该是C[arr[i]]
        C[arr[i]]--;//减一，下一个与arr[i]相同的元素会放在前一个位置
                        //因为是从后往前，因此它是稳定的原本元素的顺序不变
    }
}

void radix_sort(int *arr, int d, int length){//-------------O(d*(k+length))
    int temp[length];
    for (int i = 0; i < length; i++)//--------O(length)
        temp[i] = arr[i];
    int ret[length+1];
    for (int i = 0; i < d; i++){//----------O(d) * O(k+length) = O(d*(k+length))
        counting_sort_radix(temp, ret, length, 9, i+1);//---------O(k+length)
        for (int i = 1; i <= length;i++)//----O(length)
            temp[i-1] = ret[i];
    }
    for (int i = 0; i < length; i++)//-----O(length)
        arr[i] = temp[i];
}
/*----------------------radix-sort--------------------*/
/*----------------------bucket-sort--------------------*/
/*
struct bucket_sort_node{
    int value;
    bucket_sort_node *next;
};
//insert the new node and sort the list
void bucket_sort_node_insert(bucket_sort_node *header, bucket_sort_node *thenode){
    bucket_sort_node *currentnode = header;
    while(currentnode->next != nullptr){
        if(thenode->value <= currentnode->value){
            header = thenode;
            thenode->next = currentnode;
        }
    }
}
void bucket_sort(int *arr, int length){
    bucket_sort_node B[length];
    for (int i = 0; i < length; i++){
        B[i].value = 0;
        B[i].next = nullptr;
    }
    for (int i = 0; i < length; i++)
        
}
*/
/*----------------------bucket-sort--------------------*/
} //namespace algorithms


#endif  //E_ALGORITHMS_H_