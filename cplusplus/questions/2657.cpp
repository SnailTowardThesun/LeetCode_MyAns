//
// Created by hankun on 5/20/26.
//

/**
 * @题目描述
 * 2657. 找到两个数组的前缀公共数组
 * 给你两个下标从 0 开始长度为 n 的整数排列 A 和 B。
 * A 和 B 的前缀公共数组定义为数组 C，其中 C[i] 是数组 A 和 B 到下标为 i 之前公共元素的数目。
 * 请你返回 A 和 B 的前缀公共数组。
 * 如果一个长度为 n 的数组包含 1 到 n 的元素恰好一次，我们称这个数组是一个长度为 n 的排列。
 *
 * @示例
 * 示例 1:
 * 输入: A = [1,3,2,4], B = [3,1,2,4]
 * 输出: [0,2,3,4]
 * 解释:
 * i = 0: 没有公共元素，所以 C[0] = 0
 * i = 1: 1 和 3 是两个数组的前缀公共元素，所以 C[1] = 2
 * i = 2: 1, 2 和 3 是两个数组的前缀公共元素，所以 C[2] = 3
 * i = 3: 1, 2, 3 和 4 是两个数组的前缀公共元素，所以 C[3] = 4
 *
 * 示例 2:
 * 输入: A = [2,3,1], B = [3,1,2]
 * 输出: [0,1,3]
 * 解释:
 * i = 0: 没有公共元素，所以 C[0] = 0
 * i = 1: 只有 3 是公共元素，所以 C[1] = 1
 * i = 2: 1, 2 和 3 是两个数组的前缀公共元素，所以 C[2] = 3
 *
 * @解题思路
 * 方法一：双计数数组法
 * 1. 使用两个计数数组 cnt1 和 cnt2 分别记录 A 和 B 中每个元素出现的次数
 * 2. 遍历数组 A 和 B，每次增加对应元素的计数
 * 3. 枚举所有可能的元素值 1 到 n，累加 min(cnt1[j], cnt2[j]) 到答案中
 *
 * 时间复杂度: O(n²)，其中 n 是数组长度
 * 空间复杂度: O(n)
 *
 * 方法二：位运算优化
 * 1. 使用一个数组 visited 记录每个元素的出现状态
 * 2. 使用异或操作来切换状态
 * 3. 使用位运算快速计算公共元素个数
 *
 * 时间复杂度: O(n)
 * 空间复杂度: O(n)
 */

#include <gtest/gtest.h>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        int n = static_cast<int>(A.size());
        vector<int> ans(n);
        vector<int> cnt1(n + 1, 0), cnt2(n + 1, 0);

        for (int i = 0; i < n; ++i) {
            ++cnt1[A[i]];
            ++cnt2[B[i]];

            for (int j = 1; j <= n; ++j) {
                ans[i] += min(cnt1[j], cnt2[j]);
            }
        }

        return ans;
    }
};

TEST(Daily, 2657) {
    Solution s;

    // 测试用例 1：基本示例
    auto A1 = vector<int>{1, 3, 2, 4};
    auto B1 = vector<int>{3, 1, 2, 4};
    auto ret1 = s.findThePrefixCommonArray(A1, B1);
    EXPECT_EQ(ret1.size(), 4);
    EXPECT_EQ(ret1[0], 0);
    EXPECT_EQ(ret1[1], 2);
    EXPECT_EQ(ret1[2], 3);
    EXPECT_EQ(ret1[3], 4);

    // 测试用例 2：另一个基本示例
    auto A2 = vector<int>{2, 3, 1};
    auto B2 = vector<int>{3, 1, 2};
    auto ret2 = s.findThePrefixCommonArray(A2, B2);
    EXPECT_EQ(ret2.size(), 3);
    EXPECT_EQ(ret2[0], 0);
    EXPECT_EQ(ret2[1], 1);
    EXPECT_EQ(ret2[2], 3);

    // 测试用例 3：完全相同数组
    auto A3 = vector<int>{1, 2, 3, 4, 5};
    auto B3 = vector<int>{1, 2, 3, 4, 5};
    auto ret3 = s.findThePrefixCommonArray(A3, B3);
    EXPECT_EQ(ret3.size(), 5);
    EXPECT_EQ(ret3[0], 1);
    EXPECT_EQ(ret3[1], 2);
    EXPECT_EQ(ret3[2], 3);
    EXPECT_EQ(ret3[3], 4);
    EXPECT_EQ(ret3[4], 5);

    // 测试用例 4：完全相反顺序
    auto A4 = vector<int>{1, 2, 3, 4};
    auto B4 = vector<int>{4, 3, 2, 1};
    auto ret4 = s.findThePrefixCommonArray(A4, B4);
    EXPECT_EQ(ret4.size(), 4);
    EXPECT_EQ(ret4[0], 0);
    EXPECT_EQ(ret4[1], 0);
    EXPECT_EQ(ret4[2], 2);
    EXPECT_EQ(ret4[3], 4);

    // 测试用例 5：长度为 1
    auto A5 = vector<int>{1};
    auto B5 = vector<int>{1};
    auto ret5 = s.findThePrefixCommonArray(A5, B5);
    EXPECT_EQ(ret5.size(), 1);
    EXPECT_EQ(ret5[0], 1);
}