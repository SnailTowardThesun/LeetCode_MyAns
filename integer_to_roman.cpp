/*
 * Given an integer,convert it to a roman numeral
 * Input is guaranteed to be within the range from 1 to 3999
 * */

#include <iostream>
#include <string>
using namespace std;

class solution
{
public:
	void romanstr(string& roman, int num, char* symbol)
	{
		if(num == 0) return;
		else if(num < 3) roman.appand(num,*symbol);
		else if(num == 4)
		{
			roman.appand(1,*symbol);
			roman.appand(1,*(symbol+1));
		}
		else if(num < 8)
		{
			roman.appand(1,*(symbol+1));
			roman.appand(num-5,*symbol);
		}
		else if(num == 9)
		{
			roman.appand(1,*symbol);
			roman.appand(1,*(symbol+2));
		}
	}
	string intToRoman(int num)
	{
		char symbol[9] = {'I','V','X','L','C','D','M'};
		string roman = "";
		int scale = 1000;
		int p = 6;
		while(num)
		{
			int bit = num / scale;
			romanstr(roman,bit,symbol+p);
			scale /= 10;
			p-=2;
		}
		return roman;
	}
};
