/**
 * No.1678 设计 Goal 解析器
 *
 * @题目描述
 * 把命令字符串中的 "()" 解释为 "o"、"(al)" 解释为 "al"。
 *
 * @示例
 * 输入："G()(al)"
 * 输出："Goal"
 *
 * @解题思路
 * 链式字符串替换。
 */

fn interpret(command: String) -> String {
    command.replace("()", "o").replace("(al)", "al")
}

#[test]
fn test_interpret() {
    let obj = String::from("G()(al)");
    let ret = interpret(obj);
    println!("{}", ret);
}
