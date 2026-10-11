//
// Created by hankun on 2026/10/1.
//

/**
 * @file top150_228.cpp
 * @brief LeetCode 228. 汇总区间
 *
 * @题目描述
 * 给定一个无重复元素的有序整数数组 nums，返回恰好覆盖数组中所有数字的
 * 最小有序区间范围列表。也就是说，nums 的每个元素都恰好被某个区间范围所覆盖，
 * 并且不存在属于某个范围但不属于 nums 的数字。
 * 列表中的每个区间范围 [a,b] 应该按如下格式输出：
 * - "a->b"：如果 a != b
 * - "a"：如果 a == b
 *
 * @示例
 * 示例 1：
 * 输入：nums = [0,1,2,4,5,7]
 * 输出：["0->2","4->5","7"]
 *
 * 示例 2：
 * 输入：nums = [0,2,3,4,6,8,9]
 * 输出：["0","2->4","6","8->9"]
 *
 * @解题思路
 * 1. 双指针扫描连续段：
 *    - 外层指针 left 指向当前连续段的起点
 *    - 内层指针 right 从 left+1 开始右移，只要 nums[right] == nums[right-1] + 1
 *      就继续延伸；一旦断开即停止
 *    - 若 right 停在 left+1 之后，说明这段长度大于 1，输出 "起点->终点"
 *    - 否则该段只有一个元素，直接输出 "起点"
 *    - 将 left 跳到 right，开始下一段扫描
 *
 * 2. 复杂度分析：
 *    - 时间复杂度: O(n)，每个元素只被访问一次
 *    - 空间复杂度: O(1)，不计输出数组
 */

#include <gtest/gtest.h>
using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    vector<string> summaryRanges(vector<int>& nums) {
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
                tmp += to_string(nums[right - 1]);
            }
            ret.push_back(tmp);
            left = right;
        }

        return ret;
    }
};
}  // namespace

TEST(top150, 228) {
    Solution s;
    vector<int> nums{0, 1, 2, 4, 5, 7};
    auto ret = s.summaryRanges(nums);
    EXPECT_EQ(ret.size(), 3);
}
