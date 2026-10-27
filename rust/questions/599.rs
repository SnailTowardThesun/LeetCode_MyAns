/**
 * No.599 两个列表的最小索引总和
 *
 * @题目描述
 * 两个列表共同出现的餐厅中，下标之和最小者（可能并列多个）。
 *
 * @示例
 * 输入：["Shogun","Tapioca Express"], ["Piatti","Shogun"]
 * 输出：["Shogun"]
 *
 * @解题思路
 * 哈希存 list1 的 餐厅→下标；扫 list2 遇共同餐厅时更新最小下标和与结果集。
 */
use std::collections::HashMap;

fn find_restaurant(list1: Vec<String>, list2: Vec<String>) -> Vec<String> {
    let mut ret = vec![];
    let mut container: HashMap<String, usize> = HashMap::new();

    for (i, item) in list1.iter().enumerate() {
        container.insert(item.to_string(), i);
    }

    let mut min = usize::MAX;
    for (i, item) in list2.iter().enumerate() {
        if let Some(j) = container.get(item) {
            if i + j < min {
                ret = vec![item.to_string()];
                min = i + j;
            } else if i + j == min {
                ret.push(item.to_string());
            }
        }
    }

    return ret;
}

#[test]
fn test_find_restaurant() {
    let l1 = vec![
        String::from("Shogun"),
        String::from("Tapioca Express"),
        String::from("Burger King"),
        String::from("KFC"),
    ];
    let l2 = vec![
        String::from("Piatti"),
        String::from("The Grill at Torrey Pines"),
        String::from("Hungry Hunter Steakhouse"),
        String::from("Shogun"),
    ];
    let ret = find_restaurant(l1, l2);
    for i in ret {
        println!("{}", i)
    }
}
