// @题目描述:
// 给你一个下标从 0 开始的整数数组 nums。
// 定义 nums 一个子数组的不同计数值如下：
// 令 nums[i..j] 表示 nums 中所有下标在 i 到 j 范围内的元素构成的子数组
// （满足 0 <= i <= j < nums.length），那么子数组 nums[i..j] 中
// 不同值的数目即为 nums[i..j] 的不同计数。
// 请你返回 nums 中所有子数组的不同计数的平方和。
//
// @示例:
// 输入: nums = [1,2,1]
// 输出: 15
// 解释: 六个子数组的不同计数分别为 1、1、1、2、2、2，
//       平方和 = 1 + 1 + 1 + 4 + 4 + 4 = 15
//
// 输入: nums = [2,2]
// 输出: 3
// 解释: 三个子数组的不同计数均为 1，平方和 = 3
//
// @解题思路:
// 数据规模很小（n <= 100），直接暴力枚举所有子数组：
// 1. 外层枚举子数组左端点 i；
// 2. 内层从 i 开始向右扩展右端点 j，用 unordered_set 维护当前子数组的
//    不同值集合，每加入一个元素均摊 O(1) 更新；
// 3. 每扩展一步，把当前集合大小的平方累加到答案。
// 注意内层必须从 i 开始（而不是从 0），否则会重复统计 j < i 的无效子数组。
// 答案上界约 8.7 * 10^6（n = 100 且全不同元素），int 不会溢出。
//
// 复杂度分析：
// - 时间复杂度：O(n^2)，枚举全部子数组，每个元素哈希插入均摊 O(1)
// - 空间复杂度：O(n)，哈希集合最多存 n 个不同元素
//

#include <gtest/gtest.h>

#include <unordered_set>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    int sumCounts(vector<int>& nums) {
        int ret = 0;
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            unordered_set<int> tmp;
            for (int j = i; j < n; j++) {
                tmp.insert(nums[j]);
                ret += tmp.size() * tmp.size();
            }
        }

        return ret;
    }
};
}  // namespace

TEST(Daily, 2913) {
    Solution s;

    // 官方示例 1：六个子数组的不同计数 1、1、1、2、2、2
    vector<int> nums1 = {1, 2, 1};
    EXPECT_EQ(s.sumCounts(nums1), 15);

    // 官方示例 2：三个子数组的不同计数均为 1
    vector<int> nums2 = {2, 2};
    EXPECT_EQ(s.sumCounts(nums2), 3);

    // 手算用例：[1,2] 的子数组 [1]、[2]、[1,2] → 1 + 1 + 4 = 6
    vector<int> nums3 = {1, 2};
    EXPECT_EQ(s.sumCounts(nums3), 6);

    // 边界：单元素数组
    vector<int> nums4 = {7};
    EXPECT_EQ(s.sumCounts(nums4), 1);
}
