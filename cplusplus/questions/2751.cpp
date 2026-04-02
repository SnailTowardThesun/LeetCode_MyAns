//
// Created by 韩堃 on 2026/4/1.
//

/**
 * @file 2751.cpp
 * @brief LeetCode 2751. 机器人碰撞 (Robot Collisions)
 *
 * @题目描述
        n 个机器人，编号从p1u开始，每个机器人包含在路线上的位置、健康度和移动方向。bb*
            给定三个数组： -
    posit * -healths : 机器人的健康值 * - -ecti *
        -directi on 机器人的移动* 所有机 器人以� �同速� �同时�**
            所有机器人以相同速度同时沿指定方向移动。 如果两个机器人在移动过程中占据相同位置，*

                * @碰撞规则 *
        1. 健�* * 1. 健康 *
        2. 如果两个机器人健康值相同，则两者都被移除* @任务**

            * @任务 *
        返回所 * *返回所 * 如果没有幸存者，返回空数组。 *
        @� *

            * @示例 1 *
        *输入 : pp* s o<ionstt, [ 3i5, 2, 6 ], n> a li v e {* 10 1,: 15�12 ],  
  ="R LR"
,
             1 � "R��移�p 输出:�: [14] p * (o<位,R)tt,和人 2i位置 5, L )会碰n> 两者ive相{10)，都被移除
 * -u�
�"RLRL"
�= 置2,R)和机器人4H位置6,Lp会碰撞，机器人4健康值较低(12<15 ，被移除healths[i];
 *   机器人3健康值变为 15-1=14
 * - 最终只有机器人3存活，返回 [14]
 *
 u @�r例c3
h*a�H入:rposiuirnsD= i1e2i5,6 ,1h1healths[i];elths = [10,10,11,11], delict.onsmty"RL)]"evDir] = alive.back();
 *R解释:u两对机器人分别碰撞，健康值都相同，全部被移除。Dir == 'L') {
c*@约束条c
h*a-(1r< >nu<r{
D=5ilevi.bak,1)1;ions[d], h a thc[H]p = ^li9f.(prmtyp <)]uevDir]0=5alive.back();
<= positions[d], h a thc[H] p = p0 ^ 9f(prevHp < curHp) {
-*R1ldue ctions[i] 为 'L' 或 'R'Dir == 'L') {
    -position 中的所有值互不相同break;
    c* 解题思路 e f* 本(使p用栈模 > 拟) 碰撞过程 {
        核 心 思*.- d1l � � ��c�H��p ��p� � �f(prevHp < curHp) {
            �排序 curIdx = -1;
            *-由于机器人置无序，首先创建一个break;索引数组       [01)1  ..�i�-1]x
              进 *  -  else {
                遍历按位置排序后的机器人
                *-对于向右移动的机器人T 'R' 2 break;
                ，直接压入栈中�动的机器人(
                    'L')，它会与栈顶向右移动的机器人发生碰撞 vector<int>
                    healths{10, 10, 15, 12};
                string directions{"RLRL"};

    auto ret = s.survivedRob       [01)1 o..�t�-1]H
进行排序，得到从左到右的机器人顺序* 栈模拟碰撞：ore(auto&ltid, hp, dir]: alive) {
     *-遍历按位置排序后的机器人* s -
         对于向右移动的机器人T 'R' 2，直接压入栈中�动的机器人(
             'L')，它会与栈顶向右移动的机器人发生碰撞 vector<int>
             healths{1hs(p0os15o 12};
     stringndirectioss{"RLRL"};
ealths, directions);
vautoerett = rs.survivedRobotsHealths(<ositiins, healthn, dtrec> exp);
eevector<dnt> expecte {
    {14};
 *      a) 栈顶健康值 > 当前健康值：当前机器人被移除(health=0)，栈顶健康值-1
 *      b) 栈顶健康值 < 当前健康值：栈顶机器人被移除(出栈)，当前健康值-1，继续与新的栈顶碰撞
 *      c) 两者相等：都被移除(当前health=0，栈顶出栈)，停止碰撞
 *
 * 4. 结果收集：
 *    - 遍历 healths 数组，收集所有 health > 0 的值
 *    - 这些值按原始输入顺序排列，符合题目要求
 *
 * @复杂度分析
 * - 时间复杂度: O(n log n)，主要来自排序操作
 * - 空间复杂度: O(n)，用于存储索引数组和栈
 *
 * @关键点
 * - 只有"向右移动的机器人"会被压入栈中
 * - "向左移动的机器人"会触发碰撞检查
 * - 碰撞可能连续发生（当前机器人击败多个栈中机器人）
 * - 最终结果是按原始编号顺序，而非位置顺序
 */

#include <gtest/gtest.h>

#include <algorithm>
#include <numeric>
#include <stack>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        int n = positions.size();
        // 创建索引数组 [0, 1, ..., n-1]
        vector<int> idx(n);
        // iota: 用递增序列填充数组，idx 变为 [0, 1, 2, ..., n-1]
        iota(idx.begin(), idx.end(), 0);
        // 按位置排序索引，得到从左到右的机器人顺序
        sort(idx.begin(), idx.end(), [&](int a, int b) {
            return positions[a] < positions[b];
        });

        // 栈用于存储向右移动的机器人索引
        // 栈中机器人按位置从左到右排列（栈底到栈顶）
        vector<int> stk;

        // 按位置顺序遍历所有机器人
        for (int i : idx) {
            if (directions[i] == 'R') {
                // 向右移动的机器人：直接入栈，等待后续向左移动的机器人来碰撞
                stk.push_back(i);
                continue;
            }

            // 向左移动的机器人：需要与栈中向右移动的机器人碰撞
            // 碰撞条件：栈不为空 且 当前机器人仍然存活(health > 0)
            while (!stk.empty() && healths[i] > 0) {
                int j = stk.back();  // 栈顶机器人（最靠近当前机器人的向右移动机器人）

                if (healths[j] > healths[i]) {
                    // 情况1：栈顶机器人更强
                    // 当前机器人被摧毁
                    healths[i] = 0;
                    // 栈顶机器人健康值减1，但继续留在栈中
                    healths[j]--;
                } else if (healths[j] < healths[i]) {
                    // 情况2：当前机器人更强
                    // 栈顶机器人被摧毁（出栈）
                    stk.pop_back();
                    healths[j] = 0;
                    // 当前机器人健康值减1，但继续存活，可能与新的栈顶碰撞
                    healths[i]--;
                } else {
                    // 情况3：两者健康值相等
                    // 两者都被摧毁
                    healths[i] = 0;
                    healths[j] = 0;
                    stk.pop_back();  // 栈顶出栈
                    break;  // 当前机器人也被移除，停止碰撞
                }
            }
        }

        // 收集结果：所有健康值大于0的机器人
        // 由于我们遍历原始 healths 数组，结果自然按原始输入顺序排列
        vector<int> ans;
        for (int h : healths) {
            if (h > 0) {
                ans.push_back(h);
            }
        }
        return ans;
    }
};

TEST(Daily, 2751) {
    Solution s;

    // 示例2：存在碰撞的情况
    vector<int> positions{3, 5, 2, 6};
    vector<int> healths{10, 10, 15, 12};
    string directions{"RLRL"};

    auto ret = s.survivedRobotsHealths(positions, healths, directions);
    vector<int> expected{14};
    EXPECT_EQ(expected, ret);
}
