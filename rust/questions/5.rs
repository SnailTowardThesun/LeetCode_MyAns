/**
 * No.5 最长回文子串
 *
 * @题目描述
 * 求字符串中最长的回文子串。
 *
 * @示例
 * 输入："cbbd"
 * 输出："bb"
 *
 * @解题思路
 * 区间 DP：flags[j][i] 表示 s[j..=i] 是否回文，由 flags[j+1][i-1] 转移（两端相等且内部回文）；记录最长回文的起点与长度。
 */

fn longest_palindrome(s: String) -> String {
    let size = s.len();

    if size == 0 {
        return String::from("");
    }

    let mut flags = vec![vec![false; size]; size];

    let mut start = 0;
    let mut max = 1;
    let b = s.as_bytes();

    for i in 1..size {
        flags[i][i] = true;

        for j in 0..i {
            flags[j][i] = b[j] == b[i] && (i - j < 3 || flags[j + 1][i - 1]);
            if flags[j][i] && i - j + 1 > max {
                start = j;
                max = i - j + 1;
            }
        }
    }

    let end = start + max;
    return (s[start as usize..end as usize]).to_string();
}

#[test]
fn test_longest_palindrome() {
    let demo1 = String::from("cbbd");
    let ret = longest_palindrome(demo1);
    assert_eq!(ret, "bb");
}
