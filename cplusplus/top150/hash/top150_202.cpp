//
// Created by hankun on 2026/10/1.
//

#include <gtest/gtest.h>

using namespace std;

class Solution {
public:
    bool isHappy(int n) {
        int fast = n;
        int slow = n;

        auto helper = [](int n) {
            int sum = 0;

            while (n > 0) {
                int d = n % 10;
                sum = sum + d * d;
                n = n / 10;
            }

            return sum;
        };

        do {
            slow = helper(slow);
            fast = helper(fast);
            fast = helper(fast);
        } while (fast != slow);

        return slow == 1;
    }
};

TEST(top150, 202) {
    Solution s;
    auto n = 19;
    auto ret = s.isHappy(n);
    EXPECT_EQ(ret, true);
}
