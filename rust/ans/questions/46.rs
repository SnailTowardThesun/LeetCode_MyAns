/**
 * No.46 全排列
 *
 * @题目描述
 * 返回不含重复数字的数组的所有全排列。
 *
 * @示例
 * 输入：[1,2,3]
 *
 * @解题思路
 * 枚举每个位置取出的数：remove(i) 取出当前数，对剩余数组递归求排列，再把当前数插回每个子排列头部。
 */

pub fn permute(nums: Vec<i32>) -> Vec<Vec<i32>> {
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

#[test]
fn test_permute() {
    let nums = vec![1, 2, 3];
    let ret = permute(nums);
    for i in 0..ret.len() {
        for j in 0..ret[i].len() {
            print!("{}\t", ret[i][j])
        }
        println!();
    }
}
