/**
 * No.965 单值二叉树
 *
 * @题目描述
 * 判断二叉树所有节点值是否相同。
 *
 * @示例
 * 输入：[1,1,1,1,1]
 * 输出：true
 *
 * @解题思路
 * 递归把所有值收进 HashSet，集合大小不超过 1 即单值。
 */
use std::cell::RefCell;
use std::collections::HashSet;
use std::rc::Rc;

use crate::leetcode_common::TreeNode;

fn is_unival_tree(root: Option<Rc<RefCell<TreeNode>>>) -> bool {
    let mut buf: HashSet<i32> = HashSet::new();

    fn helper(root: &Option<Rc<RefCell<TreeNode>>>, buf: &mut HashSet<i32>) {
        if let Some(node) = root {
            buf.insert(node.borrow().val);
            helper(&node.borrow().left, buf);
            helper(&node.borrow().right, buf);
        }
    }
    helper(&root, &mut buf);

    return buf.len() == 1 || buf.len() == 0;
}

#[test]
fn test_is_unival_tree() {
    let root = Rc::new(RefCell::new(TreeNode::new(5)));
    root.borrow_mut().right = Some(Rc::new(RefCell::new(TreeNode::new(4))));
    root.borrow_mut().left = Some(Rc::new(RefCell::new(TreeNode::new(3))));

    let ret = is_unival_tree(Some(root));
    print!("{}", ret)
}
