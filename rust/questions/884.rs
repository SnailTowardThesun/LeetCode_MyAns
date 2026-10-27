/**
 * No.884 两句话中的不常见单词
 *
 * @题目描述
 * 在某个句子中只出现一次、且不出现在另一句中的单词。
 *
 * @示例
 * 输入：s1 = "this apple is sweet", s2 = "this apple is sour"
 * 输出：["sweet","sour"]
 *
 * @解题思路
 * 哈希对两句话整体计数，取出计数恰为 1 的单词。
 */

fn uncommon_from_sentences(s1: String, s2: String) -> Vec<String> {
    let mut ret = vec![];

    let mut tmp = std::collections::HashMap::new();

    fn helper(dics: &mut std::collections::HashMap<String, i32>, msg: &String) {
        for word in msg.split(' ') {
            if dics.contains_key(word) {
                if let Some(s) = dics.get_mut(word) {
                    *s += 1;
                }
                continue;
            }

            dics.insert(word.parse().unwrap(), 1);
        }
    }

    helper(&mut tmp, &s1);
    helper(&mut tmp, &s2);

    for (k, v) in tmp {
        if v == 1 {
            ret.push(k.to_string());
        }
    }

    return ret;
}

#[test]
fn test_uncommon_from_sentences() {
    let ret = uncommon_from_sentences(
        String::from("this apple is sweet"),
        String::from("this apple is sour"),
    );
    for i in 0..ret.len() {
        print!("{}\t", ret[i])
    }
}
