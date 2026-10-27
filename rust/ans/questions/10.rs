/**
 * No.10 正则表达式匹配
 *
 * @题目描述
 * 实现支持 '.' 和 '*' 的正则匹配，'.' 匹配任意单字符，'*' 匹配零个或多个前一元素，须整串匹配。
 *
 * @示例
 * 输入：s = "aa", p = "a*"
 * 输出：true
 *
 * @解题思路
 * 递归 + 模式解析：parse 把模式拆成 Empty/Single/Repeatable 三种单元；Repeatable 时走「匹配一次后带着 * 继续」或「* 吞掉零个字符」两条分支。
 */

fn is_match_bytes(s: &[u8], p: &[u8]) -> bool {
    match parse(p) {
        (Pattern::Empty, _) => s.is_empty(),
        (Pattern::Single(c), subp) => is_match_single(s, c, subp),
        (Pattern::Repeatable(c), subp) => is_match_single(s, c, p) || is_match_bytes(s, subp),
    }
}

fn is_match_single(s: &[u8], to_match: u8, p: &[u8]) -> bool {
    match s.split_first() {
        Some((c, s)) if to_match == b'.' || to_match == *c => is_match_bytes(s, p),
        _ => false,
    }
}

// Parser part:

enum Pattern {
    Empty,
    Single(u8),
    Repeatable(u8),
}

/// Returns the parsed pattern and the next pattern to parse.
fn parse(p: &[u8]) -> (Pattern, &[u8]) {
    match p.split_first() {
        None => (Pattern::Empty, p),
        Some((c, p)) => match p.split_first() {
            Some((b'*', p)) => (Pattern::Repeatable(*c), p),
            _ => (Pattern::Single(*c), p),
        },
    }
}

fn is_match(s: String, p: String) -> bool {
    return is_match_bytes(s.as_bytes(), p.as_bytes());
}

#[test]
fn test_is_match() {
    {
        let demo1 = String::from("aa");
        let match1 = String::from("a*");
        assert_eq!(is_match(demo1, match1), true);
    }
    {
        let demo1 = String::from("aa");
        let match1 = String::from("a");
        assert_eq!(is_match(demo1, match1), false);
    }
}
