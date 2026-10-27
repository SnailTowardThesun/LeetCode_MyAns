/**
 * No.1763 最长的美好子字符串
 *
 * @题目描述
 * 美好子串：每个字母的大小写形式同时出现。求最长者。
 *
 * @示例
 * 输入："YazaAay"
 * 输出："aAa"
 *
 * @解题思路
 * 分治：找到第一个大小写不配对的字符，以它为分割点两侧递归，取较长者。
 */

fn longest_nice_substring(s: String) -> String {
    let mut upper_letter = vec![false; 26];
    let mut lower_letter = vec![false; 26];

    for i in s.chars() {
        if i.is_ascii_uppercase() {
            upper_letter[i as usize - 'A' as usize] = true;
        } else {
            lower_letter[i as usize - 'a' as usize] = true;
        }
    }

    for (_i, (pos, ch)) in s.char_indices().enumerate() {
        if upper_letter[ch.to_ascii_uppercase() as usize - 'A' as usize] == true
            && lower_letter[ch.to_ascii_lowercase() as usize - 'a' as usize] == true
        {
            continue;
        }

        let s1 = longest_nice_substring(s[0..pos].to_string());
        let s2 = longest_nice_substring(s[pos + ch.len_utf8()..].to_string());
        return if s1.len() >= s2.len() { s1 } else { s2 };
    }

    return s;
}

#[test]
fn test_longest_nice_substring() {
    let example = String::from("YazaAay");
    let ret = longest_nice_substring(example);
    println!("{}", ret);
}
