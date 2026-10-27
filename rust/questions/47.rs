/**
 * No.47 全排列 II
 *
 * @题目描述
 * 返回含重复数字的数组的去重全排列。
 *
 * @示例
 * 输入：[1,1,2]
 *
 * @解题思路
 * 复用 q46 的 permute 生成全部排列，再用 HashMap 按排列去重。
 */
use super::q46::permute;

use std::collections::HashMap;

fn permute_unique(nums: Vec<i32>) -> Vec<Vec<i32>> {
    let mut ret = vec![];

    fn helper(nums: Vec<i32>) -> Vec<Vec<i32>> {
        let mut ret = vec![];
        if nums.len() == 1 {
            ret.push(nums);
            return ret;
        }

        for i in 0..nums.len() {
            let mut clone = nums.clone();
            let current = clone.remove(i);
            let tmp = permute(clone);
            for mut r in tmp {
                r.insert(0, current);
                ret.push(r);
            }
        }

        return ret;
    }

    let duplicated_ret = helper(nums);

    let mut tmp = HashMap::new();
    for i in 0..duplicated_ret.len() {
        tmp.insert(duplicated_ret[i].clone(), true);
    }

    for (k, _) in tmp {
        ret.push(k);
    }

    return ret;
}

#[test]
fn test_permute_unique() {
    let nums = vec![1, 1, 2];
    let ret = permute_unique(nums);
    for i in 0..ret.len() {
        for j in 0..ret[i].len() {
            print!("{}\t", ret[i][j])
        }
        println!();
    }
}
