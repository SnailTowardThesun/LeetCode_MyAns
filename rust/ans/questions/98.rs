/**
 * No.98 验证二叉搜索树
 *
 * @题目描述
 * 判断二叉树是否为合法 BST（中序严格递增）。
 *
 * @示例
 * 输入：[2,1,3]
 * 输出：true
 *
 * @解题思路
 * 递归传递 (min, max) 开区间边界，节点值必须严格落在区间内，左右子树分别收缩边界。
 */
use crate::leetcode_common::TreeNode;

use std::cell::RefCell;
use std::rc::Rc;

fn is_valid_bst(root: Option<Rc<RefCell<TreeNode>>>) -> bool {
    fn valid(node: Option<Rc<RefCell<TreeNode>>>, max: i64, min: i64) -> bool {
        if let Some(node) = node {
            if node.borrow().val as i64 <= min || node.borrow().val as i64 >= max {
                return false;
            }
            return valid(node.borrow().left.clone(), min, node.borrow().val as i64)
                && valid(node.borrow().right.clone(), node.borrow().val as i64, max);
        }
        true
    }
    valid(root, i64::MIN, i64::MAX)
}

#[test]
fn test_unique_binary_search_trees_ii() {
    is_valid_bst(None);
}
