/**
 * No.3 无重复字符的最长子串
 *
 * @题目描述
 * 求不含重复字符的最长子串的长度。
 *
 * @示例
 * 输入："abcabcbb"
 * 输出：3（最长子串 "abc"）
 *
 * @解题思路
 * 滑动窗口 + 下标数组：dic[128] 记录每个字符上次出现的下标，重复时把窗口起点 start 移到上次出现位置之后，边扫边更新最长长度。
 */

fn length_of_longest_substring(s: String) -> i32 {
    let mut ret: i32 = 0;
    let mut start: i32 = -1;

    let mut dic = vec![-1; 128];

    let b = s.as_bytes();
    for i in 0..s.len() {
        // if repeat just move the start
        if dic[b[i as usize] as usize] > start {
            start = dic[b[i as usize] as usize]
        }

        ret = std::cmp::max(ret, i as i32 - start);
        dic[b[i as usize] as usize] = i as i32;
    }

    return ret as i32;
}

#[test]
fn test_length_of_longest_substring() {
    let case1 = String::from("abcabcbb");
    let case2 = String::from("bbbbb");
    let case3 = String::from("pwwkew");

    assert_eq!(length_of_longest_substring(case1), 3);
    assert_eq!(length_of_longest_substring(case2), 1);
    assert_eq!(length_of_longest_substring(case3), 3);
}
