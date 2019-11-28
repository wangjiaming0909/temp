#pragma once

#include "leetcode.h"

namespace al
{
class CanJump : public ILeetCode
{
public:

    bool canJump(vector<int>& nums)
    {
        vector<char> canJump;
        canJump.resize(nums.size());
        for(int i = 0; i < canJump.size()-1; i++)
        {
            canJump[i] = 0;
        }
        canJump[canJump.size() - 1] = 1;
        for(int i = nums.size() - 2; i >= 0; i--)
        {
            for(int j = 1; j <= nums[i]; j++)
            {
                if(i + j >= canJump.size()) continue;
                if(canJump[i + j] == 1)
                {
                    canJump[i] = 1;
                    break;
                }
            }
        }
        return canJump[0] == 1;
    }

    //贪心
    //其实不需要记住所有可以跳到最右侧的节点
    //只需要记住最左侧的(遍历过程中)可以跳转到最后的节点, 记为A
    //证明如果你挑不到A,那你一定跳不到结尾
    //反证法: 假设你跳不到A,但是却可以跳到结尾
    // 那么你一定时跳到了A之后的某个节点, 但是如果你可以跳到A之后的节点,那么你一定也可以跳到A节点
    //这与你跳不到A矛盾, 因此如果你可以跳到结尾,那你肯定可以跳到A
    bool canJump2(vector<int>& nums)
    {
        int canJump = nums.size() - 1;
        for(int i = nums.size() - 2; i >= 0; i--)
        {
            if(i + nums[i] >= canJump)//i 就可以跳到最左侧的Canjump节点
            {
                canJump = i;
            }
        }
        return canJump == 0;
    }

    void test() override
    {
        vector<int> v = {2,3,1,1,4};
        cout << canJump(v) << endl;
        cout << canJump2(v) << endl;
        v = {3,2,1,0,4};
        cout << canJump(v) << endl;
        cout << canJump2(v) << endl;
        v = {2,1};
        cout << canJump(v) << endl;
        cout << canJump2(v) << endl;
    }
};
}
