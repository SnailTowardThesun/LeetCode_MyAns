//
// Created by 韩堃 on 2026/4/6.
//

#include <gtest/gtest.h>

#include <vector>
using namespace std;

class Solution {
public:
    bool judgeCircle(string moves) {
        vector<int> container(4, 0);
        for (auto i : moves) {
            if (i == 'U') {
                container[0]++;
            } else if (i == 'D') {
                container[1]++;
            } else if (i == 'L') {
                container[2]++;
            } else if (i == 'R') {
                container[3]++;
            }
        }

        return container[0] == container[1] && container[2] == container[3];
    }
};

TEST(Daily, 657) {
    string moves = "UD";
    Solution s;
    auto ret = s.judgeCircle(moves);
    EXPECT_TRUE(ret);
}
