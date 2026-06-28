//
// Created by hankun on 6/28/26.
//
// @题目描述: 给你一个正整数数组 arr。请你对 arr 执行一些操作（也可以不进行任何操作），使得数组满足以下条件：
// 1. arr 中第一个元素必须为 1
// 2. 任意相邻两个元素的差的绝对值小于等于 1
// 你可以执行以下 2 种操作任意次：
// - 减小 arr 中任意元素的值，使其变为一个更小的正整数
// - 重新排列 arr 中的元素，你可以以任意顺序重新排列
// 请你返回执行以上操作后，在满足前文所述的条件下，arr 中可能的最大值
//
// @示例:
// 示例 1:
// 输入: arr = [2,2,1,2,1]
// 输出: 2
// 解释: 可以通过重新排列数组使其变为 [1,2,2,2,1]，满足条件且最大值为 2
//
// 示例 2:
// 输入: arr = [100,1,1000]
// 输出: 3
// 解释: 可以通过操作得到 [1,2,3]，满足条件且最大值为 3
//
// 示例 3:
// 输入: arr = [1,2,3,4,5]
// 输出: 5
// 解释: 数组已经满足条件，最大值为 5
//
// @解题思路:
// 1. 排序策略：首先对数组进行升序排序，这样可以从小到大处理元素
// 2. 第一个元素处理：将第一个元素强制设为 1（如果还不是 1）
// 3. 贪心调整：遍历数组，对于每个位置 i，如果当前元素与前一个元素的差值大于 1，
//    则将当前元素调整为 arr[i-1] + 1，这样可以保证相邻元素差值不超过 1
// 4. 最终结果：数组最后一个元素即为可能的最大值
//
// 时间复杂度: O(n log n)，主要是排序的时间复杂度
// 空间复杂度: O(1)，只使用了常数级别的额外空间
//
#include <gtest/gtest.h>

#include <vector>

using namespace std;

class Solution {
   public:
    int maximumElementAfterDecrementingAndRearranging(vector<int> &arr) {
        int n = arr.size();
        sort(arr.begin(), arr.end());
        if (arr[0] != 1) {
            arr[0] = 1;
        }

        for (int i = 1; i < n; i++) {
            if (abs(arr[i] - arr[i - 1]) > 1) {
                arr[i] = arr[i - 1] + 1;
            }
        }
        return arr[n - 1];
    }
};

TEST(Daily, 1846) {
    Solution s;
    vector<int> arr{100, 1, 1000};
    auto ret = s.maximumElementAfterDecrementingAndRearranging(arr);
    EXPECT_EQ(ret, 3);
}
