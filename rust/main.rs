#![allow(dead_code)]

//! LeetCode 题解（Rust 版），文件组织与 cplusplus/、python/ 对齐：
//! - 每日一题：questions/<题号>.rs（Rust 模块名不能以数字开头，经 questions/mod.rs 的 #[path] 映射）
//! - 公共数据结构：leetcode_common.rs（ListNode/TreeNode 及构造工具，题解统一引入，禁止重复定义）
//! - 新题模板：questions/_template.rs
//! - 附加练习：extras.rs（无题号的历史题目）

mod extras;
mod leetcode_common;
mod questions;
