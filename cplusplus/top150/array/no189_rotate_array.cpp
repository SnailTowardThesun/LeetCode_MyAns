/**
 * @file no189_rotate_array.cpp
 * @brief LeetCode 189. 轮转数组
 *
 * @题目描述
 * 给定一个整数数组 nums，将数组中的元素向右轮转 k 个位置，其中 k 是非负数。
 *
 * @示例
 * 示例 1：
 * 输入: nums = [1,2,3,4,5,6,7], k = 3
 * 输出: [5,6,7,1,2,3,4]
 * 解释:
 * 向右轮转 1 步: [7,1,2,3,4,5,6]
 * 向右轮转 2 步: [6,7,1,2,3,4,5]
 * 向右轮转 3 步: [5,6,7,1,2,3,4]
 *
 * 示例 2：
 * 输入: nums = [-1,-100,3,99], k = 2
 * 输出: [3,99,-1,-100]
 * 解释:
 * 向右轮转 1 步: [99,-1,-100,3]
 * 向右轮转 2 步: [3,99,-1,-100]
 *
 * @解题思路
 * 1. 使用额外数组：
 *    - 创建一个新数组，将原数组元素放到新位置
 *    - 新位置 = (原位置 + k) % n
 *    - 最后将新数组复制回原数组
 *
 * 2. 环状替换（优化空间）：
 *    - 从第一个元素开始，将其放到正确位置
 *    - 被替换的元素继续放到它的正确位置
 *    - 直到回到起点，完成一个循环
 *    - 可能需要多个循环覆盖所有元素
 *
 * 3. 数组翻转（最优）：
 *    - 先将整个数组翻转
 *    - 再翻转前 k 个元素
 *    - 最后翻转剩余元素
 *    - 时间复杂度 O(n)，空间复杂度 O(1)
 *
 * @复杂度分析
 * - 时间复杂度: O(n)，需要遍历数组
 * - 空间复杂度: O(n)，使用额外数组存储结果
 */

#include <gtest/gtest.h>
#include <vector>

using namespace std;

TEST(TOP150, No189_RotateArray) {
    class Solution {
    public:
        void rotate(vector<int>& nums, int k) {
            auto real_steps = k % nums.size();
            std::vector<int> container(nums.end() - real_steps, nums.end());
            container.insert(container.end(), nums.begin(), nums.end() - real_steps);
            nums = container;
        }
    };

    Solution solution;
    std::vector<int> nums{-1, -100, 3, 99};
    auto k = 2;
    solution.rotate(nums, k);
}
