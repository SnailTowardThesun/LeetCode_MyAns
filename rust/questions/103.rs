/**
 * No.103 锯齿形层序遍历
 *
 * @题目描述
 * 之字形（先左后右交替）逐层遍历二叉树。
 *
 * @示例
 * 输入：[3,9,20,null,null,15,7]
 * 输出：[[3],[20,9],[15,7]]
 *
 * @解题思路
 * 队列 BFS 逐层弹出；奇数层把该层结果局部反转。
 */
use crate::leetcode_common::TreeNode;

use std::cell::RefCell;
use std::collections::VecDeque;
use std::rc::Rc;

fn zigzag_level_order(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<Vec<i32>> {
    let mut ret = vec![];
    let mut q = VecDeque::new();

    if root != None {
        q.push_back(root);
    }

    let mut level = 0;
    while !q.is_empty() {
        let mut tmp = vec![];
        let size = q.len();
        for _ in 0..size {
            if let Some(node) = q.pop_front().unwrap() {
                tmp.push(node.borrow().val);

                if node.borrow().left != None {
                    q.push_back(node.borrow_mut().left.take());
                }

                if node.borrow().right != None {
                    q.push_back(node.borrow_mut().right.take());
                }
            }
        }

        if level % 2 == 1 {
            tmp.reverse();
        }

        level += 1;
        ret.push(tmp);
    }

    return ret;
}

#[test]
fn test_zigzag_level_order() {
    let example = Some(Rc::new(RefCell::new(TreeNode::new(5))));
    let ret = zigzag_level_order(example);
    for i in 0..ret.len() {
        for j in 0..ret[i].len() {
            print!("{}\t", ret[i][j]);
        }
    }
}
