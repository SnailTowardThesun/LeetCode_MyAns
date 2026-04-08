//
// Created by 韩堃 on 2026/4/8.
//

/*
 * 题目描述：
 * 给定一个整数数组 nums 和一个查询数组 queries，其中 queries[i] = [l, r, k, v]。
 * 对于每个查询，你需要对 nums 数组执行以下操作：将区间 [l, r] 中步长为 k 的元素都乘以 v，
 * 并对结果取模 1e9+7。执行完所有查询后，计算并返回数组中所有元素的异或结果。
 *
 * 示例：
 * 输入：nums = [1, 1, 1], queries = [[0, 2, 1, 4]]
 * 输出：4
 * 解释：执行查询后，nums 变为 [4, 4, 4]，异或结果为 4 ^ 4 ^ 4 = 4
 *
 * 解题思路：
 * 1. 遍历每个查询，对指定区间内步长为 k 的元素执行乘法操作并取模
 * 2. 执行完所有查询后，计算整个数组的异或结果
 * 3. 注意处理数据类型，使用 int64_t 避免溢出
 *
 * 时间复杂度：O(q * (r-l)/k)，其中 q 是查询次数，(r-l)/k 是每个查询处理的元素个数
 * 空间复杂度：O(1)，除了存储输入数据外，不需要额外空间
 */

#include <gtest/gtest.h>

#include <vector>

class Solution {
   public:
    int xorAfterQueries(std::vector<int>& nums, std::vector<std::vector<int> >& queries) {
        int mod = 1e9 + 7;
        // 处理每个查询
        for (auto query : queries) {
            int64_t l = query[0], r = query[1], k = query[2], v = query[3];
            // 对区间 [l, r] 中步长为 k 的元素执行乘法操作
            for (int i = l; i <= r; i += k) {
                nums[i] = (nums[i] * v) % mod;
            }
        }

        // 计算所有元素的异或结果
        int ret = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            ret ^= nums[i];
        }
        return ret;
    }
};

TEST(Daily, 3653) {
    Solution s;
    std::vector<int> nums{1, 1, 1};
    std::vector<std::vector<int> > queries{{0, 2, 1, 4}};

    auto ret = s.xorAfterQueries(nums, queries);
    EXPECT_EQ(ret, 4);
}
