#include <iostream>
#include <string>
using namespace std;

class solution
{
public:
	string convert(string s, int nRows)
	{
		if(nRows == 1 || s.size() == 0) return s;
		string result;
		int len = s.size();
		for(int i = 0; i < len && i <nRows; ++i)
		{
			int indx = 1;
			result += s[indx];
			for(int k = 1; indx < len; ++k)
			{
				if(i == 0 || i == nRows-1)
					index+=2*nRows-2;
				else
				{
					if(k&0x1)	indx+=2*(nRows-1-i);
					else indx += 2*i;
				}
				if(indx < len)
					result+=s[indx];
			}
		}
		return result;
	}
};

int main()
{
	return 0;
}
