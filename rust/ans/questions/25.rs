// Author: hankun1991@outlook.com

/**
 * No.25 K 个一组翻转链表 (2026-10-05)
 *
 * @题目描述
 * 给你链表的头节点 head，每 k 个节点一组进行翻转，请你返回修改后的链表。
 * k 是一个正整数，它的值小于或等于链表的长度。
 * 如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。
 * 进阶：你可以设计一个只用 O(1) 额外内存空间的算法解决此问题吗？
 *
 * @示例
 * 示例 1：
 * 输入：head = [1,2,3,4,5], k = 2
 * 输出：[2,1,4,3,5]
 *
 * 示例 2：
 * 输入：head = [1,2,3,4,5], k = 3
 * 输出：[3,2,1,4,5]
 *
 * @解题思路
 * 数组化 + 分组反转（与 C++ 版一致，Rust 中因所有权语义改为收集节点值）：
 * 1. 第一次遍历把所有节点值收集到数组 vals 中；
 * 2. 从下标 0 开始每隔 k 个一组调用 reverse 反转值数组切片，
 *    只翻转完整组：i + k <= n，末尾不足 k 的部分保持原序；
 * 3. 按反转后的顺序重建链表，返回新头节点。
 *
 * @复杂度分析
 * - 时间复杂度: O(n)，收集、反转、重建各一遍
 * - 空间复杂度: O(n)，用于存储节点值数组
 */

struct ListNode {
    val: i32,
    next: Option<Box<ListNode>>,
}

impl ListNode {
    #[inline]
    fn new(val: i32) -> Self {
        ListNode { val, next: None }
    }
}

fn reverse_k_group(head: Option<Box<ListNode>>, k: i32) -> Option<Box<ListNode>> {
    // 收集所有节点值
    let mut vals: Vec<i32> = Vec::new();
    let mut cur = head;
    while let Some(node) = cur {
        vals.push(node.val);
        cur = node.next;
    }

    let n = vals.len();
    if n == 0 {
        return None;
    }

    // 只翻转完整的组，末尾不足 k 的部分保持原顺序
    let k = k as usize;
    let mut i = 0;
    while i + k <= n {
        vals[i..i + k].reverse();
        i += k;
    }

    // 按新顺序重建链表：从尾向头逐个前插
    let mut ret: Option<Box<ListNode>> = None;
    for &v in vals.iter().rev() {
        let mut node = ListNode::new(v);
        node.next = ret;
        ret = Some(Box::new(node));
    }

    return ret;
}

/// 根据值数组构造链表，返回头节点
fn make_list(vals: &[i32]) -> Option<Box<ListNode>> {
    let mut head: Option<Box<ListNode>> = None;
    for &v in vals.iter().rev() {
        let mut node = ListNode::new(v);
        node.next = head;
        head = Some(Box::new(node));
    }
    head
}

/// 把链表展开成值数组，便于断言
fn to_vals(mut head: Option<Box<ListNode>>) -> Vec<i32> {
    let mut vals = Vec::new();
    while let Some(node) = head {
        vals.push(node.val);
        head = node.next;
    }
    vals
}

#[test]
fn test_reverse_k_group() {
    // k=3，长度 5：前 3 个翻转，末尾 2 个保持原样
    let ret = reverse_k_group(make_list(&[1, 2, 3, 4, 5]), 3);
    assert_eq!(to_vals(ret), vec![3, 2, 1, 4, 5]);

    // k=1：等价于不翻转
    let ret = reverse_k_group(make_list(&[1, 2, 3]), 1);
    assert_eq!(to_vals(ret), vec![1, 2, 3]);

    // 长度恰为 k 的倍数：全部翻转
    let ret = reverse_k_group(make_list(&[1, 2, 3, 4]), 2);
    assert_eq!(to_vals(ret), vec![2, 1, 4, 3]);

    // 边界：空链表
    let ret = reverse_k_group(None, 3);
    assert_eq!(to_vals(ret), Vec::<i32>::new());
}
