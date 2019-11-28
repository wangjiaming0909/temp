#pragma once

#include "leetcode.h"
#include <algorithm>
#include <stack>

namespace al {
class CombinationSum : public ILeetCode
{
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target)
    {
        std::sort(candidates.begin(), candidates.end());
        re(candidates, 0, target);
        return ret;
    }

    void re(vector<int>& candidates, size_t curIndex, int remain)
    {
        if(remain < 0) return;
        if(remain == 0)
        {
            ret.push_back(tmp);
        }

        for(size_t i = curIndex; i < candidates.size(); i++)//循环中不需要向后找, 只有在递归中才会回头
        {
            if(remain < candidates[i]) return;
            tmp.push_back(candidates[i]);
            re(candidates, i, remain - candidates[i]);
            tmp.pop_back();
        }
    }

    void test()override
    {
        vector<int> v{2,3,6,7};
        int target = 7;
        auto ret = combinationSum(v, target);
        for(auto vv : ret)
        {
            printVector(vv);
            cout << endl;
        }
    }
private:
    vector<int> tmp;
    vector<vector<int>> ret;
};
}
