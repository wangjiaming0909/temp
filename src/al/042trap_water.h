#include "leetcode.h"

namespace al {

struct TrapWater : public al::ILeetCode {
public:
  int trap_with_two_pointer(vector<int> & height) {
    if (height.empty()) return 0;
    unsigned int left = 0, right = height.size() - 1;
    unsigned int total = 0, left_max = height.front(), right_max = height.back();

    while (left < right) {
      if (height[left] <= height[right]) {
        if (left_max <= height[1 + left]) {
          left_max = height[1 + left];
        } else {
          total += std::min(left_max, right_max) - height[left + 1];
        }
        left++;
      } else {
        if (right_max <= height[right-1]) {
          right_max = height[right-1];
        } else {
          total += std::min(left_max, right_max) - height[right - 1];
        }
        right--;
      }
    }
    if (left == right) total += std::min(left_max, right_max) - height[left];
    return total;
  }

  int trap_with_stack(vector<int> &height) {
    stack<pair<int, int>> s;
    int total = 0;

    for (int i = 0; i < height.size(); i++) {
      // going down
      if (s.empty() || s.top().second >= height[i]) {
        s.push({i, height[i]});
        //cout << "pushed: " << i << " val: " << height[i] << endl;
        continue;
      }
      auto& top = s.top();

      // going up
      while(top.second < height[i]) {
        //cout << "poped: " << top.first << " val: " << top.second << endl;
        s.pop();
        if (s.empty()) break;
        int width = i - s.top().first - 1;
        int h = std::min(height[i], s.top().second) - top.second;
        //cout << "added: " << width * h << endl;
        total += width * h;
        top = s.top();
      }
      s.push({i, height[i]});
      //cout << "pushed: " << i << " val: " << height[i] << endl;
    }
    return total;
  }

  int trap_with_dp(vector<int> &height) {
    vector<int> dp_forward;
    dp_forward.resize(height.size(), 0);
    dp_forward.front() = height.front();
    int total = 0;

    for (int i = 1; i < height.size(); ++i) {
      dp_forward[i] = std::max(dp_forward[i-1], height[i]);
    }

    dp_forward.back() = std::min(height.back(), dp_forward.back());
    for (int i = height.size()-2; i >= 0; --i) {
      dp_forward[i] = std::min(dp_forward[i], std::max(dp_forward[i+1], height[i]));
    }

    for (int i = 0; i < height.size(); ++i) {
      total += dp_forward[i] > height[i] ? dp_forward[i] - height[i] : 0;
    }
    return total;
  }

  void test(vector<int> height) {
    cout << "---------------------------------" << endl;
    cout << trap_with_dp(height) << endl;
    cout << trap_with_stack(height) << endl;
    cout << trap_with_two_pointer(height) << endl;
  }

  void test() override {
    vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
    test(height);
    height = { 4,2,0,3,2,5 };
    test(height);
  }
};
}
