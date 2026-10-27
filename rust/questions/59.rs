/**
 * No.59 螺旋矩阵 II
 *
 * @题目描述
 * 按顺时针螺旋顺序把 1..n² 填入 n×n 矩阵。
 *
 * @示例
 * 输入：n = 3
 * 输出：[[1,2,3],[8,9,4],[7,6,5]]
 *
 * @解题思路
 * 四边界（top/right/left/down）收缩模拟：按 左→右、上→下、右→左、下→上 四个方向循环填数并收缩边界。
 */

fn generate_matrix(n: i32) -> Vec<Vec<i32>> {
    let mut ret = vec![vec![0; n as usize]; n as usize];

    let mut direction = 0; // 0: left->right, 1: top->down, 2: right->left, 3: down->top
    let (mut top, mut right, mut left, mut down) =
        (0 as usize, (n - 1) as usize, 0 as usize, (n - 1) as usize);
    let mut count = 1;
    while top <= down && left <= right {
        match direction {
            0 => {
                for i in left..right + 1 {
                    ret[top][i] = count;
                    count += 1;
                }
                top += 1;
                direction = 1;
            }
            1 => {
                for i in top..down + 1 {
                    ret[i][right] = count;
                    count += 1;
                }
                right -= 1;
                direction = 2;
            }
            2 => {
                for i in (left..right + 1).rev() {
                    ret[down][i] = count;
                    count += 1;
                }
                down -= 1;
                direction = 3
            }
            3 => {
                for i in (top..down + 1).rev() {
                    ret[i][left] = count;
                    count += 1;
                }
                left += 1;
                direction = 0;
            }
            _ => {}
        }
    }

    return ret;
}

#[test]
fn test_generate_matrix() {
    let ret = generate_matrix(3);
    println!("{}", ret.len());
}
