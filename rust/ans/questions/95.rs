/**
 * No.95 不同的二叉搜索树 II
 *
 * @题目描述
 * 返回 1..n 能构成的所有结构不同的二叉搜索树。
 *
 * @示例
 * 输入：n = 3
 * 输出：5 棵树的列表
 *
 * @解题思路
 * 分治：枚举根 i，左子树集合 helper(l, i-1) 与右子树集合 helper(i+1, r) 做笛卡尔积组合。
 */
use crate::leetcode_common::TreeNode;

use std::cell::RefCell;
use std::rc::Rc;

fn get_all_unique_binary_search_trees(n: i32) -> Vec<Option<Rc<RefCell<TreeNode>>>> {
    let ret;

    fn helper(l: i32, r: i32) -> Vec<Option<Rc<RefCell<TreeNode>>>> {
        if l > r {
            return vec![None];
        }

        let mut res = vec![];
        for i in l..r + 1 {
            let l_nodes = helper(l, i - 1);
            let r_nodes = helper(i + 1, r);
            for ln in l_nodes.iter() {
                for rn in r_nodes.iter() {
                    let node = Some(Rc::new(RefCell::new(TreeNode {
                        val: i,
                        left: ln.clone(),
                        right: rn.clone(),
                    })));
                    res.push(node);
                }
            }
        }

        return res;
    }

    ret = helper(1, n);

    return ret;
}

#[test]
fn test_get_al_l_unique_binary_search_trees() {
    get_all_unique_binary_search_trees(5);
}
