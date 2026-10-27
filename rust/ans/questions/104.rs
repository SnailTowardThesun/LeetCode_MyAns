/**
 * No.104 二叉树的最大深度
 *
 * @题目描述
 * 返回二叉树的最大深度。
 *
 * @示例
 * 输入：[3,9,20,null,null,15,7]
 * 输出：3
 *
 * @解题思路
 * 递归：max(左子树深度, 右子树深度) + 1。
 */
use crate::leetcode_common::TreeNode;

use std::cell::RefCell;
use std::rc::Rc;

fn max_depth(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
    match root {
        None => 0,
        Some(node) => {
            let left = max_depth(node.borrow_mut().left.take());
            let right = max_depth(node.borrow_mut().right.take());
            return if left >= right { left + 1 } else { right + 1 };
        }
    }
}

#[test]
fn test_max_depth() {
    let root = Some(Rc::new(RefCell::new(TreeNode::new(5))));
    let ret = max_depth(root);
    println!("{}", ret);
}
