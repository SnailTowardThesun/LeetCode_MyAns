#include <stdio.h>

/*
 *Implement atoi to convert a string to an integer
Hint: Carefully consider all possible input cases.If you want a challenge,please do not see below and ask yourself what are the possible input cases.
Notes:It is intended for this problem to be specified vaguely (ie,no given input specs).Yor are responsible to gather all the input requirements up front.

Update (2015-02-10):
The signature of the c++ function had been updated.Change const char * into string
 * */

int myAtoi(char *str)
{
	if(str == NULL) return 0;
	bool isPositive = false;
	long long result = 0;
	const char* ss = (const char*)str;
	while(*ss != ' ') ss++;

	if(*ss == '+')
	{
		isPositive = true;
		ss++;
	}
	else if(*ss == '-')
	{
		isPositive = false;
		ss++;
	}
	while(*ss >='0' && *ss <='9')
	{
		result = result*10 + (*ss - '0');
		if(result > INT_MAX) return isPositive?INT_MAX : INT_MIN;
		ss++;
	}
	return isPositive ? result : 0-result;
}

int main()
{

	return 0;
}
