#include "leetcode.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

namespace al
{
class MaxAria : public ILeetCode
{
public:

    int maxAria(vector<int>& height)
    {
        if(height.size() == 0) return 0;
        size_t res = 0;
        size_t i = 0, j = height.size() - 1;
        while(i < j)
        {
            auto min1 = std::min(height[i], height[j]);
            res = std::max(min1 * (j - i), res);
            if(min1 == height[i]) i++;
            else j--;
        }
        return res;
    }

    void test() override 
    {
        vector<int> v = {1, 8, 6, 2, 5, 4, 8, 3, 7};
        cout << maxAria(v) << endl;
        assert(maxAria(v) == 49);
    }
};
}


