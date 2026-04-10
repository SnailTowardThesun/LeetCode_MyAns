//
// Created by 韩堃 on 2026/4/9.
//

/*
题目：3655. 执行查询后的异或和

题目描述：
给定一个整数数组 nums 和一个二维数组 queries，其中 queries[i] = [l, r, k, v]。
对于每个查询，你需要将 nums 中从下标 l 到 r（包括 l 和 r）的元素，每隔 k 个元素（即 l, l+k, l+2k, ...）乘以 v。
所有操作完成后，返回 nums 中所有元素的异或和。

解题思路：
1. 遍历每个查询，根据查询参数修改 nums 数组
2. 对于每个查询，从 l 开始，每隔 k 个元素（l, l+k, l+2k, ...）乘以 v，并对结果取模（mod = 1e9 + 7）
3. 所有查询处理完成后，计算 nums 数组中所有元素的异或和
4. 返回异或和
*/

#include <gtest/gtest.h>
#include <vector>

using namespace std;

class Solution {
private:
    const int mod = 1e9 + 7;

public:
    int xorAfterQueries(vector<int> &nums, vector<vector<int> > &queries) {
        for (auto query: queries) {
            int64_t l = query[0], r = query[1], k = query[2], v = query[3];
            for (int i = l; i <= r; i += k) {
                nums[i] = (nums[i] * v) % mod;
            }
        }

        int ret = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            ret ^= nums[i];
        }
        return ret;
    }
};

TEST(Daily, 3655) {
    Solution s;
    std::vector<int> nums{1, 1, 1};
    std::vector<std::vector<int> > queries{{0, 2, 1, 4}};

    auto ret = s.xorAfterQueries(nums, queries);
    EXPECT_EQ(ret, 4);
}
