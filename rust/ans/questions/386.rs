/**
 * No.386 字典序排数
 *
 * @题目描述
 * 返回 1..n 按字典序排序的结果。
 *
 * @示例
 * 输入：n = 13
 * 输出：[1,10,11,12,13,2,3,...,9]
 *
 * @解题思路
 * 十叉树前序 DFS：从 1..9 逐个出发，递归深入 cur*10 + i。
 */

fn lexical_order(n: i32) -> Vec<i32> {
    fn helper(cur: i32, max: i32, ret: &mut Vec<i32>) {
        if cur > max {
            return;
        }
        ret.push(cur);
        for i in 0..10 {
            helper(cur * 10 + i, max, ret);
        }
    }

    let mut ret = vec![];

    for i in 1..10 {
        helper(i, n, &mut ret)
    }

    return ret;
}

#[test]
fn test_lexical_order() {
    let ret = lexical_order(13);
    for i in 0..ret.len() {
        print!("{} ", ret[i]);
    }
}
