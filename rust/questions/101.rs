/**
 * No.101 对称二叉树
 *
 * @题目描述
 * 判断二叉树是否轴对称。
 *
 * @示例
 * 输入：[1,2,2,3,4,4,3]
 * 输出：true
 *
 * @解题思路
 * 递归镜像比较：左左 vs 右右、左右 vs 右左，值相等且子树对称。
 */
use crate::leetcode_common::TreeNode;

use std::cell::RefCell;
use std::rc::Rc;

fn symmetric_tree(root: Option<Rc<RefCell<TreeNode>>>) -> bool {
    type Rn = Rc<RefCell<TreeNode>>;

    fn f(p: Option<&Rn>, q: Option<&Rn>) -> bool {
        match (p, q) {
            (None, None) => true,
            (Some(p), Some(q)) => {
                let p = p.borrow();
                let q = q.borrow();
                p.val == q.val
                    && f(p.left.as_ref(), q.right.as_ref())
                    && f(p.right.as_ref(), q.left.as_ref())
            }
            _ => false,
        }
    }

    match root {
        None => true,
        Some(n) => {
            let n = n.borrow();
            f(n.left.as_ref(), n.right.as_ref())
        }
    }
}

#[test]
fn test_symmetric_tree() {
    let root = Some(Rc::new(RefCell::new(TreeNode::new(5))));
    symmetric_tree(root);
}
