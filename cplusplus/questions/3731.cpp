// @题目描述:
// LeetCode 3731. 找出缺失的元素（Find Missing Elements）
// 给你一个整数数组 nums，数组由若干互不相同的整数组成。
// 数组 nums 原本包含了某个范围内的所有整数，但现在可能缺失部分整数。
// 该范围内的最小整数和最大整数仍然存在于 nums 中。
// 返回一个有序列表，包含该范围内缺失的所有整数，按从小到大排序。
// 如果没有缺失的整数，返回空列表。
//
// @示例:
// 示例 1：
// 输入：nums = [1, 4, 2, 5]
// 输出：[3]
// 解释：最小整数为 1，最大整数为 5，完整范围为 [1,2,3,4,5]，只有 3 缺失。
//
// 示例 2：
// 输入：nums = [7, 8, 6, 9]
// 输出：[]
// 解释：最小整数为 6，最大整数为 9，完整范围为 [6,7,8,9]，无缺失。
//
// 示例 3：
// 输入：nums = [5, 1]
// 输出：[2, 3, 4]
// 解释：最小整数为 1，最大整数为 5，缺失 2、3、4。
//
// @解题思路:
// 排序 + 线性扫描。利用数组排序后相邻元素递增的性质，用一个指针 pos 标记
// 当前已匹配到的位置，遍历 [min, max) 范围内的每个整数 i：
// 1. 先对 nums 排序，使 nums[0] 为最小值，nums.back() 为最大值。
// 2. 从 i = nums[0] 遍历到 i < nums.back()（最大值一定存在，无需检查）。
// 3. 若 i == nums[pos]，说明该数存在，pos 前进一步。
// 4. 若 i != nums[pos]，说明该数缺失，加入结果。
// 由于题目保证元素互不相同，排序后每个 nums[pos] 只需匹配一次。
//
// 复杂度分析：
// - 时间复杂度：O(n log n + R)，n 为数组长度，R = max - min 为值域跨度。
//   排序 O(n log n)，扫描 O(R)。题中 R <= 99，整体高效。
// - 空间复杂度：O(1)（不计输出数组），排序为原地操作。

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> findMissingElements(vector<int>& nums) {
        vector<int> ret;

        sort(nums.begin(), nums.end());
        int pos = 0;
        for (auto i = nums[0]; i < nums.back(); i++) {
            if (i != nums[pos]) {
                ret.push_back(i);
            } else {
                pos++;
            }
        }

        return ret;
    }
};

TEST(Daily, 3731) {
    Solution s;

    // 基本用例
    auto nums1 = vector<int>{1, 4, 2, 5};
    auto ans1 = vector<int>{3};
    EXPECT_EQ(s.findMissingElements(nums1), ans1);

    auto nums2 = vector<int>{7, 8, 6, 9};
    EXPECT_TRUE(s.findMissingElements(nums2).empty());  // 无缺失

    auto nums3 = vector<int>{5, 1};
    auto ans3 = vector<int>{2, 3, 4};
    EXPECT_EQ(s.findMissingElements(nums3), ans3);

    // 边界用例
    auto nums4 = vector<int>{1, 2, 3, 4, 5, 6, 7, 10};  // 缺 8, 9
    auto ans4 = vector<int>{8, 9};
    EXPECT_EQ(s.findMissingElements(nums4), ans4);

    auto nums5 = vector<int>{3, 4};  // 相邻两数，无缺失
    EXPECT_TRUE(s.findMissingElements(nums5).empty());
}
