#ifndef _AL_007_REVERSE_INTEGER_H_
#define _AL_007_REVERSE_INTEGER_H_
#include "leetcode.h"
#include <cassert>
#include <vector>
#include <cmath>
#include "../timer.h"


namespace al{
class Reverse_interger : public ILeetCode{
public:
    int reverse(int x){
        al::timer _{__func__};
        std::vector<int> v_;
        if(x == 0) return x;
        int sign = x / std::abs(x);
        x = std::abs(x);
        long ret = 0;
        int remainer = 0;
        while(x/10 != 0 || x != 0){
            remainer = x - (x/10) * 10;
            if(!(remainer == 0 && v_.empty()))
                v_.push_back(remainer);
            x /= 10;
        }
        for(int i = 0; i < v_.size(); i++){
            int power = v_.size() - i - 1;
            ret += std::pow(10, power) * v_[i];
        }
        if(ret > INT32_MAX) return 0;
        if(ret < INT32_MIN) return 0;
        return ret * sign;
    }
    int reverse2(int x) {
        al::timer _{__func__};
        int64_t y = x;
        int64_t ret = 0;
        while(y)
        {
            int64_t b = y % 10; 
            y /= 10;
            ret = ret * 10 + b;
        }
        return ret > INT32_MAX || ret < INT32_MIN  ? 0 :ret;
    }
    virtual void test() override{
        int input = 123;
        int ret = 321;
        assert(reverse(input) == ret);
        assert(reverse2(input) == ret);
        input = 1;
        ret = 1;
        assert(reverse(input) == ret);
        assert(reverse2(input) == ret);
        input = 120;
        ret = 21;
        assert(reverse(input) == ret);
        assert(reverse2(input) == ret);
        input = 0;
        ret = 0;
        assert(reverse(input) == ret);
        assert(reverse2(input) == ret);
        input = -120;
        ret = -21;
        assert(reverse(input) == ret);
        assert(reverse2(input) == ret);
        input = 1534236469;
        ret = 0;
        assert(reverse(input) == ret);
        assert(reverse2(input) == ret);
    }
};

}//namespace al

#endif // _AL_007_REVERSE_INTEGER_H_