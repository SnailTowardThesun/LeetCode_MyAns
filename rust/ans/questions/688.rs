/**
 * No.688 骑士在棋盘上的概率
 *
 * @题目描述
 * n×n 棋盘上骑士从 (row,column) 走 k 步（每步 8 方向等概率）后仍在棋盘上的概率。
 *
 * @示例
 * 输入：n = 3, k = 2, row = 0, column = 0
 * 输出：0.0625
 *
 * @解题思路
 * 三维 DP：dp[i][j][p] 表示走 p 步到达 (i,j) 的概率，由 8 个来向转移，每步除以 8。
 */

fn knight_probability(n: i32, k: i32, row: i32, column: i32) -> f64 {
    let mut dp = vec![vec![vec![0.0; k as usize + 1]; n as usize]; n as usize];
    let dirs = vec![
        vec![-1, -2],
        vec![-1, 2],
        vec![1, -2],
        vec![1, 2],
        vec![-2, 1],
        vec![-2, -1],
        vec![2, 1],
        vec![2, -1],
    ];

    for i in 0..n {
        for j in 0..n {
            dp[i as usize][j as usize][0] = 1.0 as f64;
        }
    }

    for p in 1..k + 1 {
        for i in 0..n {
            for j in 0..n {
                for d in dirs.clone() {
                    let nx = i + d[0];
                    let ny = j + d[1];
                    if nx < 0 || ny < 0 || nx >= n || ny >= n {
                        continue;
                    }

                    dp[i as usize][j as usize][p as usize] +=
                        dp[nx as usize][ny as usize][p as usize - 1] / 8.0;
                }
            }
        }
    }

    return dp[row as usize][column as usize][k as usize];
}

#[test]
fn test_knight_probability() {
    let ret = knight_probability(10, 13, 5, 3);
    println!("{}", ret);
}
