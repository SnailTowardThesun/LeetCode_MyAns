# CLAUDE.md

## Project

LeetCode 算法题解集合，包含 C++ 和 Rust 两种语言的实现。本项目用于记录和练习 LeetCode 算法题目的个人解答。

- **C++ 部分**: 使用 C++17 标准，包含经典算法题解和每日一题
- **Rust 部分**: 使用 Rust 最新稳定版，练习 Rust 语言特性和算法实现
- **测试框架**: Google Test (C++) 和内置测试 (Rust)

## Key Directories

```
.
├── cplusplus/              # C++ 算法题解
│   ├── src/               # 经典算法题源代码
│   ├── tests/             # 每日一题测试代码
│   ├── top150/            # 面试经典 150 题
│   └── CMakeLists.txt     # CMake 构建配置
├── rust/                  # Rust 算法题解
│   ├── ans/               # 主答案模块
│   └── baseAlgorithm/     # 基础算法练习
├── trunk/                 # 其他练习代码
└── .clang-format          # C++ 代码格式化配置
```

## Commands

### C++ 项目

```bash
# 进入 C++ 项目目录
cd cplusplus

# 创建构建目录并编译
mkdir -p build && cd build
cmake ..
make

# 运行测试
./tests

# 或者使用 ctest
ctest --verbose
```

### Rust 项目

```bash
# 进入 Rust 项目目录
cd rust

# 构建项目
cargo build

# 运行测试
cargo test

# 运行特定测试
cargo test test_two_sum

# 格式化代码
cargo fmt

# 检查代码
cargo clippy
```

## Code Style

### C++ 代码规范

- **标准**: C++17
- **缩进**: 4 个空格，不使用 Tab
- **行宽限制**: 120 字符
- **格式**: 遵循 Google C++ Style (通过 `.clang-format` 配置)
- **命名规范**:
  - 类名: `PascalCase` (如 `Solution`)
  - 函数名: `snake_case` (如 `two_sum`)
  - 变量名: `snake_case` (如 `max_length`)
- **头文件**: 使用 `#pragma once` 或标准头文件保护

### Rust 代码规范

- **标准**: 最新稳定版 Rust
- **缩进**: 4 个空格
- **命名规范**:
  - 函数名: `snake_case`
  - 结构体/枚举: `PascalCase`
  - 常量: `SCREAMING_SNAKE_CASE`
- **文档**: 使用 `///` 为公共 API 添加文档注释
- **测试**: 使用 `#[test]` 属性标记测试函数

## Conventions

### 文件组织

- **C++ 源文件**: 每个算法题一个 `.cpp` 文件，文件名使用小写和下划线
- **Rust 模块**: 按题目类型分模块 (`daily.rs`, `offer.rs`)
- **测试文件**: C++ 测试放在 `tests/` 目录，Rust 测试与源码放在一起

### 代码结构

- **类定义**: C++ 使用 `class Solution`，包含公有方法
- **注释**: 在文件开头添加题目描述和示例
- **测试用例**: 包含基本测试用例和边界条件测试

### 提交规范

- 每日一题使用题目编号命名文件 (如 `3643.cpp`)
- 经典题目使用描述性名称 (如 `two_sum.cpp`)

## Avoid

- 不要使用 `using namespace std;` 在头文件中
- 避免使用裸指针，优先使用智能指针
- 不要提交编译生成的文件 (已配置 `.gitignore`)
- 避免代码中出现硬编码的魔法数字
- 不要使用已过时的 C++ 特性

## Build Configuration

### C++ CMake 配置

- **最低版本**: CMake 3.31
- **编译选项**: `-g -std=c++17 -Wall`
- **测试框架**: Google Test (通过 FetchContent 自动下载)

### Rust Cargo 配置

- **工作区**: 包含 `ans` 和 `baseAlgorithm` 两个成员
- **依赖**: 标准库为主，必要时添加外部 crate

## Tips

- C++ 代码使用 CLion 或支持 `.clang-format` 的编辑器进行格式化
- Rust 代码使用 `cargo fmt` 和 `cargo clippy` 保持代码质量
- 新增题目时，参考现有代码的风格和结构
- 测试失败时，检查边界条件和特殊情况处理
