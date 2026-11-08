"""
@file top150_77.py
@brief LeetCode 77. Combinations（组合）——top150 回溯分类

@题目描述
    给定两个整数 n 和 k，返回范围 [1, n] 中所有可能的 k 个数的组合。

    可以按任何顺序返回答案。

    提示：
    - 1 <= n <= 20
    - 1 <= k <= n

@示例
    示例 1：
    输入：n = 4, k = 2
    输出：[[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
    解释：[1,n] 中所有可能的 2 个数的组合，共 C(4,2) = 6 个。

    示例 2：
    输入：n = 1, k = 1
    输出：[[1]]

@解题思路
    组合问题不区分顺序（{1,2} 与 {2,1} 是同一个组合），关键是让路径严格
    递增以消除重复——本实现用「固定首元素 + 递归后缀」的自顶向下枚举
    （与 start 指针回溯等价：每个组合由它最小的元素定位）：

    1. dfs(arr, k) 返回从 arr 中选 k 个数的全部组合；
    2. 边界三连：k == 1 时每个元素自成一组；k > len(arr) 时数不够，
       无解返回 []；k == len(arr) 时只能全选，唯一组合（剪枝）；
    3. 一般情况：枚举首个元素 s = arr[i]，与 arr[i+1:] 中选 k-1 个的
       所有组合拼接 [s, *c]——首元素固定后组合天然不重；由于 arr 有序，
       循环走到「剩余长度恰好等于 k」时后续 i 只剩全选一种，由上面的
       k == len(arr) 分支兜住；
    4. 结果共 C(n, k) 个组合。

    时间复杂度 O(C(n,k) x k)（每个组合构造 O(k)）；空间复杂度 O(k)
    （递归深度，不计输出）。

来源：LeetCode
链接：https://leetcode.cn/problems/combinations/description/
"""


class Solution:
    def combine(self, n: int, k: int) -> list[list[int]]:
        def dfs(arr, k):
            if k == 1:
                return [[i] for i in arr]
            if k > len(arr):
                return []
            if k == len(arr):
                return [arr]

            ret = []
            for i in range(len(arr)):
                s = arr[i]
                combs = dfs(arr[i + 1 :], k - 1)
                for c in combs:
                    ret.append([s, *c])

            return ret

        arr = list(range(n + 1))[1:]
        return dfs(arr, k)


def test_solution() -> None:
    solution = Solution()

    # ---- 官方示例 1：n=4, k=2，C(4,2)=6 个组合 ----
    assert sorted(solution.combine(4, 2)) == [[1, 2], [1, 3], [1, 4], [2, 3], [2, 4], [3, 4]]

    # ---- 官方示例 2：n=1, k=1，唯一组合 ----
    assert sorted(solution.combine(1, 1)) == [[1]]

    # ---- n=5, k=3：C(5,3)=10 个，抽查首尾边界组合 ----
    result_5_3 = sorted(solution.combine(5, 3))
    assert len(result_5_3) == 10
    assert [1, 2, 5] in result_5_3  # 跨度最大：含最小起点与最大终点
    assert [3, 4, 5] in result_5_3  # 最晚起点的组合

    # ---- k=n：只能选满 [1,n]，唯一组合 ----
    assert sorted(solution.combine(4, 4)) == [[1, 2, 3, 4]]

    # ---- 上界规模 n=20, k=1：20 个单元素组合 ----
    result_20_1 = sorted(solution.combine(20, 1))
    assert len(result_20_1) == 20
    assert result_20_1 == [[i] for i in range(1, 21)]


if __name__ == "__main__":
    test_solution()
    print("✅ No.77 全部测试通过")
