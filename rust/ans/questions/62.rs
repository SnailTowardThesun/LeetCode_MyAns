/**
 * No.62 不同路径
 *
 * @题目描述
 * m×n 网格从左上角到右下角（每次只能右移或下移）的路径数。
 *
 * @示例
 * 输入：m = 7, n = 3
 * 输出：28
 *
 * @解题思路
 * 二维 DP：首行首列置 1，其余 dp[i][j] = dp[i-1][j] + dp[i][j-1]。
 */

fn unique_paths(m: i32, n: i32) -> i32 {
    let n = n as usize;
    let m = m as usize;

    let mut paths = vec![vec![0; n]; m];

    for i in 0..m {
        paths[i][0] = 1;
    }

    for j in 0..n {
        paths[0][j] = 1;
    }

    for i in 1..m {
        for j in 1..n {
            paths[i][j] = paths[i - 1][j] + paths[i][j - 1];
        }
    }

    return paths[m - 1][n - 1] as i32;
}

#[test]
fn test_unique_paths() {
    let m = 7;
    let n = 3;

    assert_eq!(unique_paths(m, n), 28)
}
