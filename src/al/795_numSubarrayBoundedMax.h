#pragma once
#include "leetcode.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>
#include <iostream>

namespace al
{
class NumSubarrayBoundedMax : public ILeetCode
{
public:
    int numSubarrayBoundedMax2(std::vector<int>& A, int L, int R)
    {
        int small = 0;
        int ok = 0;
        int ret = 0;
        for(size_t i = 0; i < A.size(); i++)
        {
            if(A[i] > R) 
            {
                small = 0;
                ok = 0;
            }
            if(A[i] < L) 
            {
                small++;
                ret += ok * small;
            }
            if(A[i] >= L && A[i] <= R) 
            {
                ok++;
                ret += ok + small;
            }
        }
        return ret;
    }
    int numSubarrayBoundedMax(std::vector<int>& A, int L, int R)
    {
        int ret = 0;
        int smallN = 0;

        for(size_t i = 0; i < A.size(); i++)
        {
            if(A[i] > R) 
            {
                smallN = 0;
                continue;
            }
            if(A[i] < L) 
            {
                smallN++;
                bool v = false;
                for(size_t j = i + 1; j < A.size(); j++)
                {
                    if(A[j] > R) break;
                    if(A[j] >= L || v) 
                    {
                        v = true;
                        ret++;
                    }
                }
                continue;
            }
            ret++;
            size_t j = i + 1;
            for(; j < A.size(); j++)
            {
                if(A[j] > R) break;
                ret++;
            }
        }

        return ret;
    }
    void test() override
    {
        std::vector<int> v = {2, 1, 4, 3};
        int L = 2;
        int R = 3;
        auto ret = numSubarrayBoundedMax2(v, L, R);

        std::cout << ret << std::endl;
        assert(ret == 3);

        v = {2, 1, 3, 4, 3};
        ret = numSubarrayBoundedMax(v, L, R);
        std::cout << ret << std::endl;
        assert(ret == 6);

        v = {73, 55, 36, 5, 55, 14, 9, 7, 72, 52};
        L = 32;
        R = 69;
        ret = numSubarrayBoundedMax2(v, L, R);
        std::cout << ret << std::endl;
        assert(ret == 22);
    } 
};
}