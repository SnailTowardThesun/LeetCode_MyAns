/*
 Determine whether an integer is a palindrome.Do this without extra space
 */

#include <iostream>
using namespace std;

class solution
{
public:
	bool isPalindrome(int x)
	{
		if(x < 0 || (x != 0 && (x%10 == 0)) return false;
		if(x == 0) return true;
		int rX = 0;
		while(rX < x)
		{
			rX = rX*10 + x %10;
			x = x/10;
		}
		return rX == x || rX/10==x;
	}
};

int main()
{
	return 0;
}
