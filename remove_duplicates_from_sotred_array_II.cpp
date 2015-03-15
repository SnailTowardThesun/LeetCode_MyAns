/*
 Follow up for "Remove Duplicates"
 What if duplicates are allowd at most twice?
 For example.
 Given sorted array A = [1,1,1,2,2,3,3]
 Your function should return length = 5,and A is now[1,1,2,2,3]
 */
class Solution
{
public:
	int removeDuplicates(int A[],int n)
	{
		if(A == NULL || n == 0) return 0;
		int startPostion = 0;
		bool isRepeated = false;
		for(int i = 0; i < n; i++)
		{
			if(A[i] != A[startPosition])
			{
				isRepeated = false;
				startPosition++;
				A[startPosition] = A[i];
			}
			else
			{
				if(isRepeated == false)
				{
					startPosition++;
					A[startPosition] = A[i];
					isRepeated = true;
				}
			}
		}
		return startPosition + 1;
	}
};
