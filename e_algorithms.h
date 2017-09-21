#include <iostream>
using namespace std;

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


}//namespace algorithms