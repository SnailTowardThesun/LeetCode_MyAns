/*
 Given a string,find the length of the longest substring without repeating characters.For example,the longest substring without repeating lettes for "abcabcbb" is "abc", which the length is 3.For "bbbb" the longest substring is "b",with the length of 1
 */

#include <iostream>
#include <string>
using namespace std;

class solution
{
public:
	int lengthofLongestSubString(string s)
	{
		int result = 0;
		int locs[256];
		memset(locs,-1,sizeof(locs));
		int idx = -1,max = 0;
		for(int i = 0; i < s.size(); i++)
		{
			if(locs[i] > idx)
				idx = locs[s[i]];
			if(i - idx > max)
				max = i - idx;
			locs[s[i]]=i;
		}
		return max;
	}
};

