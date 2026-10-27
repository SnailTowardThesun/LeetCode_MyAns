/**
 * No.1765 地图中的最高点
 *
 * @题目描述
 * isWater[i][j]=1 是水域，高度为 0；相邻格高度差 ≤ 1，求高度和最大的地图。
 *
 * @示例
 * 输入：[[0,1],[0,0]]
 * 输出：[[1,0],[2,1]]
 *
 * @解题思路
 * 多源 BFS：所有水域入队作为第 0 层，逐层向外扩散，每层高度 +1。
 */
use std::collections::VecDeque;

fn highest_peak(is_water: Vec<Vec<i32>>) -> Vec<Vec<i32>> {
    let m = is_water.len();
    let n = is_water[0].len();

    let mut ret = vec![vec![0; n]; m];
    let mut container = VecDeque::new();

    let mut visited = vec![vec![false; n]; m];
    for i in 0..m {
        for j in 0..n {
            if is_water[i][j] == 1 {
                visited[i][j] = true;
                container.push_back((i, j));
            }
        }
    }

    let mut target = 1;
    while !container.is_empty() {
        for _ in 0..container.len() {
            let (i, j) = container.pop_front().unwrap();
            for (x, y) in [(i + 1, j), (i - 1, j), (i, j + 1), (i, j - 1)] {
                if x < m && y < n && !visited[x][y] {
                    ret[x][y] = target;
                    visited[x][y] = true;
                    container.push_back((x, y));
                }
            }
        }

        target = target + 1;
    }

    return ret;
}

#[test]
fn test_highest_peak() {
    // let is_water = vec![vec![0,1],vec![0,0]];
    // highest_peak(is_water);
}
