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
		// ��Ϊ�գ�����true
		if (s.empty() && p.empty()) {
			return true;
		}

		// ֻ��pΪ�գ�����false
		if (p.empty()) {
			return false;
		}

		auto s_start = 0;
		auto s_current = 0;

		auto p_start = -1;
		auto p_current = 0;
		/*
			��sΪ��׼���б���
		*/
		while (s_current < s.size()) {
			// �����ǰλ���ַ���ȣ�����pΪ?����������ƶ�����һ��λ��
			if (s[s_current] == p[p_current] || p[p_current] == '?') {
				s_current++;
				p_current++;
			}
			// ���p�ַ�����ǰλ��Ϊ*���������趨��ʼλ��
			else if (p[p_current] == '*') {
				p_start = p_current++;
				s_start = s_current;
			}
			// ���p_start��Ϊ-1�����ʾ��ǰ�����*�ţ�ֱ����������ȵ��ַ�
			else if (p_start != -1) {
				p_current = p_start + 1;
				s_current = ++s_start;
			}
			else {
				return false;
			}

		}

		// p��*�Ž�β
		while (p[p_current] == '*') {
			p_current++;
		}

		// δ����ƥ��
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
