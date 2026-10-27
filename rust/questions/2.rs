/**
 * No.2 两数相加
 *
 * @题目描述
 * 两个非空链表表示两个非负整数（数字逆序存储），返回相加结果链表。
 *
 * @示例
 * 输入：(2→4→3) + (5→6→4)
 * 输出：7→0→8（342 + 465 = 807）
 *
 * @解题思路
 * 同时遍历两条链表逐位相加并维护进位 carry，短链耗尽后补零继续，结尾进位非零则追加节点。
 */
use crate::leetcode_common::ListNode;

fn add_two_numbers(l1: Option<Box<ListNode>>, l2: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
    let mut ret = Some(Box::new(ListNode::new(0)));
    let (mut p1, mut p2, mut carry) = (l1, l2, 0);
    let mut pos = ret.as_mut();
    while p1.is_some() || p2.is_some() {
        let mut sum = carry;

        if let Some(v) = p1 {
            sum += v.val;
            p1 = v.next;
        }

        if let Some(v) = p2 {
            sum += v.val;
            p2 = v.next;
        }

        if sum >= 10 {
            carry = 1;
            sum = sum - 10;
        } else {
            carry = 0;
        }

        let v = pos.unwrap();
        v.next = Some(Box::new(ListNode::new(sum)));
        pos = v.next.as_mut();
    }

    if carry > 0 {
        let v = pos.unwrap();
        v.next = Some(Box::new(ListNode::new(1)));
    }

    return ret.unwrap().next;
}

#[test]
fn test_add_two_numbers() {
    assert_eq!(1, 1);

    let mut l1 = Box::new(ListNode::new(2));
    l1.next = Some(Box::new(ListNode::new(4)));
    l1.next.as_mut().unwrap().next = Some(Box::new(ListNode::new(7)));

    let mut l2 = Box::new(ListNode::new(5));
    l2.next = Some(Box::new(ListNode::new(6)));
    l2.next.as_mut().unwrap().next = Some(Box::new(ListNode::new(4)));

    let ret = add_two_numbers(Some(l1), Some(l2));

    let expected_ret = [7, 0, 2, 1];
    let mut pos = ret;
    for i in 0..expected_ret.len() {
        assert_eq!(pos.is_some(), true);
        if !pos.is_some() {
            break;
        }

        if let Some(v) = pos {
            assert_eq!(v.val, expected_ret[i]);
            pos = v.next;
        }
    }
}
