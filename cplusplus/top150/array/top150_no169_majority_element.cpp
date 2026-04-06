/**
 * @file top150_no169_majority_element.cpp
 * @brief LeetCode 169. 多数元素
 *
 * @题目描述
 * 给定一个大小为 n 的数组 nums，返回其中的多数元素。多数元素是指在数组中出现次数
 * 大于 ⌊ n/2 ⌋ 的元素。你可以假设数组是非空的，并且给定的数组总是存在多数元素。
 *
 * @示例
 * 示例 1：
 * 输入: nums = [3,2,3]
 * 输出: 3
 *
 * 示例 2：
 * 输入: nums = [2,2,1,1,1,2,2]
 * 输出: 2
 *
 * @解题思路
 * 1. 摩尔投票法（Boyer-Moore Voting Algorithm）：
 *    - 核心思想：多数元素出现的次数大于其他所有元素出现次数之和
 *    - 维护一个候选元素和计数器
 *    - 遍历数组：
 *      - 计数器为 0 时，选择当前元素作为候选
 *      - 当前元素等于候选时，计数器加 1
 *      - 当前元素不等于候选时，计数器减 1
 *    - 最后候选元素即为多数元素
 *
 * 2. 哈希表法：
 *    - 使用哈希表统计每个元素出现次数
 *    - 找到出现次数大于 n/2 的元素
 *    - 时间复杂度 O(n)，空间复杂度 O(n)
 *
 * 3. 排序法：
 *    - 将数组排序
 *    - 中间位置的元素一定是多数元素
 *    - 时间复杂度 O(n log n)，空间复杂度 O(1) 或 O(log n)
 *
 * @复杂度分析
 * - 时间复杂度: O(n)，只需要遍历数组一次
 * - 空间复杂度: O(1)，只使用常数额外空间
 */

#include <gtest/gtest.h>
#include <vector>

using namespace std;

TEST(TOP150, No169_MajorityElement) {
    class Solution {
    public:
        int majority_element(vector<int>& nums) {
            auto candidate = -1;
            auto count = 0;
            for (auto& i : nums) {
                if (count == 0) {
                    candidate = i;
                    count = 1;
                } else if (candidate == i) {
                    count++;
                } else {
                    count--;
                }
            }

            return candidate;
        }
    };

    Solution solution;
    std::vector<int> nums{3, 2, 3};
    auto ret = solution.majority_element(nums);

    EXPECT_EQ(ret, 3);
}
