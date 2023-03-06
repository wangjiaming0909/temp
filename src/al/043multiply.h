#include "leetcode.h"
#include <cassert>

struct Multiply : public al::ILeetCode
{
  //       1 2 3   <------num1
  //       4 5 6   <------num2
  //   -----------
  //     0 7 3 8   <------ret[0]
  //     5 1 5 0   <------ret[1]
  string multiply(string num1, string num2) {
    int i = num2.size()-1;
    int j = num1.size()-1;

    vector<string> ret;
    ret.resize(num2.size());
    for (auto& v : ret) {
      v.resize(num1.size() + num2.size(), 48);
    }

    for (; i >= 0; --i) {
      unsigned char plus = 0;
      for (; j >=0; --j) {
        char down = num2[i] - 48;
        char up = num1[j] - 48;
        unsigned int val = down * up + plus;
        ret[num2.size() - i - 1][i+j+1] = val%10 + 48;
        plus = val / 10;
      }
      ret[num2.size() - i - 1][i] = plus + 48;
      j = num1.size() - 1;
    }

    string r(1,48);
    i = num1.size() + num2.size();
    for (auto &s : ret) {
      r = two_sum(s, r);
    }
    return r.empty() ? "0" : r;
  }

  // 123 + 456 = 567
  string two_sum(const string& v1, const string& v2) {
    string s;
    s.resize(v1.size() + v2.size() + 1, 48);
    int i = v1.size() - 1;
    int j = v2.size() - 1;

    char plus_1 = 0;
    while(i >= 0 && j >= 0) {
      auto val = v1[i] + v2[j] - 96 + plus_1;
      plus_1 = val / 10;
      s[v1.size() - 1 - i] = (val >= 10 ? val%10 : val) + 48;
      --i;
      --j;
    }
    if (v1.size() > v2.size()) {
      for (i = v2.size(); i < v1.size(); ++i) {
        s[i] = v1[v1.size() - i - 1] + plus_1;
        plus_1 = (s[i] -48 ) / 10;
        s[i] = (s[i]-48) % 10 + 48;
      }
      if (plus_1)
        s[i] = 1;
    } else if (v1.size() < v2.size()) {
      for (i = v1.size(); i < v2.size(); ++i) {
        s[i] = v2[v2.size() - i - 1] + plus_1;
        plus_1 = (s[i] - 48) / 10;
        s[i] = (s[i]-48) % 10 + 48;
      }
      if (plus_1)
        s[i] = 1;
    }
    std::reverse(s.begin(), s.end());
    i = 0;
    while (s[i++] == '0') { }
    return s.substr(i-1);
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
  }
};
