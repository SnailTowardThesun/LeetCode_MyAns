/**
 * No.65 有效数字
 *
 * @题目描述
 * 判断字符串是否为合法数字（十进制/科学计数法，可带符号）。
 *
 * @示例
 * 输入："0"
 * 输出：true
 *
 * @解题思路
 * 自动机：Begin/Sign/Num/NumDot/InDot/DotNum/InE/InESign/InENum 九状态逐字符转移，终态为 Num/NumDot/DotNum/InENum。
 */

fn is_number(s: String) -> bool {
    for ch in s.chars() {
        if ch.is_alphabetic() && (ch != 'e' && ch != 'E') {
            return false;
        }
    }

    enum State {
        Begin,
        Sign,    // "+"     "-"
        Num,     // "+1"    "-12",   "123"
        NumDot,  // "1."    "-2."
        InDot,   // "-."    "+."     "."
        DotNum,  // ".9"    "+1.2"   "0.0"
        InE,     // "2.E"   "-0.9e"
        InESign, // "4E-"   "0.01e+"
        InENum,  // "3e-2"  "4.e12"
        Error,
    }

    use State::*;

    fn is_digit(c: u8) -> bool {
        return b'0' <= c && c <= b'9';
    }

    let mut state = Begin;
    for c in s.as_bytes() {
        state = match state {
            Begin => match c {
                b'+' | b'-' => Sign,
                b'.' => InDot,
                c if is_digit(*c) => Num,
                _ => Error,
            },
            Sign => match c {
                c if is_digit(*c) => Num,
                b'.' => InDot,
                _ => Error,
            },
            Num => match c {
                c if is_digit(*c) => Num,
                b'.' => NumDot,
                b'e' | b'E' => InE,
                _ => Error,
            },
            InDot => match c {
                c if is_digit(*c) => DotNum,
                _ => Error,
            },
            NumDot => match c {
                c if is_digit(*c) => DotNum,
                b'e' | b'E' => InE,
                _ => Error,
            },
            DotNum => match c {
                c if is_digit(*c) => DotNum,
                b'e' | b'E' => InE,
                _ => Error,
            },
            InE => match c {
                b'+' | b'-' => InESign,
                c if is_digit(*c) => InENum,
                _ => Error,
            },
            InESign => match c {
                c if is_digit(*c) => InENum,
                _ => Error,
            },
            InENum => match c {
                c if is_digit(*c) => InENum,
                _ => Error,
            },
            Error => return false,
        };
    }
    return match state {
        Num | NumDot | DotNum | InENum => true,
        _ => false,
    };
}

#[test]
fn test_is_number() {
    let example = String::from("0");
    let ret = is_number(example);
    println!("result: {}", ret);
}
