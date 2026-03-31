//
// Created by 韩堃 on 2026/3/31.
//

/*
题目：生成满足条件的字符串

描述：
给定两个字符串 str1 和 str2，生成一个满足以下条件的字符串：
1. 对于 str1 中的每个 'T'，表示在该位置开始的 str2 长度的子串必须等于 str2
2. 对于 str1 中的每个 'F'，表示在该位置开始的 str2 长度的子串必须不等于 str2
3. 生成的字符串长度为 str1.length() + str2.length() - 1
4. 如果不存在满足条件的字符串，返回空字符串
5. 生成的字符串应该是字典序最小的

输入：
- str1: 由 'T' 和 'F' 组成的字符串
- str2: 任意字符串

输出：
- 满足条件的字符串，或空字符串
*/

#include <gtest/gtest.h>

#include <vector>
using namespace std;

class Solution {
   public:
    /*
    解题思路：
    1. 初始化：
       - container：存储生成的字符串，初始化为全 'a'（字典序最小的字符）
       - position_container：标记哪些位置已经被确定，初始化为 0（未确定）

    2. 处理 'T' 约束：
       - 对于每个 'T'，将对应的子串设置为 str2
       - 如果该位置已经被设置且与 str2 不匹配，返回空字符串

    3. 处理 'F' 约束：
       - 对于每个 'F'，检查当前子串是否等于 str2
       - 如果不等于，跳过（已经满足约束）
       - 如果等于，需要修改该子串中的一个字符
       - 为了保持字典序最小，选择最右边的未标记位置进行修改
       - 修改为当前字符的下一个字符（循环，'z' 之后是 'a'）
       - 标记该位置为已确定

    4. 生成结果字符串并返回
    */
    string generateString(string str1, string str2) {
        int str1_m = str1.length();
        int str2_n = str2.length();

        string ret;

        vector<int> position_container(str1_m + str2_n - 1, 0);  // 0: 未确定, 1: 已确定
        vector<char> container(str1_m + str2_n - 1, 'a');        // 初始化为全 'a'

        for (auto i = 0; i < str1.length(); i++) {
            // for T
            if (str1.at(i) == 'T') {
                if (i + str2_n > position_container.size()) {
                    return "";
                }
                for (int j = i; j < i + str2_n; j++) {
                    if (position_container[j] == 1 && container[j] != str2.at(j - i)) {
                        return "";
                    }
                    container[j] = str2.at(j - i);
                    position_container[j] = 1;
                }
            }
        }

        for (auto i = 0; i < str1.length(); i++) {
            // for F
            if (str1.at(i) == 'F') {
                if (i + str2_n > position_container.size()) {
                    continue;
                }
                bool is_equal = true;
                for (int j = i; j < i + str2_n; j++) {
                    if (container[j] != str2.at(j - i)) {
                        is_equal = false;
                        break;
                    }
                }

                if (!is_equal) {
                    continue;
                }

                /*
                修复理由：
                原代码选择最左边的未标记位置进行修改，但这会导致生成的字符串不是字典序最小的。
                例如，在位置 500 处，原代码会将 'a' 改为 'b'，但期望输出是保持 'a'。

                正确的做法是选择最右边的未标记位置进行修改，这样可以：
                1. 保持左边的字符尽可能小（字典序优先）
                2. 只修改最右边的必要位置，最小化对字符串的影响
                3. 确保生成的字符串满足 'F' 约束的同时，字典序最小
                */
                // Find the rightmost position that can be modified
                int modify_pos = -1;
                for (int j = i + str2_n - 1; j >= i; j--) {
                    if (position_container[j] == 0) {
                        modify_pos = j;
                        break;
                    }
                }

                if (modify_pos == -1) {
                    return "";
                }

                container[modify_pos] = (container[modify_pos] - 'a' + 1) % 26 + 'a';
                position_container[modify_pos] = 1;
            }
        }

        ret = string(container.begin(), container.end());
        return ret;
    }
};

TEST(Daily, 3474) {
    Solution s;
    string str1_long =
        "TFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
        "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
        "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
        "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
        "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
        "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
        "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
        "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
        "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
        "FFFFFFFFT";
    string str2_long =
        "baaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
    string result_long =
        "baaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaabbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";

    auto ret = s.generateString(str1_long, str2_long);

    EXPECT_EQ(ret, result_long);
}
