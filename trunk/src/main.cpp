#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



int main()
{
	cout << "the answer of leetcode" << endl;

	vector<int> nums = {1,1,-1,-1,3};

	Solution s;

	cout << s.threeSumClosest(nums, -1);


	getchar();
	return 0;
}
