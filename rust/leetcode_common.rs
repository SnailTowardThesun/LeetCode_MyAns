//! 通用数据结构与构造工具（与 cplusplus/leetcode_common.h、python/leetcode_common 对应）。
//! 题解统一 `use crate::leetcode_common::...` 引入，禁止在题解文件中重复定义。

use std::cell::RefCell;
use std::rc::Rc;

/// 链表节点（与 LeetCode 官方定义一致）
#[derive(Debug, PartialEq, Eq)]
pub struct ListNode {
    pub val: i32,
    pub next: Option<Box<ListNode>>,
}

impl ListNode {
    #[inline]
    pub fn new(val: i32) -> Self {
        ListNode { val, next: None }
    }
}

/// 二叉树节点（与 LeetCode 官方定义一致）
#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode {
    pub val: i32,
    pub left: Option<Rc<RefCell<TreeNode>>>,
    pub right: Option<Rc<RefCell<TreeNode>>>,
}

impl TreeNode {
    #[inline]
    pub fn new(val: i32) -> Self {
        TreeNode {
            val,
            left: None,
            right: None,
        }
    }
}

/// 根据值数组构造链表，返回头节点：[1, 2, 3] -> 1 -> 2 -> 3，空数组返回 None
pub fn make_list(vals: &[i32]) -> Option<Box<ListNode>> {
    let mut head: Option<Box<ListNode>> = None;
    for &v in vals.iter().rev() {
        let mut node = ListNode::new(v);
        node.next = head;
        head = Some(Box::new(node));
    }
    head
}

/// 把链表展开成值数组，便于断言与打印
pub fn to_vals(mut head: Option<Box<ListNode>>) -> Vec<i32> {
    let mut vals = Vec::new();
    while let Some(node) = head {
        vals.push(node.val);
        head = node.next;
    }
    vals
}
