"""
@file top150_108.py
@brief LeetCode 108. 将有序数组转换为二叉搜索树

@题目描述
    给你一个整数数组 nums，其中元素已经按 升序 排列，请将其转换为一棵
    高度平衡 二叉搜索树。
    高度平衡 二叉树是一棵满足「每个节点的左右两个子树的高度差的绝对值不超过 1」的二叉树。

@示例
    示例 1：
    输入：nums = [-10,-3,0,5,9]
    输出：[0,-3,9,-10,null,5]
    解释：[0,-10,9,null,-3,null,5] 也同样是正确的答案。

    示例 2：
    输入：nums = [1,3]
    输出：[3,1] 或 [1,3]
    解释：[1,3] 和 [3,1] 都是高度平衡二叉搜索树。

@解题思路
    分治：有序数组取中间元素作根，左半部分递归建左子树，右半部分递归建右子树。
    1. 切片为空返回 None；
    2. mid = len(bnums) // 2（偶数长度取左中位数），bnums[mid] 作根；
    3. 左子树递归 bnums[:mid]，右子树递归 bnums[mid+1:]（必须跳过根，否则根会被重复建节点）；
    4. 中序遍历即原数组 ⇒ 是 BST；左右子树节点数差不超过 1 ⇒ 高度平衡。

    时间复杂度 O(n)，空间复杂度 O(n)（递归路径上切片拷贝的峰值；改传下标区间可降到 O(log n) 递归栈）

来源：LeetCode
链接：https://leetcode.cn/problems/convert-sorted-array-to-binary-search-tree/description/
"""

from leetcode_common import TreeNode, tree_to_level


class Solution:
    def sortedArrayToBST(self, nums: list[int]) -> TreeNode | None:
        def build(bnums: list[int]) -> TreeNode | None:
            if not bnums:
                return None
            mid = len(bnums) // 2
            root = TreeNode(bnums[mid])
            root.left = build(bnums[:mid])
            root.right = build(bnums[mid + 1 :])
            return root

        return build(nums)


def _is_balanced_bst(root: TreeNode | None, nums: list[int]) -> bool:
    """性质校验：中序遍历等于原数组（是 BST），且任意节点左右子树高度差 <= 1（平衡）。"""

    def height(node: TreeNode | None) -> int:
        # 返回树高；-1 表示子树已不平衡，向上短路
        if node is None:
            return 0
        left_h = height(node.left)
        right_h = height(node.right)
        if left_h == -1 or right_h == -1 or abs(left_h - right_h) > 1:
            return -1
        return max(left_h, right_h) + 1

    inorder: list[int] = []
    stack: list[TreeNode] = []
    node = root
    while stack or node:
        while node:
            stack.append(node)
            node = node.left
        node = stack.pop()
        inorder.append(node.val)
        node = node.right
    return inorder == nums and height(root) != -1


def test_solution() -> None:
    solution = Solution()

    # 边界：空数组返回 None；单元素只有根节点
    assert solution.sortedArrayToBST([]) is None
    assert tree_to_level(solution.sortedArrayToBST([1])) == [1]

    # 本题答案不唯一：官方示例 1 的 [0,-3,9,-10,null,5]、示例 2 的 [1,3] 和 [3,1] 都是合法输出，
    # 因此不做精确层序断言，改为校验性质——中序遍历 = 原数组（BST）且高度平衡，
    # 无论用哪种构造方式实现，只要正确即可通过
    cases: list[list[int]] = [
        [-10, -3, 0, 5, 9],  # 官方示例 1
        [1, 3],  # 官方示例 2
        [i * 7 - 10_000 for i in range(101)],  # 长数组，含负数（对齐官方数据范围）
    ] + [list(range(n)) for n in range(2, 33)]  # 奇偶长度逐规模对拍
    for nums in cases:
        assert _is_balanced_bst(solution.sortedArrayToBST(nums), nums), f"nums={nums}"


if __name__ == "__main__":
    test_solution()
    print("✅ 108 全部测试通过")
