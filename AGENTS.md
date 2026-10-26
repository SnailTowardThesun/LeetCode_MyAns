# AGENTS.md — LeetCode_MyAns（算法题解）

本仓库只包含**算法题解**一个项目，C++ / Rust / Python 三种实现。与技术博客（SnailTowardThesun.github.io）的联动发布流程见上层工作区 `AGENTS.md` 及 `.agents/skills/` 技能（`leetcode_publish`、`leetcode-comment-blog-batch`）。

---

## 核心原则

- **Logic over Tokens** — 优先生成逻辑严密的短代码，而非冗长的 AI 生成片段
- **最小变更** — 只修改必要文件，不引入无关改动
- **注释即文档** — 新题必须包含完整中文注释，缺一不可
- **本地验证** — 提交前必须通过构建和测试验证

---

## 项目结构

```
LeetCode_MyAns/
├── cplusplus/                     # C++20 题解（CMake + Google Test）
│   ├── questions/                 # 每日一题（题号.cpp，如 1.cpp）
│   ├── top150/                    # 面试经典 150 题（top150_题号.cpp，按分类分子目录）
│   │   ├── array/  binary_search/  binary_tree/  double_pointer/  hash/
│   │   └── interval/  sliding_windows/  stack/  string/
│   ├── leetcode_common.h          # 通用 ListNode/TreeNode 定义（唯一来源）
│   ├── CMakeLists.txt             # 全部 .cpp 链接进同一个 tests 可执行文件
│   └── README.md
├── rust/                          # Rust 题解（Cargo Workspace）
│   ├── ans/                       # 主答案模块（questions/ 内按题号命名 .rs）
│   ├── baseAlgorithm/             # 基础算法练习（src/main.rs）
│   └── Cargo.toml                 # Workspace 配置（ans + baseAlgorithm）
├── python/                        # Python 题解（uv + pytest + ruff）
│   ├── leetcode_common/           # 通用数据结构 ListNode/TreeNode 及构造工具
│   ├── questions/                 # 每日一题（题号.py）+ _template.py 模板
│   ├── top150/                    # 面试经典 150 题（top150_题号.py）
│   ├── new_question.py            # 新题脚手架
│   └── pyproject.toml             # uv 项目配置（pytest/ruff 规则）
├── .clang-format                  # C++ 格式化配置（Google 风格）
├── LeetCode_MyAns.code-workspace  # VSCode 工作区
├── package.json / turbo.json      # Turborepo 顶层配置
└── README.md
```

---

## 构建与测试命令

```bash
# === Turborepo 顶层（在 LeetCode_MyAns/ 下执行）===
npm install                          # 首次必跑（安装 turbo，node_modules 不入库）
npm run build                        # 构建所有子项目
npm run test                         # 运行所有测试
npm run lint                         # 格式化/检查所有子项目

# === C++ 项目（在 cplusplus/ 下执行）===
cmake -B build && cmake --build build   # 构建（build/ 已 gitignore）
ctest --test-dir build                  # 运行测试
./build/tests                           # 直接运行测试可执行文件
find questions top150 -name '*.cpp' -exec clang-format -i {} +   # 格式化

# === Rust 项目（在 rust/ 下执行）===
cargo build                        # 构建
cargo test                         # 运行测试
cargo test test_two_sum            # 运行指定测试
cargo fmt                          # 格式化代码
cargo clippy                       # 代码检查

# === Python 项目（在 python/ 下执行）===
uv sync                            # 初始化/更新环境（首次必跑）
uv run pytest                      # 运行全部测试
uv run python questions/1.py       # 单独运行一题
uv run ruff format .               # 格式化代码
uv run ruff check .                # 代码检查
uv run python new_question.py 219 "存在重复元素 II"   # 从模板生成新题文件
```

---

## C++ 编码规范

- **标准**: C++20，编译标志 `-g -std=c++20 -Wall`
- **CMake**: 最低版本 3.28，通过 FetchContent 自动下载 Google Test
- **缩进**: 4 空格，不使用 Tab（遵循 `.clang-format` 的 Google 风格）
- **行宽**: 120 字符
- **匿名命名空间**: Solution/题目类必须包在 `namespace { ... }` 内——CMake 将全部 .cpp 链接进同一个 tests 可执行文件，内部链接可避免同名类 ODR/符号冲突
- **通用数据结构**: `ListNode`/`TreeNode` 统一 `#include "leetcode_common.h"`，禁止在 .cpp 中重复定义
- **命名**:
  - 类名: `PascalCase`（如 `Solution`）
  - 函数/变量: `snake_case`（如 `two_sum`, `max_length`）
- **文件命名**:
  - 每日一题: `题号.cpp`（如 `1.cpp`, `2089.cpp`）
  - Top150: `top150_题号.cpp`（如 `top150_106.cpp`），放入 top150/ 对应分类子目录
- **注释要求**（文件头部，中文）:
  - `@题目描述`: 完整题目内容
  - `@示例`: 输入输出示例
  - `@解题思路`: 算法思路、步骤、复杂度分析
- **测试**: 使用 `TEST(Daily, 题号)` 格式，包含基本和边界用例

### C++ 避免事项

- 不要在头文件中使用 `using namespace std;`
- 避免裸指针，优先使用智能指针
- 不要提交编译产物（`.gitignore` 已配置）
- 避免硬编码魔法数字
- 不要使用已废弃的 C++ 特性

---

## Rust 编码规范

- **标准**: 最新稳定版 Rust
- **缩进**: 4 空格
- **命名**:
  - 函数/变量: `snake_case`
  - 结构体/枚举: `PascalCase`
  - 常量: `SCREAMING_SNAKE_CASE`
- **文件组织**: 按题号命名 `.rs` 文件（如 `2389.rs`），放在 `ans/questions/`
- **测试**: 使用 `#[test]` 属性，测试函数与源码放在同一文件
- **文档**: 使用 `///` 为公共 API 添加文档注释
- **Workspace**: `ans` 和 `baseAlgorithm` 两个成员；`Cargo.lock` 需提交（含二进制 crate，锁定依赖保证构建可复现）

---

## Python 编码规范

- **版本/管理**: uv 管理，Python >= 3.12（`.python-version` 固定），行宽 120、4 空格缩进
- **命名**:
  - 题解函数签名保持 LeetCode 官方 camelCase（如 `twoSum`），便于直接提交
  - 辅助函数/变量: `snake_case`
- **文件组织**: 每日一题按题号命名 `.py`（如 `1.py`），放在 `questions/`
- **通用数据结构**: `ListNode`/`TreeNode` 统一 `from leetcode_common import ListNode, TreeNode, build_list, ...`，禁止在题解中重复定义
- **注释要求**: 文件头 docstring 使用与 C++ 相同标签（`@题目描述`/`@示例`/`@解题思路` + 复杂度），中文
- **测试**: 每题写 `test_solution()` 函数——既被 pytest 收集，也支持 `uv run python questions/题号.py` 直接运行；新题可用 `new_question.py` 脚手架生成

---

## 新题提交 Checklist

- [ ] 代码注释完整（题目描述 + 解题思路 + 示例，中文）
- [ ] 测试用例包含基本场景和边界条件
- [ ] C++ 代码通过 `clang-format` 格式化
- [ ] Rust 代码通过 `cargo fmt` 和 `cargo clippy` 检查
- [ ] Python 代码通过 `uv run ruff format .` 和 `uv run ruff check .` 检查
- [ ] 构建通过且测试全部通过
- [ ] 文档文件命名为 `README.md`（不是 `readme.md`）

---

## 提交规范

- **提交信息**: 简洁明了，包含项目标识前缀，如 `[algo] Add solution for LeetCode 61`
- **分支策略**: 直接在主分支提交（个人仓库）
- **文件命名**: 只使用 `README.md`（大写），不使用 `readme.md`

---

*算法题解仓库 Agent 指南。跨项目（博客发布）协作见上层工作区 AGENTS.md。*
