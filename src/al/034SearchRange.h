#pragma once

#include "leetcode.h"
#include <algorithm>


namespace al {
class SearchRange : public ILeetCode
{

public:

    vector<int> searchRange(vector<int>& nums, int target)
    {
        auto loit = std::lower_bound(nums.begin(), nums.end(), target);
        if(loit == nums.end() || *loit != target) return vector<int>{-1,-1};
        vector<int> ret{};
        ret.resize(2);
        ret[0] = loit - nums.begin();
        auto upit = std::upper_bound(nums.begin(), nums.end(), target);
        if(upit == nums.end() && nums.back() == target) ret[1] = nums.size() - 1;
        else ret[1] = upit - nums.begin() - 1;
        return ret;
    }

    void test() override
    {
        vector<int> v{5,7,7,8,8,10};
        printVector(searchRange(v, 8));//3,4
        printVector(searchRange(v, 6));//-1,-1
    }

};
}
