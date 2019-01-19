#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

class Solution {
public:
	Solution() = default;

	virtual ~Solution() = default;
public:
	bool isMatch(std::string s, std::string p) {
		// 均为空，返回true
		if (s.empty() && p.empty()) {
			return true;
		}

		// 只有p为空，返回false
		if (p.empty()) {
			return false;
		}

		auto s_start = 0;
		auto s_current = 0;

		auto p_start = -1;
		auto p_current = 0;
		/*
			以s为基准进行遍历
		*/
		while (s_current < s.size()) {
			// 如果当前位置字符相等，包括p为?的情况，则移动到下一个位置
			if (s[s_current] == p[p_current] || p[p_current] == '?') {
				s_current++;
				p_current++;
			}
			// 如果p字符串当前位置为*，则重新设定开始位置
			else if (p[p_current] == '*') {
				p_start = p_current++;
				s_start = s_current;
			}
			// 如果p_start不为-1，则表示了前面存在*号，直接跳过不相等的字符
			else if (p_start != -1) {
				p_current = p_start + 1;
				s_current = ++s_start;
			}
			else {
				return false;
			}

		}

		// p以*号结尾
		while (p[p_current] == '*') {
			p_current++;
		}

		// 未结束匹配
		if (p_current < p.size()) {
			return false;
		}

		return true;
	}
};

int main()
{
	Solution solution;
	std::string s = "aaaa";
	std::string p = "***a";

	auto result = solution.isMatch(s, p);

	if (result) {
		std::cout << "result is true" << std::endl;
	}
	else {
		std::cout << "result is false" << std::endl;
	}

	getchar();
	return 0;
}
