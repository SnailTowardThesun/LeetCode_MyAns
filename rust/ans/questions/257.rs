/**
 * No.257 二叉树的所有路径
 *
 * @题目描述
 * 返回所有根到叶节点路径，形如 "1->2->3"。
 *
 * @示例
 * 输入：[1,2,3,null,5]
 * 输出：["1->2->5","1->3"]
 *
 * @解题思路
 * 递归收集：叶节点返回单值路径，否则把根值追加到子树返回的每条路径前，最后 join("->")。
 */
use crate::leetcode_common::TreeNode;

use std::cell::RefCell;
use std::rc::Rc;

fn binary_tree_paths(root: Option<Rc<RefCell<TreeNode>>>) -> Vec<String> {
    fn helper(root: &Option<Rc<RefCell<TreeNode>>>) -> Vec<Vec<String>> {
        let mut result: Vec<Vec<String>> = vec![];
        if let Some(node) = root {
            let (left, right) = (&node.borrow().left, &node.borrow().right);
            if left.is_none() && right.is_none() {
                result.push(vec![node.borrow().val.to_string()]);
            } else {
                [left, right].iter().for_each(|branch| {
                    result.extend(helper(*branch).into_iter().map(|mut p| {
                        p.push(node.borrow().val.to_string());
                        p
                    }))
                });
            }
        }
        return result;
    }

    return helper(&root)
        .into_iter()
        .map(|path| path.into_iter().rev().collect::<Vec<String>>().join("->"))
        .collect();
}

#[test]
fn test_binary_tree_paths() {
    let root = Rc::new(RefCell::new(TreeNode::new(1)));
    binary_tree_paths(Some(root));
}
