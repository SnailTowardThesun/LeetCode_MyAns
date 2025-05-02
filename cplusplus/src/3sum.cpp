/*MIT License

Copyright (c) 2016 ME_Kun_Han

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void problem()
{
	cout << "Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero." << endl;
	cout << "Note: The solution set must not contain duplicate triplets." << endl;
	cout << "For example given array S = [-1, 0 ,1, 2, -1, -4]," << endl;
	cout << "A solution set is :" << endl;
	cout << "[" << endl;
	cout << "\t" << "[-1, 0, 1]," << endl;
	cout << "\t" << "[-1, -1, 2]" << endl;
	cout << "]" << endl;
}

class Solution
{
public:
	vector<vector<int>> threeSum(vector<int>& nums)
	{
		vector<vector<int>> res;
		std::sort(nums.begin(), nums.end());

		for (int k = 0; k < nums.size(); ++k) {
			if (nums[k] > 0) {
				break;
			}

			if (k > 0 && nums[k] == nums[k - 1]) {
				continue;
			}

			int target = 0 - nums[k];
			int i = k + 1, j = nums.size() - 1;
			while (i < j) {
				if (nums[i] + nums[j] == target) {
					res.push_back({ nums[k], nums[i], nums[j] });
					while (i < j && nums[i] == nums[i + 1]) ++i;
					while (i < j && nums[j] == nums[j - 1]) --j;
					++i; --j;
				}
				else if (nums[i] + nums[j] < target) {
					++i;
				}
				else {
					--j;
				}
			}
		}
		return res;
	}

};

int test(int argc, char* argvp[])
{
	problem();
	vector<int> example;

	example.push_back(-1);
	example.push_back(0);
	example.push_back(1);
	example.push_back(2);
	example.push_back(-1);
	example.push_back(-4);

	Solution s;
	auto ret = s.threeSum(example);
	for (auto i : ret)
	{
		for (auto j : i)
		{
			cout << j << " ";
		}
		cout << endl;
	}
	return 0;
}
