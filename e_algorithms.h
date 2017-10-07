#include <iostream>
#include <unordered_map>
#include <iomanip>
#include <utility>
#include <unordered_set>
#include <vector>
using namespace std;
namespace algorithms
{

/*--------------------1-insertsort-------------------O(n2)-------------*/
//升序排序
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
        size_t i = n-2;
        while(nums[i] > last){
            nums[i+1] = nums[i];
            i--;
        }
        nums[i+1] = last;
    }
    return nums;
}
/*--------------------1-insertsort-------------------*/
/*--------------------2-selectsort-------------------*/
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

/*--------------------3-mergesort--------------------O(n)-*/
//将数组A[p..q] 和A[q+1...r]合并
//其中这两个数组是已经排完序的
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
/*----------------------------------------------*/
}

int *merge_sort(int *nums, size_t p, size_t r){//-------------------加上merge   O(nlgn)
    if(p < r){
        size_t q = (p+r) / 2;
        merge_sort(nums, p, q);
        merge_sort(nums, q+1, r);
        merge(nums, p ,q, r);
    }
    return nums;
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
    // maxheap(T *t, size_t capacity, size_t size) : heap(t), arraylength(capacity), heapsize(size){}
    void initialize(T *theHeap, int theSize);
    void push(const T& theElement);
    bool empty() const;
    int m_size() const;
    const T& top();
    void pop();
    ~maxheap(){}
private:
    T       *heap;
    size_t  arraylength;//capacity of array heap 
    size_t  heapsize;//nums of elements in heap
};

template <class T>
void maxheap<T>::initialize(T *theHeap, int theSize){
    delete [] heap;
    heap = theHeap;
    heapsize = theSize;

    for(int root = heapsize / 2; root >= 1; root--){
        T rootElement = heap[root];
        int child = 2 * root;
        while(child <= heapsize){
            if(child < heapsize && heap[child] < heap[child+1])
            child++;
        }

        if(rootElement >= heap[child])
            break;
        heap[child/2] = heap[child];
        child *= 2;
    }
    heap[child/2] = rootElement;
}
/*--------------------1-maxpriorityqueue-------------------*/

} //namespace algorithms