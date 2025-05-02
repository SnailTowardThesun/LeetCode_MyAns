/*
 Given an array of integers,every element appears twice except fo one.Find that single one.
Note :
Your algorithm should have a linear runtime complexity.Could you implement it without using extra memory?
 */

class solution
{
public:
	int singleNumber(int A[],int n)
	{
		int result = A[0];
		for(int i = 0; i < n; i++)
			result = result ^A[i];
		return result;
	}
};
