/**
 * No.717 1 比特与 2 比特字符
 *
 * @题目描述
 * 比特串由 0（1 比特字符）与 10/11（2 比特字符）组成，判断最后一个字符是否必为 1 比特字符。
 *
 * @示例
 * 输入：[1,1,1,0]
 * 输出：false
 *
 * @解题思路
 * 扫描分组：遇 1 消耗两个比特，遇 0 消耗一个，看最后一个 0 是否恰好单独成组落位。
 */

fn is_one_bit_character(bits: Vec<i32>) -> bool {
    if bits[bits.len() - 1] == 1 {
        return false;
    }

    if bits.len() > 2 {
        if bits[bits.len() - 1] == 0 && bits[bits.len() - 2] == 0 {
            return true;
        }
    }

    let mut ret = false;

    let mut container = vec![];
    for i in bits {
        if i == 1 {
            if container.len() == 1 {
                container.clear();
                ret = false;
            } else {
                container.push(i);
            }
        } else {
            if container.len() == 1 {
                container.clear();
                ret = false;
            } else {
                ret = true;
            }
        }
    }

    return ret;
}

#[test]
fn test_is_one_bit_character() {
    let example = vec![1, 1, 1, 0];
    let ret = is_one_bit_character(example);
    println!("ret: {}", ret);
}
