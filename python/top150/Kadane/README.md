# Kadane 算法（最大子数组和）

Kadane 算法由卡内基梅隆大学的 Joseph Kadane 于 1984 年提出，用于在线性时间内解决**最大子数组和问题**（Maximum Subarray Problem）：给定一个整数数组，找出和最大的连续子数组。它把朴素的 O(n²) / O(n³) 枚举优化到 **O(n) 时间、O(1) 空间**，是动态规划"局部最优 → 全局最优"思想的经典范例。

## 问题描述

> 给定一个整数数组 `nums`，找出其中**和最大**的**连续**子数组（至少包含一个元素），返回其最大和。
>
> —— LeetCode 53. 最大子数组和（面试经典 150 题）

例如 `nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]`，和最大的连续子数组是 `[4, -1, 2, 1]`，最大和为 `6`。

注意：子数组必须**连续**（不能跳过中间元素），且**至少包含一个元素**——全负数组的答案就是最大的那个负数，而不是 0。

## 核心思想

关键观察：**一个"拖后腿"的前缀，不如不要。**

定义 `dp[i]` 为**以第 i 个元素结尾**的最大子数组和，则有两种选择：

- 把 `nums[i]` 接在前一个子数组后面：和为 `dp[i-1] + nums[i]`；
- 另起炉灶，从 `nums[i]` 单独开始：和为 `nums[i]`。

于是得到状态转移方程：

```
dp[i] = max(nums[i], dp[i-1] + nums[i])
```

直观解释：如果 `dp[i-1] < 0`（前面累计的是负贡献），带上它只会让和变小，不如从当前元素重新开始。全局答案则是所有 `dp[i]` 的最大值：

```
ans = max(dp[0], dp[1], ..., dp[n-1])
```

由于 `dp[i]` 只依赖 `dp[i-1]`，可以用一个变量滚动更新，无需数组，空间降为 O(1)。

## 手动推演示例

以 `nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]` 为例（`cur` 即 `dp[i]`，`ans` 为全局最大）：

| i | nums[i] | cur = max(nums[i], cur + nums[i]) | ans |
|---|---------|-----------------------------------|-----|
| 0 | -2      | -2（初始化）                       | -2  |
| 1 | 1       | max(1, -2+1) = **1**（另起炉灶）    | 1   |
| 2 | -3      | max(-3, 1-3) = -2                 | 1   |
| 3 | 4       | max(4, -2+4) = **4**（另起炉灶）    | 4   |
| 4 | -1      | max(-1, 4-1) = 3                  | 4   |
| 5 | 2       | max(2, 3+2) = 5                   | 5   |
| 6 | 1       | max(1, 5+1) = 6                   | **6** |
| 7 | -5      | max(-5, 6-5) = 1                  | 6   |
| 8 | 4       | max(4, 1+4) = 5                   | 6   |

最终答案 `6`，对应子数组 `[4, -1, 2, 1]`（下标 3~6）。

## 实现

### 标准版（Python）

函数签名保持 LeetCode 官方 camelCase，便于直接提交：

```python
class Solution:
    def maxSubArray(self, nums: list[int]) -> int:
        # cur: 以当前元素结尾的最大子数组和（滚动变量）
        # ans: 全局最大子数组和
        cur = ans = nums[0]
        for x in nums[1:]:
            # 前缀贡献为负时另起炉灶，否则接在后面
            cur = max(x, cur + x)
            ans = max(ans, cur)
        return ans
```

C++ 版本见本仓库 [cplusplus/questions/53.cpp](../../../cplusplus/questions/53.cpp)。

### 扩展：返回子数组本身

记录最优区间的结束下标，再倒推起点：

```python
def max_subarray_with_index(nums: list[int]) -> tuple[int, int, int]:
    """返回 (最大和, 起始下标, 结束下标)。"""
    cur = ans = nums[0]
    start = best_start = best_end = 0
    for i in range(1, len(nums)):
        if nums[i] > cur + nums[i]:   # 另起炉灶
            cur, start = nums[i], i
        else:                          # 接在后面
            cur += nums[i]
        if cur > ans:
            ans, best_start, best_end = cur, start, i
    return ans, best_start, best_end
```

## 复杂度分析

| 指标 | 复杂度 | 说明 |
|------|--------|------|
| 时间 | O(n) | 只遍历数组一次 |
| 空间 | O(1) | 仅用 cur / ans 两个滚动变量 |

## 正确性简证

对 `dp[i]`（以 i 结尾的最大子数组和）做归纳：

- 基础：`dp[0] = nums[0]`，显然成立。
- 归纳：以 i 结尾的最优子数组，要么只含 `nums[i]`，要么是"以 i-1 结尾的某个子数组 + `nums[i]`"。后者要最大，前缀必须是最大的 `dp[i-1]`。故 `dp[i] = max(nums[i], dp[i-1] + nums[i])`。

而全局最优子数组必然以某个下标结尾，所以 `ans = max(dp[i])` 覆盖了所有情况。

## 常见变体与相关题目

| 题目 | 变体要点 |
|------|----------|
| [53. 最大子数组和](https://leetcode.cn/problems/maximum-subarray/) | 标准模板题 |
| [918. 环形子数组的最大和](https://leetcode.cn/problems/maximum-sum-circular-subarray/) | 分"不跨环"（标准 Kadane）与"跨环"（总和 − 最小子数组和）两类取较大值；注意全负数时的边界 |
| [152. 乘积最大子数组](https://leetcode.cn/problems/maximum-product-subarray/) | 负数会翻转大小，需同时维护以 i 结尾的**最大积与最小积**两个状态 |
| [1567. 乘积为正数的最长子数组长度](https://leetcode.cn/problems/maximum-length-of-subarray-with-positive-product/) | 按正负分段讨论，维护正/负乘积子数组的长度 |
| [1186. 删除一次得到子数组最大和](https://leetcode.cn/problems/maximum-subarray-sum-with-one-deletion/) | 正反两次扫描，`left[i] + right[i+1]` 拼出"删 i"后的最优值 |
| [978. 最长湍流子数组](https://leetcode.cn/problems/longest-turbulent-subarray/) | 把"和"换成"比较符号交替的长度"，思想同构 |
| [363. 矩形区域不超过 K 的最大数值和](https://leetcode.cn/problems/max-sum-of-rectangle-no-larger-than-k/) | 上下边界枚举 + 列前缀和压缩，退化为一维子数组问题后配合 Kadane / 有序集合 |

几个高频易错点：

1. **初始化用 `nums[0]` 而不是 0**——全负数组时答案应为最大负数，用 0 初始化会错误地返回空子数组的和。
2. **先更新 `cur` 再更新 `ans`**，顺序不能颠倒。
3. 滚动数组写法中 `cur` 和 `ans` 可以合并成一行 `cur = max(x, cur + x); ans = max(ans, cur)`，但不要在更新 `ans` 之前误用旧的 `cur`。

## 参考资料

- Jon Bentley, *Programming Pearls*（编程珠玑）第 2 版第 8 章 "Algorithm Design Techniques"——最大子数组问题的原始出处与 Kadane 算法的推导过程
- 本仓库参考实现：[53.cpp](../../../cplusplus/questions/53.cpp)
