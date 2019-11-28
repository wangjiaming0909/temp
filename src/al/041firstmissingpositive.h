#pragma once
#include "leetcode.h"

namespace al {
class FirstMissingPositive : public ILeetCode
{
public:

    int firstMissingPositive(vector<int>& nums)
    {
        int size = nums.size();
        for(int i = 0; i < size; i++)
        {
            int value = nums[i];
            if(value <= 0 || value > size) continue;
            if(value == i + 1) continue;
            nums[i] = 0;
            while(value > 0 && value <= size && nums[value-1] != value)
            {
                auto tmp = value;
                value = nums[value-1];
                nums[tmp-1] = tmp;
            }
        }
        int i = 0;
        for(; i < size; i++)
        {
            if(nums[i] != i + 1) return i+1;
        }
        return i + 1;
    }

    void test() override
    {
        vector<int> v{3,4,-1,1};
        cout << firstMissingPositive(v) << endl;

        v = {7,8,9,10,11,12};
        cout << firstMissingPositive(v) << endl;
        v = {1,2,0};
        cout << firstMissingPositive(v) << endl;
        v = {2,1};
        cout << firstMissingPositive(v) << endl;
    }
};
}
