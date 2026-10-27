/**
 * No.96 不同的二叉搜索树
 *
 * @题目描述
 * 1..n 能构成的结构不同的 BST 种数。
 *
 * @示例
 * 输入：n = 3
 * 输出：5
 *
 * @解题思路
 * 卡特兰数 DP：dp[i] = Σ dp[j-1] * dp[i-j]（j 为根）。
 */

fn num_trees(n: i32) -> i32 {
    let n = n as usize;
    let mut dp: Vec<i32> = vec![0; n + 1];
    dp[0] = 1;
    dp[1] = 1;
    for i in 2..=n {
        for j in 1..=i {
            dp[i] += dp[j - 1] * dp[i - j];
        }
    }

    return dp[n];
}

#[test]
fn test_num_trees() {
    num_trees(10);
}
