/**
 * No.72 编辑距离
 *
 * @题目描述
 * word1 转换成 word2 所需最少操作数（插入/删除/替换一个字符）。
 *
 * @示例
 * 输入：word1 = "intention", word2 = "execution"
 * 输出：5
 *
 * @解题思路
 * 二维 DP：steps[i][j] 为前缀转换代价，字符相同继承左上角，否则取 左/上/左上 最小值 +1。
 */

fn min_distance(word1: String, word2: String) -> i32 {
    let n = word1.len();
    let m = word2.len();

    let mut steps = vec![vec![0; n + 1]; m + 1];

    for i in 0..m + 1 {
        steps[i][0] = i;
    }

    for i in 0..n + 1 {
        steps[0][i] = i;
    }

    let b1 = word1.as_bytes();
    let b2 = word2.as_bytes();

    for i in 0..m {
        for j in 0..n {
            if b1[j] == b2[i] {
                steps[i + 1][j + 1] = steps[i][j];
            } else {
                steps[i + 1][j + 1] =
                    std::cmp::min(std::cmp::min(steps[i][j], steps[i + 1][j]), steps[i][j + 1]) + 1;
            }
        }
    }
    return steps[m][n] as i32;
}

#[test]
fn test_min_distance() {
    let word1 = String::from("intention");
    let word2 = String::from("execution");

    assert_eq!(min_distance(word1, word2), 5);
}
