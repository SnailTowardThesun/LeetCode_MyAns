/**
 * @file top150_no88_merge_sorted_array.cpp
 * @brief LeetCode 88. 合并两个有序数组
 *
 * @题目描述
 * 给你两个按非递减顺序排列的整数数组 nums1 和 nums2，另有两个整数 m 和 n，
 * 分别表示 nums1 和 nums2 中的元素数目。
 * 请你合并 nums2 到 nums1 中，使合并后的数组同样按非递减顺序排列。
 * 注意：最终合并后数组不应由函数返回，而是存储在数组 nums1 中。
 * 为了应对这种情况，nums1 的初始长度为 m + n，其中前 m 个元素表示应合并的元素，
 * 后 n 个元素为 0，应忽略。nums2 的长度为 n。
 *
 * @示例
 * 示例 1：
 * 输入: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
 * 输出: [1,2,2,3,5,6]
 * 解释: 需要合并 [1,2,3] 和 [2,5,6]，合并结果是 [1,2,2,3,5,6]
 *
 * 示例 2：
 * 输入: nums1 = [1], m = 1, nums2 = [], n = 0
 * 输出: [1]
 * 解释: 只需要返回 nums1 即可
 *
 * 示例 3：
 * 输入: nums1 = [0], m = 0, nums2 = [1], n = 1
 * 输出: [1]
 * 解释: nums1 中没有元素，直接将 nums2 的元素放入 nums1
 *
 * @解题思路
 * 1. 双指针法：
 *    - 使用两个指针分别指向 nums1 和 nums2 的开头
 *    - 比较两个指针指向的元素，将较小的放入临时数组
 *    - 当一个数组遍历完后，将另一个数组剩余元素直接放入临时数组
 *    - 最后将临时数组复制回 nums1
 *
 * 2. 优化思路（从后向前填充）：
 *    - 从 nums1 和 nums2 的末尾开始比较
 *    - 将较大的元素放到 nums1 的末尾
 *    - 这样可以避免使用额外空间
 *
 * @复杂度分析
 * - 时间复杂度: O(m + n)，需要遍历两个数组的所有元素
 * - 空间复杂度: O(m + n)，使用临时数组存储合并结果
 */

#include <gtest/gtest.h>
#include <vector>

using namespace std;

TEST(TOP150, No88_MergeTwoSortedLists) {
    class Solution {
    public:
        void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
            std::vector<int> container;
            container.reserve(m + n);

            int pos1 = 0, pos2 = 0;
            while (pos1 < m && pos2 < n) {
                if (nums1[pos1] < nums2[pos2]) {
                    container.emplace_back(nums1[pos1++]);
                } else {
                    container.emplace_back(nums2[pos2++]);
                }
            }

            while (pos1 < m) {
                container.emplace_back(nums1[pos1++]);
            }

            while (pos2 < n) {
                container.emplace_back(nums2[pos2++]);
            }

            nums1 = container;
        }
    };

    Solution solution;
    vector<int> nums1{1, 3, 5};
    vector<int> nums2{2, 4, 6};

    solution.merge(nums1, 3, nums2, 3);
    for (auto& i : nums1) {
        cout << i << ", ";
    }

    cout << std::endl;
}
