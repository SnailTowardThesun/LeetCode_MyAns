/**
 * No.1020 飞地的数量
 *
 * @题目描述
 * 无法离开边界（上下左右四方向连通到边界）的陆地格数量。
 *
 * @示例
 * 输入：[[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
 * 输出：1
 *
 * @解题思路
 * DFS 把与四条边界连通的陆地全部置 0，剩余 1 的个数即飞地数。
 */

fn num_enclaves(grid: Vec<Vec<i32>>) -> i32 {
    let mut grid = grid;

    fn helper(g: &mut Vec<Vec<i32>>, col: usize, row: usize) {
        if g[col][row] == 0 {
            return;
        }

        g[col][row] = 0;

        if col == g.len() && row == g[0].len() {
            return;
        }

        // left
        if row > 0 {
            helper(g, col, row - 1);
        }

        // top
        if col > 0 {
            helper(g, col - 1, row);
        }

        // right
        if row < g[0].len() - 1 {
            helper(g, col, row + 1);
        }

        // bottom
        if col < g.len() - 1 {
            helper(g, col + 1, row);
        }
    }

    let height = grid.len();
    let width = grid[0].len();

    for i in 0..width {
        helper(&mut grid, 0, i);
        helper(&mut grid, height - 1, i);
    }

    for i in 0..height {
        helper(&mut grid, i, 0);
        helper(&mut grid, i, width - 1);
    }

    let mut ret = 0;
    for i in 0..height {
        for j in 0..width {
            ret += grid[i][j];
        }
    }

    return ret;
}

#[test]
fn test_num_enclaves() {
    // let example = vec![vec![0, 0, 0, 0], vec![1, 0, 1, 0], vec![0, 1, 1, 0], vec![0, 0, 0, 0]];
    let example = vec![vec![0], vec![1], vec![1], vec![0], vec![0]];
    let ret = num_enclaves(example);
    println!("{}", ret);
}
