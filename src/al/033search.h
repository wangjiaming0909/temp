#pragma once
#include "leetcode.h"
#include <algorithm>

namespace al
{
class ArraySearch : public ILeetCode
{

public:

    int search(vector<int>& nums, int target)
    {
        size_t size = nums.size();
        if(size == 0) return -1;
        if(size == 1)
        {
            return target == nums[0] ? 0 : -1;
        }
        if(nums[0] < nums[size/2-1] && target >= nums[0] && target <= nums[size/2-1])
        {
            auto it = std::lower_bound(nums.begin(), nums.begin() + size/2, target);
            return (it == nums.begin() + size/2) ? -1 : (it - nums.begin());
        }
        else if(nums[0] < nums[size/2-1])
        {
            vector<int> v (nums.begin() + size/2, nums.end());
            auto tmp = search(v, target);
            return  tmp >= 0 ? tmp + size/2: tmp;
        }
        else if(target >= nums[size/2] && target <= nums.back())
        {
            auto it = std::lower_bound(nums.begin() + size/2, nums.end(), target);
            return (it == nums.end() ? -1 : (it - nums.begin() + size/2));
        }
        else
        {
            vector<int> v (nums.begin(), nums.begin() + size/2);
            return search(v, target);
        }
    }

    void test() override
    {
        vector<int> v{4,5,6,7,0,1,2};
        printVector<int>(v);
        cout << "finding 3: " << search(v, 3) << endl;
        cout << "finding 1: " << search(v, 1) << endl;
        cout << "finding 4: " << search(v, 4) << endl;
        cout << "finding 7: " << search(v, 7) << endl;
        v = {3,1};
        printVector<int>(v);
        cout << "finding 0: " << search(v, 0) << endl;
    }

};



}
