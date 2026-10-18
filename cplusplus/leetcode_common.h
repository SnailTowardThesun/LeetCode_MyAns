// LeetCode 题解通用数据结构定义
// 需要链表/二叉树的题解统一 #include 本头文件，禁止在 .cpp 中重复定义，
// 唯一定义保证跨编译单元满足 ODR（CMake 将全部 .cpp 链接进同一个 tests 可执行文件）。
#pragma once

// 链表节点（与 LeetCode 官方定义一致）
struct ListNode {
    int val;
    ListNode* next;

    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// 二叉树节点（与 LeetCode 官方定义一致）
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
