/**
 * No.17 电话号码的字母组合
 *
 * @题目描述
 * 数字串 2-9 按九宫格键盘映射到字母，返回所有可能的字母组合。
 *
 * @示例
 * 输入："23"
 * 输出：["ad","ae","af","bd",...,"cf"]
 *
 * @解题思路
 * 哈希表存 数字→字母串，DFS 逐位枚举字母回溯拼接。
 */
use std::collections::HashMap;

fn letter_combinations(digits: String) -> Vec<String> {
    let mut map = HashMap::new();
    map.insert('2', "abc".to_string());
    map.insert('3', "def".to_string());
    map.insert('4', "ghi".to_string());
    map.insert('5', "jkl".to_string());
    map.insert('6', "mno".to_string());
    map.insert('7', "pqrs".to_string());
    map.insert('8', "tuv".to_string());
    map.insert('9', "wxyz".to_string());

    fn dfs(
        idx: usize,
        digits: &String,
        map: &HashMap<char, String>,
        path: &mut String,
        ans: &mut Vec<String>,
    ) {
        if digits.len() == idx {
            ans.push(path.clone());
            return;
        }
        let cc = digits.chars().nth(idx).unwrap();
        for c in map.get(&cc).unwrap().chars() {
            path.push(c);
            dfs(idx + 1, &digits, &map, path, ans);
            path.pop();
        }
    }
    let mut ans = Vec::new();
    if digits.is_empty() {
        return ans;
    }
    dfs(0, &digits, &map, &mut String::new(), &mut ans);

    return ans;
}

#[test]
fn test_letter_combinations() {
    let digits = String::from("23");
    let ret = letter_combinations(digits);
    for i in ret {
        println!("{}", i);
    }
}
