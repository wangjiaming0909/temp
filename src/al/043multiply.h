#include "leetcode.h"
#include <vector>
#include <cassert>
#include <queue>
#include <unordered_map>

struct Multiply : public al::ILeetCode {
  //       1 2 3   <------num1
  //       4 5 6   <------num2
  //   -----------
  //     0 7 3 8   <------ret[0]
  //     5 1 5 0   <------ret[1]
  string multiply(string num1, string num2) {
    int i = num2.size() - 1;
    int j = num1.size() - 1;

    vector<string> ret;
    ret.resize(num2.size());
    for (auto &v : ret) {
      v.resize(num1.size() + num2.size(), 48);
    }

    for (; i >= 0; --i) {
      unsigned char plus = 0;
      for (; j >= 0; --j) {
        char down = num2[i] - 48;
        char up = num1[j] - 48;
        unsigned int val = down * up + plus;
        ret[num2.size() - i - 1][i + j + 1] = val % 10 + 48;
        plus = val / 10;
      }
      ret[num2.size() - i - 1][i] = plus + 48;
      j = num1.size() - 1;
    }

    string r(1, 48);
    i = num1.size() + num2.size();
    for (auto &s : ret) {
      r = two_sum(s, r);
    }
    return r.empty() ? "0" : r;
  }

  // 123 + 456 = 567
  string two_sum(const string &v1, const string &v2) {
    string s;
    s.resize(v1.size() + v2.size() + 1, 48);
    int i = v1.size() - 1;
    int j = v2.size() - 1;

    char plus_1 = 0;
    while (i >= 0 && j >= 0) {
      auto val = v1[i] + v2[j] - 96 + plus_1;
      plus_1 = val / 10;
      s[v1.size() - 1 - i] = (val >= 10 ? val % 10 : val) + 48;
      --i;
      --j;
    }
    if (v1.size() > v2.size()) {
      for (i = v2.size(); i < v1.size(); ++i) {
        s[i] = v1[v1.size() - i - 1] + plus_1;
        plus_1 = (s[i] - 48) / 10;
        s[i] = (s[i] - 48) % 10 + 48;
      }
      if (plus_1)
        s[i] = 1;
    } else if (v1.size() < v2.size()) {
      for (i = v1.size(); i < v2.size(); ++i) {
        s[i] = v2[v2.size() - i - 1] + plus_1;
        plus_1 = (s[i] - 48) / 10;
        s[i] = (s[i] - 48) % 10 + 48;
      }
      if (plus_1)
        s[i] = 1;
    }
    std::reverse(s.begin(), s.end());
    i = 0;
    while (s[i++] == '0') {
    }
    return s.substr(i - 1);
  }

  int fastest_path044(vector<int> nums) {
    if (nums[0] == 0)
      return 0;
    int max_pos = 0;
    int steps = 0;
    int cur_max_pos = 0;
    for (int i = 0; i < nums.size() - 1; ++i) {
      max_pos = std::max(max_pos, i + nums[i]);
      if (cur_max_pos == i) {
        cur_max_pos = max_pos;
        steps++;
      }
    }
    return steps;
  }

  int can_complete_circuit134(vector<int> gas, vector<int> cost) {
    int step = 0;
    int total = 0;
    int min_gas = INT32_MAX;

    for (int i = 0; i < gas.size(); ++i) {
      int g = gas[i] - cost[i];
      total += g;
      if (min_gas > total) {
        min_gas = total;
        step = i;
      }
    }
    if (total >= 0) {
      return step + 1 >= gas.size() ? 0 : step + 1;
    }
    string s;
    auto it = s.begin();
    if (*it == 's') {
    }
    return -1;

#if 0
    auto size = gas.size();

    int max = 0;
    int cur_max = 0;

    vector<int> checks;
    for (int i = 0; i < gas.size(); ++i) {
      if (gas[i] >= cost[i]) checks.push_back(i);
    }

    int target_x = -1;
    for (int i = 0; i < checks.size(); ++i) {
      int x = target_x = checks[i];
      int g = gas[x];
      int c = cost[x];

      while (g >= c) {
        x = x + 1 >= gas.size() ? 0 : x + 1;
        if (x == target_x) break;
        g += gas[x];
        c += cost[x];
      }
      if (x != target_x) target_x = -1;
      else break;
    }
    return target_x;
#endif
  }

  string largestNumber(vector<int> nums) {
    vector<string> s;
    for (int i = 0; i < nums.size(); ++i) {
      s.push_back(std::to_string(nums[i]));
    }

    std::sort(s.begin(), s.end(), [](const string &s1, const string &s2) {
      return s1 + s2 > s2 + s1;
    });
    stringstream ss;
    for (int i = 0; i < s.size(); ++i) {
      ss << s[i];
    }
    string ret = ss.str();
    auto it = ret.begin();
    if (*it == '0')
      return "0";
    return ret;
  }

  bool increasingTriplet(vector<int> nums) {
    int min = INT32_MAX;
    int max = INT32_MAX;

    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] <= min) {
        min = nums[i];
      } else if (nums[i] <= max) {
        max = nums[i];
      } else if (nums[i] > max) {
        return true;
      }
    }
    return false;
  }

  int integer_replacement_397_bfs(int n) {
    std::queue<int> q;
    std::unordered_map<int, int> m;

    q.push(n);
    m[n] = 0;
    while (!q.empty()) {
      int v = q.front();
      int step = m[v];
      q.pop();
      std::vector<int> arr;
      if (v % 2 == 0) {
        arr.push_back(v / 2);
      } else {
        arr.push_back(v + 1);
        arr.push_back(v - 1);
      }

      for (auto val : arr) {
        if (val == 1) return step + 1;
        if (m.find(val) == m.end()) {
          q.push(val);
          m[val] = step + 1;
        }
      }
    }
  }

  int integer_replacement_397_dfs(int n) {
    if (n == 1) return 0;
    std::stack<long> s;
    std::unordered_map<long, long> m;

    s.push(n);
    m[n] = 0;

    while (!s.empty()) {
      auto v = s.top();
      s.pop();

      auto step = m[v];

      std::vector<long> arr;
      if (v % 2 == 0) {
        arr.push_back(v / 2);
      } else {
        arr.push_back(v + 1);
        arr.push_back(v - 1);
      }
      for (auto val : arr) {
        if (m.find(val) == m.end()) m[val] = step + 1;
        else m[val] = std::min(m[val], step + 1);
        if (val != 1) s.push(val);
      }

    }
    return m[1];
  }

  int integer_replacement_397_recursive(int n) {
    if (n == 1) return 0;

    if (n % 2 == 0)
      return integer_replacement_397_recursive(n / 2) + 1;
    long long_n = n;
    int n_ = (long_n + 1) / 2;
    return std::min(integer_replacement_397_recursive(n_),
                    integer_replacement_397_recursive((n - 1) / 2)) +
           2;
  }

  int max_sub_array_053(vector<int>nums) {
    nums.insert(nums.begin(), 0);
    vector<int> min_arr;
    min_arr.push_back(0);
    bool is_always_downing = true;
    int max = INT32_MIN;
    for (int i = 1; i < nums.size(); ++i) {
      max = std::max(max, nums[i]);
      nums[i] += nums[i-1];
      if (min_arr.back() < nums[i]) {
        min_arr.push_back(min_arr.back());
        is_always_downing = false;
      } else {
        min_arr.push_back(nums[i]);
      }
    }

    if (is_always_downing) return max;

    max = INT32_MIN;
    for (int i = min_arr.size() - 2; i >= 0; --i) {
      max = std::max(std::max(nums[i + 1], nums[i]) - min_arr[i], max);
    }
    return max;
  }

  int max_sub_array_053_dp(vector<int> nums) {
    int f_x = 0, ret = nums[0];
    for (auto v : nums) {
      f_x = std::max(f_x + v, v);
      ret = std::max(ret, f_x);
    }
    return ret;
  }

  int rob_198_dp(vector<int> nums) {
    if (nums.size() == 1)
      return nums[0];
    vector<int> dp;
    dp.resize(2);
    dp[0] = nums[0];
    int max = std::max(nums[0], nums[1]);
    dp[1] = max;
    for (int i = 2; i < nums.size(); ++i) {
      dp[i % 2] = std::max(max, dp[i % 2] + nums[i]);
      max = std::max(max, dp[i % 2]);
    }
    return max;
  }

  void test() override {
    assert(15 == rob_198_dp({1,2,3,1,10,11}));
    assert(4 == rob_198_dp({1,2,3,1}));
    assert(12 == rob_198_dp({2,7,9,3,1}));
    assert(4 == rob_198_dp({2,1,1,2}));

    assert(6 == max_sub_array_053_dp({-2, 1, -3, 4, -1, 2, 1, -5, 4}));
    assert(1 == max_sub_array_053_dp({1}));
    assert(23 == max_sub_array_053_dp({5, 4, -1, 7, 8}));
    assert(-1 == max_sub_array_053_dp({-2, -1}));
    assert(3 == max_sub_array_053_dp({2, -1, 1, 1}));

    assert(6 == max_sub_array_053({-2, 1, -3, 4, -1, 2, 1, -5, 4}));
    assert(1 == max_sub_array_053({1}));
    assert(23 == max_sub_array_053({5, 4, -1, 7, 8}));
    assert(-1 == max_sub_array_053({-2, -1}));
    assert(3 == max_sub_array_053({2, -1, 1, 1}));
    assert(3 == integer_replacement_397_recursive(8));
    assert(4 == integer_replacement_397_recursive(7));
    assert(5 == integer_replacement_397_recursive(15));
    assert(17 == integer_replacement_397_recursive(65535));
    assert(0 == integer_replacement_397_recursive(1));
    // assert(0 == integer_replacement_397_recursive(2147483647));

    assert(3 == integer_replacement_397_dfs(8));
    assert(4 == integer_replacement_397_dfs(7));
    assert(5 == integer_replacement_397_dfs(15));
    assert(17 == integer_replacement_397_dfs(65535));
    assert(0 == integer_replacement_397_dfs(1));
    assert(3 == integer_replacement_397_bfs(8));
    assert(4 == integer_replacement_397_bfs(7));
    assert(5 == integer_replacement_397_bfs(15));
    assert(17 == integer_replacement_397_bfs(65535));
    string v1 = "000738", v2 = "006150";
    string s;
    s.resize(10, 48);

    assert(two_sum("006150", "000738") == "6888");
    assert(two_sum("00123", "000456") == "579");
    assert(two_sum("01123", "000456") == "1579");
    assert(two_sum("09923", "000456") == "10379");
    assert(two_sum("2940", "098000") == "100940");
    cout << two_sum(v1, v2) << endl;
    cout << "2 * 3 = " << multiply("2", "3") << endl;
    cout << "12 * 12 = " << multiply("12", "12") << endl;
    cout << "100 * 12 = " << multiply("100", "12") << endl;
    cout << "1232221 * 12991727 = " << multiply("1232221", "12991727") << endl;
    cout << "0 * 0 = " << multiply("0", "0") << endl;
    cout << "9 * 99 = " << multiply("9", "99") << endl;
    cout << "140 * 721 = " << multiply("140", "721") << endl;

    cout << "000 fast path: " << fastest_path044({0, 0, 0}) << endl;

    auto ret = fastest_path044({2, 3, 1, 1, 0});
    cout << "23110 fast path: " << ret << endl;
    ret = fastest_path044({7, 0, 9, 6, 9, 6, 1, 7, 9, 0, 1, 2, 9, 0, 3});
    cout << "{7,0,9,6,9,6,1,7,9,0,1,2,9,0,3} fast path: " << ret << endl;

    cout << "gas: [1,2,3,4,5] cost = [3,4,5,1,2] should be 3, actually: "
         << can_complete_circuit134({1, 2, 3, 4, 5}, {3, 4, 5, 1, 2}) << endl;

    cout << "gas = [2,3,4], cost = [3,4,3] should be -1, actually: "
         << can_complete_circuit134({2, 3, 4}, {3, 4, 3}) << endl;

    cout << "gas = [3,1,1], cost = [1,2,2] should be 0, actually: "
         << can_complete_circuit134({3, 1, 1}, {1, 2, 2}) << endl;

    cout << "gas = [1,2], cost = [2,1] should be 1, actually: "
         << can_complete_circuit134({1, 2}, {2, 1}) << endl;

    largestNumber({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});

    cout << "increasingTriplet: [1,2,3,4,5] should be 1: "
         << increasingTriplet({1, 2, 3, 4, 5}) << endl;
    cout << "increasingTriplet: [5,4,3,2,1] should be 0: "
         << increasingTriplet({5, 4, 3, 2, 1}) << endl;
    cout << "increasingTriplet: [2,1,5,0,4,6] should be 1: "
         << increasingTriplet({2, 1, 5, 0, 4, 6}) << endl;
    cout << "increasingTriplet: [1] should be 0: " << increasingTriplet({1})
         << endl;
    cout << "increasingTriplet: [1,1,-2,6] should be 0: "
         << increasingTriplet({1, 1, -2, 6}) << endl;
  }
};
