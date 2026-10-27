/**
 * No.61 旋转链表
 *
 * @题目描述
 * 链表向右循环右移 k 个位置。
 *
 * @示例
 * 输入：[0,1,2], k = 4
 * 输出：[2,0,1]
 *
 * @解题思路
 * 先求长度 size，断开点在第 size-k%size 个节点之后：把尾部截下接到原头部。
 */
use crate::leetcode_common::ListNode;

fn rotate_right(head: Option<Box<ListNode>>, k: i32) -> Option<Box<ListNode>> {
    let mut head = match head {
        Some(a) => a,
        None => return None,
    };

    let mut size = 1;
    let mut pos = &head;

    while let Some(ref cur) = pos.next {
        size += 1;
        pos = cur;
    }

    println!("size: {}", size);

    let mut target = size - k % size;
    if target == size {
        return Some(head);
    }

    let mut cur = &mut head;
    while target > 1 {
        cur = cur.next.as_mut().unwrap();
        target -= 1;
    }

    let mut ret = std::mem::replace(&mut cur.next, None).unwrap();
    let mut cur = &mut ret;
    while let Some(ref mut next) = cur.next {
        cur = next;
    }
    cur.next = Some(head);

    return Some(ret);
}

#[test]
fn test_rotate_right() {
    let head = Box::new(ListNode::new(2));
    let ret = rotate_right(Some(head), 1);
    if let Some(node) = ret.as_ref() {
        println!("{}", node.val);
    }
}
