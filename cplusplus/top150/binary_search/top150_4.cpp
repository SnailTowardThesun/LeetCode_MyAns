//
// Created by hankun on 2026/10/18.
//

// LeetCode 4. 寻找两个正序数组的中位数（Hard）
//
// @题目描述:
// 给定两个正序数组 nums1（长度 m）和 nums2（长度 n），返回两者的中位数。
//
// @示例:
// 输入：nums1 = [1, 3], nums2 = [2]
// 输出：2.00000
//
// @解题思路（分割二分）：
//   想象把两个数组各切一刀，所有元素分成"左半部分"和"右半部分"，满足：
//   1) 左半部分共 (m+n+1)/2 个元素（总长为奇数时左半多放一个）；
//   2) 左半的最大值 <= 右半的最小值。
//   此时中位数只由切分点旁边的 4 个数决定：
//   - 总长为奇数：中位数 = 左半最大值；
//   - 总长为偶数：中位数 = (左半最大值 + 右半最小值) / 2。
//   只在较短的数组上二分切分位置 i（i = nums1 贡献给左半的元素个数，0 <= i <= m），
//   nums2 的切分位置随之确定为 j = half - i：
//   - 若 nums1[i-1] > nums2[j]：nums1 拿多了，i 左移；
//   - 若 nums2[j-1] > nums1[i]：nums1 拿少了，i 右移；
//   - 否则切分合法，直接算中位数。
//   i、j 取到边界（0 或 m/n）时用 INT_MIN / INT_MAX 哨兵代替越界元素。
// 复杂度分析：
// - 时间复杂度：O(log(min(m, n)))。
// - 空间复杂度：O(1)。

#include <gtest/gtest.h>

#include <climits>

using namespace std;

namespace {
class Solution {
   public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // 保证 nums1 是较短的那个，二分次数为 O(log(min(m,n)))
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }

        int m = nums1.size();
        int n = nums2.size();
        int half = (m + n + 1) / 2;  // 左半部分应有的元素个数
        int lo = 0, hi = m;

        while (lo <= hi) {
            int i = (lo + hi) / 2;  // nums1 贡献给左半的元素个数，切分点在 nums1[i] 前
            int j = half - i;       // nums2 贡献给左半的元素个数

            // 哨兵：i 或 j 取到边界时，把不存在的元素当作 -inf / +inf
            int left1 = (i == 0) ? INT_MIN : nums1[i - 1];
            int right1 = (i == m) ? INT_MAX : nums1[i];
            int left2 = (j == 0) ? INT_MIN : nums2[j - 1];
            int right2 = (j == n) ? INT_MAX : nums2[j];

            if (left1 <= right2 && left2 <= right1) {
                // 切分合法：左半最大值 <= 右半最小值
                int maxLeft = max(left1, left2);
                int minRight = min(right1, right2);
                if ((m + n) % 2) {
                    return maxLeft;  // 奇数长度：左半多一个
                }
                return (maxLeft + minRight) / 2.0;  // 偶数长度取平均
            }
            if (left1 > right2) {
                hi = i - 1;  // nums1 贡献太多，切分点左移
            } else {
                lo = i + 1;  // nums1 贡献太少，切分点右移
            }
        }

        return 0.0;  // 不会到达（题目保证 m+n >= 1）
    }
};
}  // namespace

TEST(top150, 4) {
    Solution s;

    vector<int> a1{1, 3}, b1{2};
    EXPECT_DOUBLE_EQ(s.findMedianSortedArrays(a1, b1), 2.0);

    vector<int> a2{1, 2}, b2{3, 4};
    EXPECT_DOUBLE_EQ(s.findMedianSortedArrays(a2, b2), 2.5);

    vector<int> a3{0, 0}, b3{0, 0};
    EXPECT_DOUBLE_EQ(s.findMedianSortedArrays(a3, b3), 0.0);

    vector<int> a4{}, b4{1};  // 其中一个数组为空
    EXPECT_DOUBLE_EQ(s.findMedianSortedArrays(a4, b4), 1.0);

    vector<int> a5{1, 3, 5, 7, 9}, b5{2, 4, 6, 8, 10};  // 两数组交错
    EXPECT_DOUBLE_EQ(s.findMedianSortedArrays(a5, b5), 5.5);

    vector<int> a6{100000}, b6{100001};
    EXPECT_DOUBLE_EQ(s.findMedianSortedArrays(a6, b6), 100000.5);
}
