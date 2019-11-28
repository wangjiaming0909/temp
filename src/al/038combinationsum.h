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

        //找以curIndex开头的所有可能组合, 每一次递归中的循环都还是从当前curIndex开始
        //因此找的是树结构中的第curIndex棵树
        //当curIndex增加时,就是遍历的下一课树
        for(size_t i = curIndex; i < candidates.size(); i++)
        {
            if(remain < candidates[i]) return;
            tmp.push_back(candidates[i]);
            re(candidates, i, remain - candidates[i]);//这个i表示下一次递归中的for循环还是从当前的i开始
            tmp.pop_back();
        }
    }
    /*
     * 第一棵树                      第二棵树   	    第三棵树        第四颗树
     *    2                           3              6   	   	   7
     * 2 3 6 7   				2 3 6 7        2 3 6 7  	2 3 6 7
     * 2367 2367 2367 2367
     * 236723672367236723.....
     */

    void re2(vector<int>& candidates, int curIndex, int remain)
    {
        if(remain < 0) return;
        if(remain == 0)
        {
            ret.push_back(tmp);
        }

        for(int i = curIndex; i < candidates.size(); i++)
        {
            if(i-1 >= curIndex && candidates[i-1] == candidates[i])
            {
                continue;
            }
            if(remain < candidates[i]) return;
            tmp.push_back(candidates[i]);
            re2(candidates, i+1, remain - candidates[i]);
            tmp.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
    {
        std::sort(candidates.begin(), candidates.end());
        re2(candidates, 0, target);
        return ret;
    }

    void test()override
    {
        vector<int> v{2,3,6,7};
        int target = 7;
//        auto ret = combinationSum(v, target);
//        for(auto vv : ret)
//        {
//            printVector(vv);
//            cout << endl;
//        }

//        auto ret = combinationSum(v, target);
//        for(auto vv : ret)
//        {
//            printVector(vv);
//            cout << endl;
//        }
        v = {10,1,2,7,6,1,5};
        target = 8;
        ret = combinationSum2(v, target);
        for(auto vv : ret)
        {
            printVector(vv);
            cout << endl;
        }

//        v = {2,5,2,1,2};
//        target = 5;
//        ret = combinationSum2(v, target);
//        for(auto vv : ret)
//        {
//            printVector(vv);
//            cout << endl;
//        }

    }
private:
    vector<int> tmp;
    vector<vector<int>> ret;
};
}
