# Rust 算法题解

本目录包含使用 Rust 语言实现的 LeetCode 算法题解，文件组织与 `cplusplus/`、`python/` 保持一致。

## 技术栈

- **语言**: Rust 最新稳定版（Cargo Workspace）
- **依赖**: 标准库为主，必要时使用外部 crate（如 `rand`）
- **测试**: Rust 内置测试框架

## 代码结构

```
rust/
├── ans/                       # 主答案 crate
│   ├── questions/             # 每日一题（按题号命名，与 cplusplus/questions/、python/questions/ 对应）
│   │   ├── 1.rs               # No.1 两数之和
│   │   ├── 25.rs              # No.25 K 个一组翻转链表
│   │   ├── ...
│   │   ├── _template.rs       # 新题模板（不注册到 mod.rs，不参与编译）
│   │   └── mod.rs             # #[path] 把 q<题号> 模块映射到 <题号>.rs
│   ├── leetcode_common.rs     # 公共数据结构（对应 cplusplus/leetcode_common.h、python/leetcode_common/）
│   ├── extras.rs              # 附加练习（无题号的历史题目）
│   ├── main.rs                # crate 根，仅声明模块
│   └── Cargo.toml
├── baseAlgorithm/             # 基础算法练习 crate（排序 / 并查集 / 树遍历）
└── README.md                  # 项目说明文档
```

## 约定

- **每日一题**: 一题一文件 `questions/<题号>.rs`，注释头包含 `@题目描述` / `@示例` / `@解题思路`
- **公共数据结构**: `ListNode` / `TreeNode` 及构造工具统一 `use crate::leetcode_common::...` 引入，禁止在题解文件中重复定义
- **跨题复用**: 被其他题引用的函数（如 `q51::solve_n_queens`、`q56::merge`、`q547::OrderedUnion`）声明为 `pub`，用 `use super::q<题号>::...` 引入
- **命名规范**: 函数/变量 `snake_case`，结构体/枚举 `PascalCase`
- **新题**: 复制 `questions/_template.rs` 为 `<题号>.rs`，并在 `questions/mod.rs` 中注册

## 编译与运行

```bash
cd rust

cargo build              # 构建所有模块（0 警告）
cargo test               # 运行全部测试
cargo test q1            # 运行单题测试（如 No.1）
cargo fmt                # 格式化
cargo clippy             # 静态检查
```

## 注意事项

- 新增题目时，请确保代码注释完整，包含题目描述和解题思路
- 测试用例应包含基本测试用例和边界条件测试
- 保持代码风格一致，使用 `cargo fmt` 和 `cargo clippy` 确保代码质量

## 参考资料

- [Rust 官方文档](https://doc.rust-lang.org/)
- [LeetCode 官网](https://leetcode.com/)
- [Rust 语言圣经](https://kaisery.github.io/trpl-zh-cn/)
