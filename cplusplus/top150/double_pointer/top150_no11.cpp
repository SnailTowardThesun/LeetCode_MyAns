//
// @题目描述: 给你 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai)。
//           画 n 条垂直线，使得两条线 i 和 j 生成的容器可以容纳最多的水。
//           容器能容纳的水量等于两条线之间的最短高度乘以它们之间的宽度。
//           请找出能容纳最多水的两条线，返回最大容量。
//
// @示例: 输入: height = [1,8,6,2,5,4,8,3,7]
//        输出: 49
//        解释: 8和7之间的距离是7，高度由较短的8决定，所以面积为min(8,7)*7=49
//
// @解题思路: 使用双指针，从数组两端向中间移动。
//            面积由较短的那条边决定，所以每次移动较短的边，才有可能找到更大的面积。
//            如果移动较长的边，面积只会变小（因为高度由最短边决定，而距离在减小）。
//            时间复杂度: O(n)，空间复杂度: O(1)
//
// Created by hankun on 5/31/26.
//

#include <gtest/gtest.h>
using namespace std;

class Solution {
public:
    int maxArea(vector<int> &height) {
        int maxArea = 0;
        int i = 0, j = height.size() - 1;

        while (i < j) {
            int area = min(height[i], height[j]) * (j - i);
            maxArea = max(maxArea, area);
            if (height[i] < height[j]) {
                i++;
            } else {
                j--;
            }
        }

        return maxArea;
    }
};

TEST(top150, 11) {
    Solution s;
    vector<int> arr{1, 8, 6, 2, 5, 4, 8, 3, 7};
    auto ret = s.maxArea(arr);
    EXPECT_EQ(49, ret);
}