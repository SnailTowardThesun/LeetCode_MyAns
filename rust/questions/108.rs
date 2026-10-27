/**
 * No.108 将有序数组转换为二叉搜索树
 *
 * @题目描述
 * 把升序数组转换为一棵高度平衡的 BST。
 *
 * @示例
 * 输入：[-10,-3,0,5,9]
 * 输出：[0,-3,9,-10,null,5]
 *
 * @解题思路
 * 取中点为根，左半段递归构建左子树、右半段递归构建右子树。
 */
use crate::leetcode_common::TreeNode;

use std::cell::RefCell;
use std::rc::Rc;

fn convert_sorted_array_into_bst(nums: Vec<i32>) -> Option<Rc<RefCell<TreeNode>>> {
    if nums.is_empty() {
        return None;
    }

    let mid = nums.len() / 2;
    let root = Rc::new(RefCell::new(TreeNode::new(nums[mid])));
    root.borrow_mut().left = convert_sorted_array_into_bst(nums[..mid].to_vec());
    root.borrow_mut().right = convert_sorted_array_into_bst(nums[mid + 1..].to_vec());

    return Some(root);
}

#[test]
fn test_convert_sorted_array_into_bst() {
    let nums = vec![-10, -3, 0, 5, 9];
    let ret = convert_sorted_array_into_bst(nums);
    print!("{}", ret.is_none());
}
