//
// Created by hankun on 2026/10/1.
//

#include <gtest/gtest.h>
using namespace std;

class Solution {
public:
    vector<string> summaryRanges(vector<int> &nums) {
        vector<string> ret;

        int left = 0;
        while (left < nums.size()) {
            string tmp = to_string(nums[left]);
            int right = left + 1;
            while (right < nums.size()) {
                if (nums[right] != nums[right - 1] + 1) {
                    break;
                }
                right++;
            }

            if (right > left + 1) {
                tmp += "->";
                tmp += to_string(nums[right-1]);
            }
            ret.push_back(tmp);
            left = right;
        }


        return ret;
    }
};

TEST(top150, 228) {
    Solution s;
    vector<int> nums{0, 1, 2, 4, 5, 7};
    auto ret = s.summaryRanges(nums);
    EXPECT_EQ(ret.size(), 3);
}
