/**
 * No.64 最小路径和
 *
 * @题目描述
 * 从左上角到右下角（只能右/下）路径数字总和最小值。
 *
 * @示例
 * 输入：[[1,3,1],[1,5,1],[4,2,1]]
 * 输出：7
 *
 * @解题思路
 * 原地 DP：先累计首行首列，其余格 += min(上, 左)。
 */
use std::cmp;

fn min_path_sum(grid: Vec<Vec<i32>>) -> i32 {
    let grid = grid;

    let m = grid.len();
    let n = grid[0].len();

    let mut min_paths = grid;
    for i in 1..m {
        min_paths[i][0] = min_paths[i - 1][0] + min_paths[i][0];
    }

    for i in 1..n {
        min_paths[0][i] = min_paths[0][i - 1] + min_paths[0][i];
    }

    for i in 1..m {
        for j in 1..n {
            min_paths[i][j] = min_paths[i][j] + cmp::min(min_paths[i - 1][j], min_paths[i][j - 1]);
        }
    }

    return min_paths[m - 1][n - 1];
}

#[test]
fn test_in_path_sum() {
    let grid: Vec<Vec<i32>> = vec![vec![1, 3, 1], vec![1, 5, 1], vec![4, 2, 1]];
    assert_eq!(min_path_sum(grid), 7);
}
