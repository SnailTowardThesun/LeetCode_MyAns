/**
 * No.1380 矩阵中的幸运数
 *
 * @题目描述
 * 幸运数 = 所在行最小且所在列最大的元素。
 *
 * @示例
 * 输入：[[3,7,8],[9,11,13],[15,16,17]]
 * 输出：15
 *
 * @解题思路
 * 预计算每列最大值，再逐行找行最小值并比对是否等于该列最大。
 */

fn lucky_numbers(matrix: Vec<Vec<i32>>) -> Vec<i32> {
    let m = matrix.len();
    let n = matrix[0].len();
    let mut col = vec![0; n];
    let mut res = vec![];
    for j in 0..n {
        for i in 0..m {
            col[j] = col[j].max(matrix[i][j]);
        }
    }
    for x in 0..m {
        let mut i = 0;
        for y in 1..n {
            if matrix[x][y] < matrix[x][i] {
                i = y;
            }
        }
        if matrix[x][i] == col[i] {
            res.push(col[i]);
        }
    }
    return res;
}

#[test]
fn test_lucky_numbers() {
    let example = vec![vec![7, 8], vec![1, 2]];
    let ret = lucky_numbers(example);
    println!("{}", ret[0]);
}
