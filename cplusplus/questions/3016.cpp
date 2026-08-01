// @题目描述:
// 给你一个字符串 word，由不同的小写英文字母组成。
// 电话按键上将一些字母映射到数字键 2-9（共 8 个键），每个键可以映射任意数量的字母。
// 每个键上的字母按顺序排列，第 1 个字母需要按 1 次，第 2 个需要按 2 次，以此类推。
// 你可以自定义字母到按键的映射方式。返回输入 word 所需的最少按键次数。
//
// @示例:
// 示例 1：
// 输入：word = "abcde"
// 输出：5
// 解释：将 a、b、c、d、e 分别映射到不同键的第 1 位，每个字母按 1 次，共 5 次。
//
// 示例 2：
// 输入：word = "xyzxyzxyzxyz"
// 输出：12
// 解释：x、y、z 各出现 4 次。将它们映射到 3 个键的第 1 位，每个按 1 次，共 4×3 = 12 次。
//
// 示例 3：
// 输入：word = "aabbccddeeffff"
// 输出：14
// 解释：f 出现 4 次映射到第 1 位（4×1=4），a~e 各出现 2 次映射到第 1 位（5×2×1=10），共 14 次。
//
// @解题思路:
// 贪心算法：频率高的字母优先映射到按键第 1 位（按 1 次），次高的映射到第 2 位（按 2 次），以此类推。
// 1. 统计每个字母的出现频率
// 2. 按频率降序排序
// 3. 前 8 个字母各按 1 次，第 9-16 个各按 2 次，第 17-24 个各按 3 次，以此类推
// 4. 累加 每个字母频率 × 所需按键次数
//
// 复杂度分析：
// - 时间复杂度：O(n + 26 log 26) ≈ O(n)，n 为 word 长度
// - 空间复杂度：O(1)，固定 26 个字母

#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <string>

using namespace std;

class Solution {
   public:
    int minimumPushes(string word) {
        array<int, 26> freq{};
        for (char c : word) {
            freq[c - 'a']++;
        }

        sort(freq.begin(), freq.end(), greater<int>());

        int ret = 0;
        for (int i = 0; i < 26 && freq[i] > 0; i++) {
            ret += (i / 8 + 1) * freq[i];
        }
        return ret;
    }
};

TEST(Daily, 3016) {
    Solution s;

    EXPECT_EQ(s.minimumPushes("abcde"), 5);
    EXPECT_EQ(s.minimumPushes("xyzxyzxyzxyz"), 12);
    EXPECT_EQ(s.minimumPushes("aabbccddeeffff"), 14);
}
