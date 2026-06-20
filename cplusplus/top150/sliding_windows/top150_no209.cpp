//
// Created by hankun on 6/20/26.
//
#include <gtest/gtest.h>

#include <climits>
#include <vector>

using namespace std;

class Solution {
   public:
    int minSubArrayLen(int target, vector<int> &nums) {
        int n = nums.size();
        int left = 0;
        int sum = 0;
        int result = INT_MAX;

        for (int right = 0; right < n; right++) {
            sum += nums[right];

            while (sum >= target) {
                result = min(result, right - left + 1);
                sum -= nums[left];
                left++;
            }
        }

        return result == INT_MAX ? 0 : result;
    }
};

TEST(TOP150, 209) {
    auto target = 7;
    vector<int> nums{2, 3, 1, 2, 4, 3};
    Solution s;
    auto ret = s.minSubArrayLen(target, nums);
    EXPECT_EQ(ret, 2);
}
