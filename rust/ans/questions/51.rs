/**
 * No.51 N 皇后
 *
 * @题目描述
 * n 皇后问题的全部棋盘摆法（任意两皇后不同行/列/对角线）。
 *
 * @示例
 * 输入：n = 4
 * 输出：2 种摆法（".Q.."/"...Q" 等）
 *
 * @解题思路
 * 逐行 DFS：cols 记录每行皇后所在列，not_valid 检查同列与两条对角线冲突，合法方案转成 Q/. 字符串。
 */

pub fn solve_n_queens(n: i32) -> Vec<Vec<String>> {
    fn make_ans(pos: Vec<Vec<usize>>) -> Vec<Vec<String>> {
        let mut ans = vec![];
        for cols in pos.iter() {
            let len = cols.len();
            let mut solution = vec![];
            for &line in cols {
                let mut s = ".".repeat(len).to_string();
                s.replace_range(line..line + 1, "Q");
                solution.push(s);
            }
            ans.push(solution);
        }
        ans
    }
    fn not_valid(cols: &Vec<usize>, cur: usize) -> bool {
        cols.iter().enumerate().any(|(r, &c)| {
            cur == c
                || cols.len() == r
                || (cur as i64 - c as i64).abs() == (cols.len() as i64 - r as i64).abs()
        })
    }
    fn dfs(n: usize, cols: &mut Vec<usize>, ans: &mut Vec<Vec<usize>>) {
        if cols.len() == n {
            ans.push(cols.to_vec());
            return;
        }
        for cur in 0..n {
            if not_valid(cols, cur) {
                continue;
            }
            cols.push(cur);
            dfs(n, cols, ans);
            cols.pop();
        }
    }
    let mut ans = vec![];
    dfs(n as usize, &mut vec![], &mut ans);
    return make_ans(ans);
}

#[test]
fn test_solve_n_queens() {
    let ret = solve_n_queens(4);
    for i in ret.iter() {
        for j in i.iter() {
            print!("{}\n", j);
        }
        println!("-------------------------------");
    }
}
