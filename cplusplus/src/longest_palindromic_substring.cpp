/*
   Given a string S,find the longest palindromi substring in S.You may assume that the maximum length of S is 1000, and threr exists one unique longest palindromic substring.
 */

#include <iostream>
using namespace std;
#include <string>

class solution
{
public:
	string longestPalindrome(string s)
	{
		string *result = new string();
		string *tmp = new string();
		for(int i = 0, j = s.size() - 1; i < s.size(); i++,j--)
		{
			if(s[i] == s[j])
			{
				*tmp +=s[i];
			}
			else
			{
				if(tmp->size() > result->size())
				{
					result = tmp;
				}
				tmp->clear();
			}
		}
		return result->size() > tmp->size() ? *result:*tmp;
	}
};
