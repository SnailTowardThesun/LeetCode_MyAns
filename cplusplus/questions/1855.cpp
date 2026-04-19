//
// Created by 韩堃 on 2026/4/19.
//

/*
题目：1855. 下标对中的最大距离

题目描述：
给你两个下标从 0 开始的整数数组 nums1 和 nums2。
你需要从 nums1 中选择 i，从 nums2 中选择 j，所选下标对 (i, j) 需要满足 i <= j，
并且 nums1[i] <= nums2[j]。
返回满足条件的最大距离 j - i。

解题思路：
方法一（二分查找）：
1. 对于 nums1 中的每个元素 nums1[i]，需要在 nums2 中找到满足条件的最大 j
2. 条件 nums1[i] <= nums2[j] 意味着 j 需要在 nums2 中第一个大于 nums1[i] 的位置之前
3. 使用二分查找（upper_bound）找到第一个大于 nums1[i] 的位置 pos，则满足条件的最大 j 为 pos-1
4. 如果 pos > i，则最大距离为 pos - 1 - i
5. 遍历所有 i，维护最大距离

时间复杂度：O(n log m)，其中 n 是 nums1 的长度，m 是 nums2 的长度
空间复杂度：O(1)，只使用了常数级的额外空间

方法二（双指针）：
1. 使用两个指针 i 和 j 分别指向 nums1 和 nums2 的起始位置
2. 当 nums1[i] <= nums2[j] 时，说明满足条件，更新最大距离 j - i，然后将 j 后移
3. 当 nums1[i] > nums2[j] 时，说明不满足条件，将 i 后移
4. 重复上述步骤直到任一数组遍历完毕

时间复杂度：O(n + m)，其中 n 和 m 分别是两个数组的长度
空间复杂度：O(1)，只使用了常数级的额外空间
*/

#include <gtest/gtest.h>

#include <vector>

using namespace std;

class Solution {
   public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        int ret = 0;
        for (int i = 0; i < nums1.size(); ++i) {
            auto t = nums1[i];
            auto pos = upper_bound(nums2.begin(), nums2.end(), t, greater<int>{}) - nums2.begin();
            if (pos > i) {
                ret = max(ret, static_cast<int>(pos - 1 - i));
            }
        }

        return ret;
    }
};

class Solution2 {
   public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        int ret = 0;
        int i = 0, j = 0;
        while (i < nums1.size() && j < nums2.size()) {
            if (nums1[i] <= nums2[j]) {
                ret = max(ret, j - i);
                ++j;
            } else {
                ++i;
            }
        }

        return ret;
    }
};

TEST(Daily, 1855) {
    Solution s;
    auto nums1 = vector<int>{55, 30, 5, 4, 2};
    auto nums2 = vector<int>{100, 20, 10, 10, 5};
    auto ret = s.maxDistance(nums1, nums2);
    EXPECT_EQ(ret, 2);
}
