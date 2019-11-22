#pragma once
#include "leetcode.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

namespace al
{
class ThreeSum : public ILeetCode
{
public:
    vector<vector<int>> threeSum(vector<int>& nums)
    {
        if(nums.size() < 3) return vector<vector<int>>();
        vector<vector<int>> ret{};
        int i = 1, l = 0, r = nums.size() - 1;

        std::sort(nums.begin(), nums.end());//O(nlogn)

        while(i <= static_cast<int>(nums.size() - 2))
        {
            while(l < i && i < r)
            {
                if(nums[i] == nums[i-1]) 
                {
                    if(i > 1 && nums[i-2] == nums[i-1] && nums[i-1] == nums[i]) break;
                    l = i-1;
                }

                auto sum = nums[l] + nums[i] + nums[r];
                if(sum < 0)
                {
                    l++;
                }
                else if(sum > 0)
                {
                    r--;
                }
                else 
                {
                    //如果先判断是否应该添加就需要跟上一次进行比较, 上一次是否存在都不知道
                    //先push_back,之后再收缩范围, 
                    ret.push_back(vector<int>{nums[l], nums[i], nums[r]});
                    do
                    {
                        l++;
                    }while(l < i && nums[l-1] == nums[l]);
                    do
                    {
                        r--;
                    }while(l < r && nums[r+1] == nums[r]);
                }
            }
            i++;
            l = 0;
            r = nums.size()-1;
        }

        return ret;
    }

    void test() override 
    {
        vector<int> v{-1, 0, 1, 2, -1, -4};
        auto ret = threeSum(v);
        print(ret);
        cout << endl;

        v = {0, 0, 0, 0, 0};
        ret = threeSum(v);
        print(ret);
        cout << endl;

        v = {0, 0, 0};
        ret = threeSum(v);
        print(ret);
        cout << endl;

        v = {-2, -1, 0, 1, 2};
        ret = threeSum(v);
        print(ret);
        cout << endl;

        v = {-2, -1, 0, 1, 2, 2, 3, 1, 2, -1, -4, -3};
        ret = threeSum(v);
        print(ret);
        cout << endl;

        v = {-2, -2, -2, 0, 4, 4};
        ret = threeSum(v);
        print(ret);
        cout << endl;

        v = {-5, -5, 1, 1, 4, 4};
        ret = threeSum(v);
        print(ret);
        cout << endl;

    }

    void print(vector<vector<int>>& v)
    {
        for(auto& vv : v)
        {
            for(auto i : vv)
            {
                cout << i << " ";
            }
            cout << endl;
        }
    }
};
/*
-1 -1 2
-1 0 1

0 0 0

0 0 0

-2 0 2
-1 0 1

-2 -1 3
-1 -1 2
-3 0 3
-2 0 2
-1 0 1
-4 1 3
-3 1 2
-2 1 1
-4 2 2

-2 -2 4

-5 1 4

*/

}
