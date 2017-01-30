/*
 Reverse digits of an integer.
Example1: x = 123,return 321
Example2: x = -123, return -321
 */

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string>
using namespace std;

class solution
{
public:
	int reverse(int x)
	{
		long num = abs((long)x);
		long new_num = 0;
		while(num)
		{
			new_num = new_num * 10 + num%10;
			num /= 10;
		}
		if(new_num > INT_MAX) return 0;
		return (x < 0 ? 0-new_num:new_num);
	}
};
