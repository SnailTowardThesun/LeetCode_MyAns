/**
 * No.783 二叉搜索树节点最小距离
 *
 * @题目描述
 * BST 中任意两不同节点值的最小差值。
 *
 * @示例
 * 输入：[4,2,6]
 * 输出：2
 *
 * @解题思路
 * 中序收集为升序数组，取相邻两数之差的最小值。
 */
use crate::leetcode_common::TreeNode;

use std::cell::RefCell;
use std::rc::Rc;

fn min_diff_in_bst(root: Option<Rc<RefCell<TreeNode>>>) -> i32 {
    let mut buff = vec![];

    fn helper(root: &Option<Rc<RefCell<TreeNode>>>, buf: &mut Vec<i32>) {
        if let Some(node) = root {
            let val = node.borrow().val;
            let l = &node.borrow().left;
            let r = &node.borrow().right;
            helper(l, buf);
            buf.push(val);
            helper(r, buf);
        }
    }

    helper(&root, &mut buff);

    return buff.windows(2).map(|c| c[1] - c[0]).min().unwrap();
}

#[test]
fn test_min_diff_in_bst() {
    let root = Rc::new(RefCell::new(TreeNode {
        val: 4,
        left: Some(Rc::new(RefCell::new(TreeNode {
            val: 2,
            left: None,
            right: None,
        }))),
        right: Some(Rc::new(RefCell::new(TreeNode {
            val: 6,
            left: None,
            right: None,
        }))),
    }));

    min_diff_in_bst(Some(root));
}
