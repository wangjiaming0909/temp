#include "leetcode.h"
#include <cassert>

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

  void test() override {
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
         << can_complete_circuit134({1,2}, {2,1}) << endl;

    largestNumber({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});

    cout << "increasingTriplet: [1,2,3,4,5] should be 1: " << increasingTriplet({1,2,3,4,5}) << endl;
    cout << "increasingTriplet: [5,4,3,2,1] should be 0: " << increasingTriplet({5,4,3,2,1}) << endl;
    cout << "increasingTriplet: [2,1,5,0,4,6] should be 1: " << increasingTriplet({2,1,5,0,4,6}) << endl;
    cout << "increasingTriplet: [1] should be 0: " << increasingTriplet({1}) << endl;
    cout << "increasingTriplet: [1,1,-2,6] should be 0: " << increasingTriplet({1,1,-2,6}) << endl;
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
};
