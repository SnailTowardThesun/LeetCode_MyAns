/**
 * No.1447 最简分数
 *
 * @题目描述
 * 返回所有分母 ≤ n 的最简真分数。
 *
 * @示例
 * 输入：n = 4
 * 输出：["1/2","1/3","2/3","1/4","3/4"]
 *
 * @解题思路
 * 枚举分母 i 与分子 j，gcd(i, j) == 1 时收录。
 */

fn simplified_fractions(n: i32) -> Vec<String> {
    let mut ret = vec![];

    fn helper(a: i32, b: i32) -> i32 {
        return if b == 0 { a } else { helper(b, a % b) };
    }

    for i in 1..n + 1 {
        for j in 1..i {
            println!("i: {}, j: {}", i, j);
            if helper(i, j) == 1 {
                ret.push(format!("{}/{}", j, i));
            }
        }
    }

    return ret;
}

#[test]
fn test_simplified_fractions() {
    let ret = simplified_fractions(4);
    for x in ret {
        print!("{}\t", x);
    }
}
