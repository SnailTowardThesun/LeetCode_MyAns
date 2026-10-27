/**
 * No.94 二叉树的中序遍历
 *
 * @题目描述
 * 返回二叉树的中序遍历序列。
 *
 * @示例
 * 输入：[1,null,2,3]
 * 输出：[1,3,2]
 *
 * @解题思路
 * 递归 helper：左子树 → 根 → 右子树。
 */
use crate::leetcode_common::TreeNode;

use std::cell::RefCell;
use std::rc::Rc;

fn inorder_traversal(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<i32> {
    fn do_inorder(r: &mut Option<Rc<RefCell<TreeNode>>>, a: &mut Vec<i32>) {
        if let Some(n) = r {
            let mut n = n.borrow_mut();
            do_inorder(&mut n.left, a);
            a.push(n.val);
            do_inorder(&mut n.right, a);
        }
    }
    let mut root = root;
    let mut res = vec![];
    do_inorder(&mut root, &mut res);
    return res;
}

#[test]
fn test_inorder_traversal() {
    let root = None;
    inorder_traversal(root);
}
