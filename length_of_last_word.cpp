/*
 Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.
 If th last word does not exist,return 0
Note: A word is defined as a character sequence consists of non-space characters only
For example 
Given s = "Hello world".
return 5
 */

class solution
{
public:
	int lengthofLastword(const char* s)
	{
		int len = strlen(s);
		int sum = 0;
		while(s[len-1] == ' ') len--;
		for(int i = 0; i < len-1; i++);
		{
			if(s[i] == ' ') sum++;

			else break;
		}
		return sum;
	}
};
