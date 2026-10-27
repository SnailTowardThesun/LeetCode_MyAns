/**
 * No.113 路径总和 II
 *
 * @题目描述
 * 找出所有从根到叶、节点和等于 targetSum 的路径。
 *
 * @示例
 * 输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
 * 输出：[[5,4,11,2],[5,8,4,5]]
 *
 * @解题思路
 * DFS 回溯：buf 记录当前路径，叶节点时判断剩余值是否恰好等于节点值，返回前 pop。
 */
use crate::leetcode_common::TreeNode;

use std::cell::RefCell;
use std::rc::Rc;

fn path_sum_ii(root: Option<Rc<RefCell<TreeNode>>>, target_sum: i32) -> Vec<Vec<i32>> {
    let mut ret = vec![];

    fn helper(
        root: &Option<Rc<RefCell<TreeNode>>>,
        target: i32,
        buf: &mut Vec<i32>,
        ret: &mut Vec<Vec<i32>>,
    ) {
        if let Some(node) = root {
            let val = node.borrow().val;
            let l = &node.borrow().left;
            let r = &node.borrow().right;
            buf.push(val);
            if target == val && l.is_none() && r.is_none() {
                ret.push(buf.clone());
            }
            helper(l, target - val, buf, ret);
            helper(r, target - val, buf, ret);
            buf.pop();
        }
    }

    helper(&root, target_sum, &mut vec![], &mut ret);
    return ret;
}

#[test]
fn test_path_sum_ii() {
    let root = Rc::new(RefCell::new(TreeNode::new(5)));
    let ret = path_sum_ii(Some(root), 5);
    for i in ret {
        for j in i {
            print!("{}\t", j);
        }

        print!("\n");
    }
}
