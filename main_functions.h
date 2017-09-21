#include "e_algorithms.h"

void main_insertsort()
{
    using algorithms::insert_sort;
    int nums[10] = {2, 3, 1, 62, 12, 7, 95, 21, 6, 33};
    // int nums[4] = {2,3,1,0};
    int *p = insert_sort(nums, 10);
    for (int i = 0; i < 10; i++)
    {
        cout << *(p++) << " ";
    }
    cout << endl;
}