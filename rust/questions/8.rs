/**
 * No.8 字符串转换整数 (atoi)
 *
 * @题目描述
 * 实现 atoi：跳过前导空格，接受一个正负号，取连续数字转换为整数，超界截断到 i32 范围。
 *
 * @示例
 * 输入：" -42"
 * 输出：-42
 *
 * @解题思路
 * 状态机式扫描：空格/符号/数字三类字符分别处理，数字用 i64 累积防溢出，符号只允许出现一次。
 */

fn my_atoi(str: String) -> i32 {
    let mut ret: i64 = 0;
    let mut is_recording: bool = false;
    let mut is_positive_or_negative_sign_apper: bool = false;
    let mut is_negative: bool = false;

    for ch in str.chars().into_iter() {
        if ch == ' ' {
            if is_recording {
                break;
            }
            continue;
        }

        if ch == '-' {
            if is_positive_or_negative_sign_apper {
                break;
            }
            if is_recording {
                break;
            }
            is_recording = true;
            is_positive_or_negative_sign_apper = true;
            is_negative = true;
            continue;
        }

        if ch == '+' {
            if is_positive_or_negative_sign_apper {
                break;
            }
            if is_recording {
                break;
            }
            is_recording = true;
            is_positive_or_negative_sign_apper = true;
            continue;
        }

        if ch >= '0' && ch <= '9' {
            is_recording = true;
            ret = ret * 10 + ch.to_digit(10).unwrap() as i64;
            if ret > i32::MAX as i64 {
                break;
            }
            continue;
        }

        break;
    }

    if is_negative {
        ret = 0 - ret;
    }

    if ret > i32::MAX as i64 {
        return i32::MAX;
    }

    if ret < i32::MIN as i64 {
        return i32::MIN;
    }

    return ret as i32;
}

#[test]
fn test_my_atoi() {
    let s = String::from("9223372036854775808");
    assert_eq!(my_atoi(s), i32::MAX);
}
