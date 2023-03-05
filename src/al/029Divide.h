#pragma once

#include "leetcode.h"
#include <cstdlib>
#include <cmath>
#include <boost/lexical_cast.hpp>

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

      int divide2(int dividend, int divisor) {
        bool sign = true;
        if (dividend >= 0 && divisor >= 0) sign = false;
        if (dividend < 0 && divisor <0 ) sign = false;

        dividend = dividend > 0 ? -1 * dividend  : dividend;
        divisor = divisor > 0 ? -1 * divisor : divisor;

        int ret = div(dividend, divisor);
        if (sign) return ret;
        return INT32_MIN == ret ? INT32_MAX : -1 * ret;
      }

      int div(int dividend, int divisor) {
        if (dividend > divisor) return 0;
        int a = divisor;
        int time = -1;
        while (dividend - divisor < ( divisor)) {
          divisor += divisor;
          time *= 2;
        }
        return time + div(dividend - divisor, a);
      }

      int divide3(int dividend, int divisor) {
        bool sign = true;
        if (dividend >= 0 && divisor >= 0) sign = false;
        if (dividend < 0 && divisor <0 ) sign = false;

        dividend = dividend > 0 ? -1 * dividend  : dividend;
        divisor = divisor > 0 ? -1 * divisor : divisor;

        int total_times = 0;
        int times = -1;
        int a = divisor;
        while (dividend <= divisor) {
          if (dividend - divisor < divisor)  {
            divisor += divisor;
            times *=2;
          } else {
            total_times += times;
            times = -1;
            dividend -= divisor;
            divisor = a;
          }
        }
        times = total_times;
        if (sign) return times;
        return INT32_MIN == times ? INT32_MAX : -1 * times;
      }


      void test() override
      {
        cout << divide3(10, 3) << endl;
        cout << divide(7, -3) << endl;
      }

      void test_with_param(vector<string> params) override{
        if (!param_check(2, params)) return;
        int p1 = boost::lexical_cast<int>(params[0].c_str(), params[0].size());
        int p2 = boost::lexical_cast<int>(params[1].c_str(), params[1].size());

        cout << divide(p1, p2) << endl;
        cout << divide2(p1, p2) << endl;
        cout << divide3(p1, p2) << endl;
      }

};


}
