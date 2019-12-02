#include "leetcode.h"
#include <algorithm>
#include <cstdint>

namespace al {

class LengthOfLIS : public ILeetCode
{

public:
    int findMaxBefore(vector<int>& nums, vector<int>& v, int i)
    {
        int max = INT32_MIN;
        for(int j = 0; j < i; j++)
        {
            if(nums[j] >= nums[i]) continue;
            max = std::max(max, v[j]);
        }
        if(max == INT32_MIN) return 0;
        return max;
    }

    int lengthOfLIS(vector<int>& nums)
    {
        vector<int> v;
        v.resize(nums.size());

        for(int i = 0; i < nums.size(); i++)
        {
            auto val = findMaxBefore(nums, v, i);
            v[i] = val+1;
        }

        return *std::max_element(v.begin(), v.end());
    }

    void test() override
    {
//        [10,9,2,5,3,7,101,18]
        vector<int> v = {10, 9, 2, 5, 3, 7, 101, 18};
        cout << lengthOfLIS(v) << endl;
    }
};
}
