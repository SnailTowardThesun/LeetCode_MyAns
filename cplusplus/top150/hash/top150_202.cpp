//
// Created by hankun on 2026/10/1.
//

/**
 * @file top150_202.cpp
 * @brief LeetCode 202. 快乐数
 *
 * @题目描述
 * 编写一个算法来判断一个数 n 是不是快乐数。
 * 快乐数定义为：
 * - 对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和；
 * - 然后重复这个过程直到这个数变为 1，也可能是无限循环但始终变不到 1；
 * - 如果这个过程的结果为 1，那么这个数就是快乐数。
 * 如果 n 是快乐数就返回 true；不是则返回 false。
 *
 * @示例
 * 示例 1：
 * 输入：n = 19
 * 输出：true
 * 解释：
 * 1^2 + 9^2 = 82
 * 8^2 + 2^2 = 68
 * 6^2 + 8^2 = 100
 * 1^2 + 0^2 + 0^2 = 1
 *
 * 示例 2：
 * 输入：n = 2
 * 输出：false
 * 解释：平方和会在 4, 16, 37, 58, 89, 145, 42, 20 中无限循环。
 *
 * @解题思路
 * 1. 快慢指针（弗洛伊德判圈法）：
 *    - 关键洞察：非快乐数的平方和序列会进入循环，
 *      这与"链表有环"在结构上完全等价
 *    - helper：计算数位平方和，相当于链表的 next 指针
 *    - slow 每次走一步（一次 helper），fast 每次走两步（两次 helper）
 *    - 若序列最终到 1：序列收敛，fast 与 slow 在 1 处相遇
 *    - 若序列有环：fast 会在环内追上 slow
 *    - 相遇时判断 slow == 1 即可区分两种情况
 *
 * 2. 复杂度分析：
 *    - 时间复杂度: O(log n)，数位平方和下降极快，判圈步数为常数级
 *    - 空间复杂度: O(1)，只用两个指针变量
 */

#include <gtest/gtest.h>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    bool isHappy(int n) {
        int fast = n;
        int slow = n;

        auto helper = [](int n) {
            int sum = 0;

            while (n > 0) {
                int d = n % 10;
                sum = sum + d * d;
                n = n / 10;
            }

            return sum;
        };

        do {
            slow = helper(slow);
            fast = helper(fast);
            fast = helper(fast);
        } while (fast != slow);

        return slow == 1;
    }
};
}  // namespace

TEST(top150, 202) {
    Solution s;
    auto n = 19;
    auto ret = s.isHappy(n);
    EXPECT_EQ(ret, true);
}
