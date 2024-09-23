#pragma once
#include "leetcode.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

namespace al {
class ThreeSum : public ILeetCode {
public:
  vector<vector<int>> threeSum(vector<int> &nums) {
    return threeSum2(nums);
    if (nums.size() < 3)
      return vector<vector<int>>();
    vector<vector<int>> ret{};
    int i = 1, l = 0, r = nums.size() - 1;

    std::sort(nums.begin(), nums.end()); // O(nlogn)

    while (i <= static_cast<int>(nums.size() - 2)) {
      while (l < i && i < r) {
        if (nums[i] == nums[i - 1]) {
          if (i > 1 && nums[i - 2] == nums[i - 1] && nums[i - 1] == nums[i])
            break;
          l = i - 1;
        }

        auto sum = nums[l] + nums[i] + nums[r];
        if (sum < 0) {
          l++;
        } else if (sum > 0) {
          r--;
        } else {
          // 如果先判断是否应该添加就需要跟上一次进行比较,
          // 上一次是否存在都不知道 先push_back,之后再收缩范围,
          ret.push_back(vector<int>{nums[l], nums[i], nums[r]});
          do {
            l++;
          } while (l < i && nums[l - 1] == nums[l]);
          do {
            r--;
          } while (l < r && nums[r + 1] == nums[r]);
        }
      }
      i++;
      l = 0;
      r = nums.size() - 1;
    }

    return ret;
  }

  // assume from [begin, end) are sorted
  std::vector<std::pair<int, int>> twoSum(vector<int>::const_iterator begin,
                                          vector<int>::const_iterator end,
                                          int target) {
    std::vector<std::pair<int, int>> ret;
    if (begin == end - 1)
      return {};
    end--;
    int sum = *begin + *end;
    while (begin < end) {
      if (sum > target) {
        end = end - 1;
      } else if (sum < target) {
        begin = begin + 1;
      } else {
        ret.emplace_back(*begin, *end);
        while (begin + 1 < end && *begin == *(begin + 1))
          begin++;
        begin++;
      }
      if (begin < end)
        sum = *begin + *end;
    }
    return ret;
  }

  vector<vector<int>> threeSum2(vector<int> &nums) {
    std::sort(nums.begin(), nums.end());
    std::vector<std::vector<int>> res;

    for (int i = 0; i < nums.size(); ++i) {
      if (i > 0 && nums[i] == nums[i - 1])
        continue;
      int cur = nums[i];
      auto twoSumRes = twoSum(nums.begin() + i + 1, nums.end(), 0 - cur);
      for (int j = 0; j < twoSumRes.size(); ++j) {
        vector<int> threeInt = {cur, twoSumRes[j].first, twoSumRes[j].second};
        res.push_back(threeInt);
      }
    }
    return res;
  }
  void test() override {
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

    v = {-2, -1, -1, 0, 0, 0, 1, 2, 2, 3};
    auto r = twoSum(v.begin(), v.end(), 0);
    cout << "two sum == 0:" << endl;
    for (int i = 0; i < r.size(); ++i) {
      cout << r[i].first << ", " << r[i].second << endl;
    }

    v = {0, 0, 0, 0};
    ret = threeSum2(v);
    print(ret);
    cout << endl;
  }

  void print(vector<vector<int>> &v) {
    for (auto &vv : v) {
      for (auto i : vv) {
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

} // namespace al
