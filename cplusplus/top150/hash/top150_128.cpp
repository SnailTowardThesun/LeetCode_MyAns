//
// Created by hankun on 2026/10/1.
//

#include <gtest/gtest.h>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int> &nums) {
        unordered_set<int> container{nums.begin(), nums.end()};
        int ret = 1;
        for (auto it: container) {
            if (container.find(it - 1) != container.end()) { continue; }
            int next = it + 1;
            while (container.find(next) != container.end()) {
                next = next + 1;
            }

            ret = max(ret, next - it);
        }

        return ret;
    }
};

TEST(top150, 128) {
    Solution s;
    vector<int> nums{100, 4, 200, 1, 3, 2};
    auto ret = s.longestConsecutive(nums);
    EXPECT_EQ(ret, 4);
}
