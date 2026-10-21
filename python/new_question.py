"""新题脚手架：从 questions/_template.py 生成题目文件。

用法（在 python/ 目录下执行）：
    uv run python new_question.py 219 "存在重复元素 II" [url-slug]
"""

import sys
from pathlib import Path

QUESTIONS_DIR = Path(__file__).parent / "questions"
TEMPLATE = QUESTIONS_DIR / "_template.py"


def main() -> None:
    if len(sys.argv) < 2:
        sys.exit("用法: uv run python new_question.py <题号> [标题] [url-slug]")

    num = sys.argv[1]
    if not num.isdigit():
        sys.exit(f"题号必须是纯数字，收到: {num!r}")

    title = sys.argv[2] if len(sys.argv) > 2 else "TODO-补充标题"
    slug = sys.argv[3] if len(sys.argv) > 3 else "TODO-补充slug"

    target = QUESTIONS_DIR / f"{num}.py"
    if target.exists():
        sys.exit(f"已存在 {target}，不覆盖")

    content = TEMPLATE.read_text(encoding="utf-8")
    content = content.replace("{{NUM}}", num).replace("{{TITLE}}", title).replace("{{SLUG}}", slug)
    target.write_text(content, encoding="utf-8")
    print(f"已生成 {target}")
    print(f"下一步: 1) 补充注释  2) 实现函数与测试  3) uv run python questions/{num}.py 验证")


if __name__ == "__main__":
    main()
