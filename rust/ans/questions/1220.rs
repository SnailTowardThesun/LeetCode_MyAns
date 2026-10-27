/**
 * No.1220 统计元音字母序列的数目
 *
 * @题目描述
 * 长度 n 的序列，每个元音后可跟的元音按规则限定，求方案数（mod 1e9+7）。
 *
 * @示例
 * 输入：n = 1
 * 输出：5
 *
 * @解题思路
 * 相邻规则 DP：滚动数组 dp/ndp 五个元音状态按转移表累加。
 */

fn count_vowel_permutation(n: i32) -> i32 {
    let tmp: i64 = 1000000000 + 7;
    let mut dp = vec![1, 1, 1, 1, 1];
    let mut ndp = vec![0, 0, 0, 0, 0];

    for _ in 1..n {
        ndp[0] = (dp[1] + dp[2] + dp[4]) % tmp;
        ndp[1] = (dp[0] + dp[2]) % tmp;
        ndp[2] = (dp[1] + dp[3]) % tmp;
        ndp[3] = (dp[2]) % tmp;
        ndp[4] = (dp[2] + dp[3]) % tmp;
        dp = ndp.clone();
    }

    let mut ans = 0;
    for i in 0..5 {
        ans = (ans + dp[i]) % tmp;
    }
    return ans as i32;
}

#[test]
fn test_count_vowel_permutation() {
    let ret = count_vowel_permutation(144);
    print!("{}", ret);
}
