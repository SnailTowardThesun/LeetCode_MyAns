/**
 * No.1405 最长快乐字符串
 *
 * @题目描述
 * 只含 a/b/c 且不含 aaa/bbb/ccc 的最长字符串（给定各字母数量上限）。
 *
 * @示例
 * 输入：a = 0, b = 8, c = 11
 *
 * @解题思路
 * 贪心：每轮把剩余数量最多的字母接到串尾；若末尾已连出两个相同字母则改放次多的。
 */

fn longest_diverse_string(a: i32, b: i32, c: i32) -> String {
    let mut ch = vec![(a, 'a'), (b, 'b'), (c, 'c')];
    let mut ans = vec![];
    loop {
        ch.sort_unstable();
        if ch[2].0 == 0 {
            break;
        }
        let len = ans.len();
        if len >= 2 && ans[len - 1] == ans[len - 2] && ans[len - 1] == ch[2].1 {
            if ch[1].0 > 0 {
                ch[1].0 -= 1;
                ans.push(ch[1].1);
            } else {
                ch[2].0 -= 1;
            }
        } else {
            ch[2].0 -= 1;
            ans.push(ch[2].1);
        }
    }
    ans.iter().collect()
}

#[test]
fn test_longest_diverse_string() {
    let ret = longest_diverse_string(0, 8, 11);
    print!("{}\n", ret);
}
