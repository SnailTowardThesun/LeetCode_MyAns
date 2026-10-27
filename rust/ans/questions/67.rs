/**
 * No.67 二进制求和
 *
 * @题目描述
 * 两个二进制字符串相加。
 *
 * @示例
 * 输入：a = "11", b = "1"
 * 输出："100"
 *
 * @解题思路
 * 转成 i128 相加后按二进制格式化输出。
 */

fn add_binary(a: String, b: String) -> String {
    let ia = i128::from_str_radix(&a, 2).unwrap();
    let ib = i128::from_str_radix(&b, 2).unwrap();
    return format!("{:b}", (ia + ib)).to_string();
}

#[test]
fn test_add_binary() {
    let a = String::from("11");
    let b = String::from("1");
    let ret = add_binary(a, b);
    println!("{}", ret);
}
