#pragma once

#include "leetcode.h"
#include <cstdlib>
#include <cmath>

namespace al {

class Divide : public ILeetCode
{
public:
    int divide(int dividend, int divisor)
    {
        bool sign = (dividend * divisor < 0);
        dividend = std::abs(dividend);
        divisor = std::abs(divisor);
        int time = 0;
        while(dividend  > divisor)
        {
            dividend -= divisor;
            time++;
        }
        return sign ? -1 * time : time;
    }

    void test() override
    {
        cout << divide(10, 3) << endl;
        cout << divide(7, -3) << endl;
    }

};


}
