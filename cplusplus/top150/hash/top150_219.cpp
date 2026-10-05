//
// Created by hankun on 2026/10/1.
//

#include <gtest/gtest.h>

using namespace std;

class Solution {
public:
    bool containsNearbyDuplicate(vector<int> &nums, int k) {
        unordered_map<int, int> container;
        for (auto i = 0; i < nums.size(); i++) {
            if (container.find(nums[i]) != container.end()) {
                auto diff = abs(i - container[nums[i]]);
                if (diff <= k) {
                    return true;
                }
            }
            container[nums[i]] = i;
        }

        return false;
    }
};

TEST(top150, 219) {
    Solution s;
    vector<int> nums{1, 2, 3, 1};
    auto k = 3;
    auto ret = s.containsNearbyDuplicate(nums, k);
    EXPECT_TRUE(ret);
}
