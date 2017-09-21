#include "e_algorithms.h"
#include "coursera_algorithms.h"
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

void main_quickfind(){
    using coursera::quickfind;
    quickfind qf(10);
    qf.union_(1,2);
    qf.union_(3,4);
    qf.union_(1,6);
    cout << qf.connected(2,6) << " ";
}