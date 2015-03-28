/*
 *Given n non-negative integers a1,a2.......an,where each represents a point at corrdinate(i,a).n vertical lines are drawn such that the two endpoints of line i is at (i,a) and (i,0).Find two lines,which together wit x-axis forms a container,such that the contaier contains the most water.
Note:You may not slant the container
 * */

#include <iostream>
#include <vector>
using namespace std;
class solution
{
public:
	int maxArea(vector<int> &height)
	{
		int i = 0;
		int j = height.size() - 1;
		int result = 0;
		while(i < j)
		{
			int area = (j - i)*min(height[i],height[j]);
			result = max(result,area);
			if(height[i] <= height[j] i++;
			else j--;
		}
		return result;
	}
};
