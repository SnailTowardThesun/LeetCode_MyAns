# LeetCode Python 题解

Python 题解子项目，与 `cplusplus/`、`rust/` 平级，使用 **uv** 管理环境与依赖，**pytest** 跑测试，**ruff** 做格式化与检查。

## 目录结构

```
python/
├── pyproject.toml           # uv 项目配置（含 pytest / ruff 规则）
├── uv.lock                  # 依赖锁文件（提交到 git）
├── .python-version          # 固定 Python 版本
├── leetcode_common/         # 通用数据结构 ListNode / TreeNode 及构造工具（对齐 leetcode_common.h）
├── new_question.py          # 新题脚手架
├── questions/               # 每日一题，按题号命名（如 1.py）
│   └── _template.py         # 新题模板（pytest 不收集）
└── tests/                   # 框架自检
```

## 常用命令（在 python/ 目录下执行）

```bash
uv sync                        # 初始化/更新环境（首次必跑，自动创建 .venv）
uv run python new_question.py 219 "存在重复元素 II"   # 从模板生成新题文件
uv run python questions/219.py                        # 单独运行一题
uv run pytest                                         # 运行全部测试
uv run ruff format .                                  # 格式化
uv run ruff check .                                   # 静态检查
```

## 约定

- 文件命名与 C++ 一致：每日一题 `题号.py`；文件头注释使用与 `1.cpp` 相同的 `@题目描述` / `@示例` / `@解题思路` 标签（中文）
- `Solution` 类函数签名保持 LeetCode 官方 camelCase（如 `twoSum`），便于直接提交
- 链表/二叉树结构一律 `from leetcode_common import ListNode, TreeNode, ...`，禁止在题解中重复定义
- 题解内写 `test_solution()` 函数：既被 pytest 收集，也支持 `python 题号.py` 直接运行
- Turborepo 接入：上层目录 `npm run build/test/lint` 已包含本项目
