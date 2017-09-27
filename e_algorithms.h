#include <iostream>
using namespace std;
#include <unordered_map>
#include <unordered_set>
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
/*--------------------1-maxpriorityqueue-------------------*/

} //namespace algorithms