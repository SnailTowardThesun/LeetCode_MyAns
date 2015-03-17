/*
 Given an array of integers, find two numbers such that they add up to a specific target number.
 The function twoSum should return indices of the tow numbers such that they add up to the target,where index1 must be less than index2,Please note that your returned answers(both index1 and index2) are not zero-based.
 You may assume that each input would have exactly one solution.
Input:numbers = {2,7,11,15},target = 9
Output: index1 = 1, index2 = 2
 */

#include <iostream>
#include <vector>
using namespace std;

class solution
{
public:
	vector<int> twosum(vector<int> &number,int target)
	{
		vector<int> result;
		int index1,index2;
		for(int i = 0; i < number.size(); i++)
		{
			index1 = number[i];
			for(int j = i+1; j < number.size(); j++)
			{
				if(index1 + number[j] == target)
				{
					result.push_back(index1 > number[j] ? number[j] : index1);
					result.push_back(index1 == result[0] ? number[j] : index1);
				}

			}
		}
		return result;
	}
};

int main()
{
	return 0;
}
