/**
 * No.52 N 皇后 II
 *
 * @题目描述
 * n 皇后问题的解的数量。
 *
 * @示例
 * 输入：n = 10
 * 输出：724
 *
 * @解题思路
 * 直接复用 q51 的 solve_n_queens，返回解的个数。
 */
use super::q51::solve_n_queens;

fn total_n_queens(n: i32) -> i32 {
    let ret = solve_n_queens(n);
    return ret.len() as i32;
}

#[test]
fn test_total_n_queens() {
    let ret = total_n_queens(10);
    println!("{}", ret);
}
