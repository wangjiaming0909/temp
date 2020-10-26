#pragma once
#include "leetcode.h"
#include <vector>
#include <cassert>
#include <unordered_map>

namespace al
{
class TwoSum : public ILeetCode
{
public:
  vector<int> two_sum(vector<int>& nums, int target)
  {
    std::unordered_map<int, int> m{};
    for (int i = 0; i < nums.size(); ++i) {
      auto it = m.find(target-nums[i]);
      if (it != m.end()) {
        return {it->second, i};
      }
      m[nums[i]] = i;
    }
    return vector<int>();
  }

  void test() override
  {
  }
};
}
