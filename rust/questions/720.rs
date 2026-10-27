/**
 * No.720 词典中最长的单词
 *
 * @题目描述
 * 从词典中找出能由词典中逐个加一个字母构建出的最长单词。
 *
 * @示例
 * 输入：["w","wo","wor","world"]
 * 输出："world"
 *
 * @解题思路
 * 【占位实现】当前仅返回空字符串，待补充逻辑。
 */

fn longest_word(_words: Vec<String>) -> String {
    let ret = String::from("");

    return ret;
}

#[test]
fn test_longest_word() {
    let example = vec![
        String::from("w"),
        String::from("wo"),
        String::from("wor"),
        String::from("worl"),
        String::from("world"),
    ];
    let ret = longest_word(example);
    println!("{}", ret);
}
