# Rust 算法题解

本目录包含使用 Rust 语言实现的 LeetCode 算法题解。

## 技术栈

- **语言**: Rust 最新稳定版
- **依赖**: 标准库为主，必要时使用外部 crate
- **测试**: Rust 内置测试框架

## 代码结构

```
rust/
├── ans/                    # 主答案模块
│   ├── questions/          # 每日一题（按题目编号命名）
│   │   ├── 1615.rs
│   │   └── 2389.rs
│   ├── top150/             # 面试经典 150 题
│   │   ├── array/          # 数组相关题目
│   │   └── string/         # 字符串相关题目
│   ├── main.rs             # 经典算法题实现
│   └── Cargo.toml          # 项目配置文件
├── baseAlgorithm/          # 基础算法练习
│   ├── src/
│   │   └── main.rs
│   └── Cargo.toml
└── README.md               # 项目说明文档
```

## 编译与运行

### 构建项目

```bash
# 进入 Rust 项目目录
cd rust

# 构建所有模块
cargo build

# 构建特定模块
cd ans
cargo build
```

### 运行测试

```bash
# 运行所有测试
cargo test

# 运行特定测试
cargo test test_two_sum

# 运行特定文件的测试
cargo test --test main
```

### 代码格式化

```bash
# 格式化代码
cargo fmt

# 检查代码
cargo clippy
```

## 代码规范

- **命名规范**:
  - 函数名: `snake_case`
  - 结构体/枚举: `PascalCase`
  - 常量: `SCREAMING_SNAKE_CASE`
- **文档**: 使用 `///` 为公共 API 添加文档注释
- **测试**: 使用 `#[test]` 属性标记测试函数
- **文件组织**:
  - 每日一题: 按题目编号命名文件（如 `1615.rs`）
  - 面试经典 150 题: 按类型分类存放在对应子目录中
  - 经典算法题: 存放在 `main.rs` 文件中

## 注意事项

- 新增题目时，请确保代码注释完整，包含题目描述和解题思路
- 测试用例应包含基本测试用例和边界条件测试
- 保持代码风格一致，使用 `cargo fmt` 和 `cargo clippy` 确保代码质量

## 参考资料

- [Rust 官方文档](https://doc.rust-lang.org/)
- [LeetCode 官网](https://leetcode.com/)
- [Rust 编程实战](https://kaisery.github.io/trpl-zh-cn/)
