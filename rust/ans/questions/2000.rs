/**
 * No.2000 反转单词前缀
 *
 * @题目描述
 * 把单词第一个字符 ch 及其之前的部分反转。
 *
 * @示例
 * 输入：word = "abcdefd", ch = "d"
 * 输出："dcbaefd"
 *
 * @解题思路
 * find 定位 ch，反转前缀后拼接剩余部分；找不到则原样返回。
 */

fn reverse_prefix(word: String, ch: char) -> String {
    let pos = word.find(ch);
    if pos == None {
        return word;
    }

    return word[0..pos.unwrap() + 1].chars().rev().collect::<String>()
        + &word[(pos.unwrap() + 1)..];
}

#[test]
fn test_reverse_prefix() {
    let example = String::from("abcdef");
    let ret = reverse_prefix(example, 'd');
    println!("{}", ret);
}
