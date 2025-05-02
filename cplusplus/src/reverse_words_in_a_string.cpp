/*
 Given an input string,reserve the string word by word
 For example.
 Given s = "the sky is blue"
 return "blue is sky the"
 */
#include <iostream>
using namespace std;

class solution
{
public:
	void reserveWords(string &s)
	{
		string ss;
		int i = s.length() - 1;
		while(i >= 0)
		{
			while(i >= 0 && s[i] == ' ') i--;
			if(i < 0) break;
			if(ss.length() != 0)
				ss.push_back(' ');
			string temp;
			for(;i >= 0 && s[i] != ' ';i--)
				temp.push_back(s[i]);
			reverse(temp.begin(),temp.end());
			ss.append(temp);
		}
		s = ss;
	}
};
