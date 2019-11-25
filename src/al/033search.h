#pragma once
#include "leetcode.h"
#include <algorithm>
#include <cassert>

namespace al
{
class ArraySearch : public ILeetCode
{

public:

    int search(vector<int>& nums, int target)
    {
        size_t size = nums.size();
        if (size == 0) return -1;
        if (size == 1)
        {
            return target == nums[0] ? 0 : -1;
        }
        if (size == 2)
        {
            if(nums[0] == target) return 0;
            if (nums[1] == target) return 1;
        }
        //前半部分有序, 并且target就在该范围内
        if (nums[0] <= nums[size / 2 - 1] && target >= nums[0] && target <= nums[size / 2 - 1])
        {
            auto it = std::lower_bound(nums.begin(), nums.begin() + size / 2, target);
            if(*it != target)
            {
                return -1;
            }
            return it - nums.begin();
        }
        //前半部分有序,但是target不在该范围内
        else if (nums[0] <= nums[size / 2 - 1])
        {
            vector<int> v(nums.begin() + size / 2, nums.end());
            auto tmp = search(v, target);
            return  tmp >= 0 ? tmp + size / 2 : tmp;
        }
        //后半部分有序, 且target在该范围内
        else if (nums[size / 2] <= nums.back() && target >= nums[size / 2] && target <= nums.back())
        {
            auto it = std::lower_bound(nums.begin() + size / 2, nums.end(), target);
            if (target != *it)
            {
                return -1;
            }
            else
            {
                return it - nums.begin();
            }
        }
        else
        {
            vector<int> v(nums.begin(), nums.begin() + size / 2);
            return search(v, target);
        }
    }

    void test() override
    {
        vector<int> v{4,5,6,7,0,1,2};
        printVector<int>(v);
        cout << "finding 3: " << search(v, 3) << endl;
        assert(search(v, 3) == -1);
        cout << "finding 1: " << search(v, 1) << endl;
        assert(search(v, 1) == 5);
        cout << "finding 4: " << search(v, 4) << endl;
        assert(search(v, 4) == 0);
        cout << "finding 7: " << search(v, 7) << endl;
        assert(search(v, 7) == 3);
        cout << "finding 0: " << search(v, 0) << endl;
        assert(search(v, 0) == 4);
        v = {3,1};
        printVector<int>(v);
        cout << "finding 0: " << search(v, 0) << endl;
        assert(search(v, 0) == -1);
        v = {1,3,5};
        printVector<int>(v);
        cout << "finding 4: " << search(v, 4) << endl;
        assert(search(v, 4) == -1);
        v = { 3,5,1 };
        printVector<int>(v);
        cout << "finding 1: " << search(v, 1) << endl;
        assert(search(v, 1) == 2);
//        [0,1,3,4,6,8,9]
//        5
        v = {0,1,3,4,6,8,9};
        printVector<int>(v);
        cout << "find 5: " << search(v, 5) << endl;
        assert(search(v, 5) == -1);
    }

};



}
