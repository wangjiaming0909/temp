#pragma once

#include "leetcode.h"
#include <algorithm>

namespace al {
class SearchInsert : public ILeetCode
{
public:

    int searchInsert(vector<int>& nums, int target)
    {
        auto loit = lower_bound(nums.begin(), nums.end(), target);
        auto upit = upper_bound(nums.begin(), nums.end(), target);
        if(loit == upit)
        {
            auto pos = loit - nums.begin();
            nums.insert(loit, target);
            return pos;
        }
        return loit - nums.begin();
    }

    void test() override
    {
        vector<int> v{1,3,5,6};
        cout << searchInsert(v, 5) << endl;//2;
        v = {1,3,5,6};
        cout << searchInsert(v, 2) << endl;//1
        v = {1,3,5,6};
        cout << searchInsert(v, 7) << endl;//4
        v = {1,3,5,6};
        cout << searchInsert(v, 0) << endl;//0
    }
};
}
