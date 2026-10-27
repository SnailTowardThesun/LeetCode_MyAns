# CLAUDE.md

## Project

LeetCode 算法题解集合，包含 C++、Rust 和 Python 三种语言的实现。本项目用于记录和练习 LeetCode 算法题目的个人解答。

- **C++ 部分**: 使用 C++20 标准，包含经典算法题解和每日一题
- **Rust 部分**: 使用 Rust 最新稳定版，练习 Rust 语言特性和算法实现
- **Python 部分**: 使用 uv 管理环境，pytest 测试，ruff 格式化检查
- **测试框架**: Google Test (C++)、内置测试 (Rust) 和 pytest (Python)

## Key Directories

```
.
├── cplusplus/              # C++ 算法题解（CMake + Google Test）
│   ├── questions/         # 每日一题（题号.cpp，测试 TEST(Daily, 题号) 写在同文件）
│   ├── top150/            # 面试经典 150 题（top150_题号.cpp，按分类分子目录）
│   ├── leetcode_common.h  # 通用 ListNode/TreeNode 定义（唯一来源）
│   └── CMakeLists.txt     # CMake 构建配置（全部 .cpp 链接进同一个 tests）
├── rust/                  # Rust 算法题解（根包 ans + workspace）
│   ├── questions/         # 每日一题（题号.rs）+ _template.rs 模板
│   ├── leetcode_common.rs # 通用数据结构 ListNode/TreeNode
│   └── baseAlgorithm/     # 基础算法练习（src/main.rs）
├── python/                # Python 算法题解（uv 管理）
│   ├── leetcode_common/   # 通用数据结构 ListNode/TreeNode
│   ├── questions/         # 每日一题（题号.py）+ _template.py 模板
│   └── top150/            # 面试经典 150 题（top150_题号.py）
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

### Python 项目

```bash
# 进入 Python 项目目录
cd python

# 初始化/更新环境（首次必跑）
uv sync

# 运行测试
uv run pytest

# 单独运行一题
uv run python questions/1.py

# 格式化与检查
uv run ruff format .
uv run ruff check .

# 从模板生成新题文件
uv run python new_question.py 219 "存在重复元素 II"
```

## Code Style

### C++ 代码规范

- **标准**: C++20
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

- **C++ 源文件**: 每日一题一个 `.cpp` 文件，按题号命名（如 `2089.cpp`）；Top150 命名为 `top150_题号.cpp`，放入 top150/ 对应分类子目录
- **Rust 模块**: 按题号命名 `.rs` 文件（如 `2389.rs`），放在 `questions/`（rust/ 根目录）
- **测试文件**: C++ 测试写在题解同文件（`TEST(Daily, 题号)`），Rust/Python 测试与源码放在一起

### 代码结构

- **类定义**: C++ 使用 `class Solution`，包含公有方法
- **注释**: 在文件开头添加题目描述和示例
- **测试用例**: 包含基本测试用例和边界条件测试

### 提交规范

- 每日一题使用题目编号命名文件 (如 `2089.cpp`)
- Top150 使用 `top150_题号` 命名并按分类放入 `cplusplus/top150/` 子目录
- **文档文件命名**: 只能使用 `README.md`，不能使用 `readme.md` 等其他形式
- **提交前必须检查**: 新增题目的注释内容必须完整
  - 必须包含题目内容描述
  - 必须包含解题思路说明
  - 必须使用中文编写注释
  - 如缺少以上内容，必须在提交前补充完整

## Avoid

- 不要使用 `using namespace std;` 在头文件中
- 避免使用裸指针，优先使用智能指针
- 不要提交编译生成的文件 (已配置 `.gitignore`)
- 避免代码中出现硬编码的魔法数字
- 不要使用已过时的 C++ 特性

## Build Configuration

### C++ CMake 配置

- **最低版本**: CMake 3.28
- **编译选项**: `-g -std=c++20 -Wall`
- **测试框架**: Google Test (通过 FetchContent 自动下载)

### Rust Cargo 配置

- **工作区**: 根包 `ans`（题解主模块，位于 rust/ 根目录）+ 成员 `baseAlgorithm`
- **依赖**: 标准库为主，必要时添加外部 crate

## Tips

- C++ 代码使用 CLion 或支持 `.clang-format` 的编辑器进行格式化
- Rust 代码使用 `cargo fmt` 和 `cargo clippy` 保持代码质量
- 新增题目时，参考现有代码的风格和结构
- 测试失败时，检查边界条件和特殊情况处理
