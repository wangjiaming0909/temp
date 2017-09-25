#include <iostream>
using namespace std;
#include <unordered_map>
#include <unordered_set>
namespace algorithms
{

/*--------------------1-insertsort-------------------*/
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