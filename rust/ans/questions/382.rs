/**
 * No.382 链表随机节点
 *
 * @题目描述
 * 链表中等概率随机返回一个节点值。
 *
 * @示例
 * 输入：[1,2,3]
 * 输出：1/2/3 各 1/3 概率
 *
 * @解题思路
 * EqualList 把链表展开成值数组，随机取下标（蓄水池抽样的数组化版本）。
 */
use crate::leetcode_common::ListNode;

struct EqualList {
    list: Vec<i32>,
}

use rand::Rng;

impl EqualList {
    fn new(head: Option<Box<ListNode>>) -> Self {
        let mut list = vec![];

        let mut pos = head.as_ref();

        while let Some(node) = pos {
            list.push(node.val);
            pos = node.next.as_ref();
        }

        return EqualList { list };
    }

    fn get_random(&self) -> i32 {
        let mut ra = rand::thread_rng();
        let target: usize = ra.gen_range(0..self.list.len());
        return self.list[target];
    }
}
#[test]
fn test_equal_list() {
    let head = Box::new(ListNode::new(2));
    let obj = EqualList::new(Some(head));
    let ret = obj.get_random();
    println!("{}", ret);
}
