#include <iostream>
using namespace std;
#include <unordered_map>
#include <unordered_set>
namespace algorithms
{

/*--------------------1-insertsort-------------------*/
int *insert_sort(int *nums, int n)
{
    for (int j = 1; j < n; j++)
    {
        int key = nums[j];
        int i = j - 1;
        while (i >= 0 && nums[i] > key)
        {
            nums[i + 1] = nums[i]; //向右移动元素
            i--;
        }
        nums[i+1] = key;
    }
    return nums;
}
/*--------------------1-insertsort-------------------*/

/*--------------------1-maxpriorityqueue-------------------*/
//数据结构p299练习1
//使用数组线性表实现最大优先级队列
template <class T>
class maxpriorityqueue{
public:
    virtual ~maxpriorityqueue(){}
    virtual bool empty() const = 0;
    virtual int m_size() const = 0;
    virtual const T& top() = 0;
    virtual void pop() = 0;
    virtual void push(const T& element) = 0; 
};
/*--------------------1-maxpriorityqueue-------------------*/

}//namespace algorithms