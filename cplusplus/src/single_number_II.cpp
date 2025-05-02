/*
 Given an array of integers,every element appears three times except for one.Find that sigle one.
 Note:
 Your algorithm should have a linear runtime complexity.Could you implement it without using extra memroy?
 */

class solution
{
public:
	int singleNumber(int A[],int n)
	{
		int x[32] = {0};
		for(int i = 0; i < n; i++)
			for(int j = 0; j < 32; j++)
			{
				x[j] += (A[i] >> j) &(1);
				x[j] %= 3;
			}
		int res = 0;
		for(int i = 0; i < 32; i++)
			res +=(x[i] << i);
		return res;
	}
};
