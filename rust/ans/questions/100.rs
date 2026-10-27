/**
 * No.100 相同的树
 *
 * @题目描述
 * 判断两棵二叉树结构与节点值完全相同。
 *
 * @示例
 * 输入：p = [1,2,3], q = [1,2,3]
 * 输出：true
 *
 * @解题思路
 * 同步递归比较：两空相等；一空不等；值相等且左右子树分别相同。
 */
use crate::leetcode_common::TreeNode;

use std::cell::RefCell;
use std::rc::Rc;

fn same_tree(p: Option<Rc<RefCell<TreeNode>>>, q: Option<Rc<RefCell<TreeNode>>>) -> bool {
    match (p, q) {
        (None, None) => true,
        (Some(p), Some(q)) => {
            let p = p.borrow();
            let q = q.borrow();
            p.val == q.val
                && same_tree(p.left.clone(), q.left.clone())
                && same_tree(p.right.clone(), q.right.clone())
        }
        _ => false,
    }
}

#[test]
fn test_same_tree() {
    let p = Some(Rc::new(RefCell::new(TreeNode::new(5))));
    let q = Some(Rc::new(RefCell::new(TreeNode::new(5))));
    assert_eq!(true, same_tree(p, q));
}
