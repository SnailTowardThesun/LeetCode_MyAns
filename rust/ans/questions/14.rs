/**
 * No.14 最长公共前缀
 *
 * @题目描述
 * 求字符串数组的最长公共前缀，不存在返回空串。
 *
 * @示例
 * 输入：["flower","flow","flight"]
 * 输出："fl"
 *
 * @解题思路
 * 逐列比较：以最短串长度为界，第 i 列字符不一致时返回前 i 个字符组成的子串。
 */

fn longest_common_prefix(strs: Vec<String>) -> String {
    if strs.len() == 0 {
        return String::from("");
    }

    if strs.len() == 1 {
        return strs[0].to_string();
    }

    let min_len = strs.iter().map(|s| s.len()).min().unwrap();

    for i in 0..min_len {
        let c = strs[0].chars().nth(i).unwrap();

        for s in &strs {
            if s.chars().nth(i).unwrap() != c {
                return s[0..i].to_string();
            }
        }
    }

    return strs[0][..min_len].to_string();
}

#[test]
fn test_logest_common_prefix() {
    let demo = vec![
        String::from("flower"),
        String::from("flow"),
        String::from("flight"),
    ];
    assert_eq!(longest_common_prefix(demo), "fl");
}
