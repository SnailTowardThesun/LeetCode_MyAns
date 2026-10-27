/**
 * No.538 把二叉搜索树转换为累加树
 *
 * @题目描述
 * 每个节点值加上所有比它大的节点值。
 *
 * @示例
 * 输入：[4,1,6]
 * 输出：[11,12,6]（示例语义）
 *
 * @解题思路
 * 反中序（右 → 根 → 左）递归，维护累计和 sum 并回写到每个节点。
 */
use crate::leetcode_common::TreeNode;

use std::cell::RefCell;
use std::rc::Rc;

fn convert_bst(root: Option<Rc<RefCell<TreeNode>>>) -> Option<Rc<RefCell<TreeNode>>> {
    fn helper(root: &Option<Rc<RefCell<TreeNode>>>, sum: &mut i32) {
        if let Some(node) = root {
            let mut n = node.borrow_mut();
            helper(&n.right, sum);
            n.val += *sum;
            *sum = n.val;
            helper(&n.left, sum);
        }
    }

    let mut sum: i32 = 0;
    helper(&root, &mut sum);

    root
}

#[test]
fn test_convert_bst() {
    convert_bst(None);
}
