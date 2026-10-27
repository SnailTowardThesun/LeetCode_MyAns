/**
 * No.299 猜数字游戏
 *
 * @题目描述
 * Bulls and Cows：公牛为位置数字都对的数量，母牛为数字对位置错的数量。
 *
 * @示例
 * 输入：secret = "1807", guess = "7810"
 * 输出："1A3B"
 *
 * @解题思路
 * 【占位实现】当前仅返回空字符串，待补充统计逻辑。
 */

fn get_hint(_secret: String, _guess: String) -> String {
    let ret = String::from("");

    return ret;
}

#[test]
fn test_get_hint() {
    let secret = String::from("1807");
    let guess = String::from("7810");

    let ret = get_hint(secret, guess);
    println!("{}", ret)
}
