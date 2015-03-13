/*
 Given an unsorted integer array, find the first missing positive integer
 For example.
 Given[1,2,0] return 3
 and [3.4.-1.1] return 2.
 Your algorithm should run in O(n) time and used constant space
 */

class solution
{
public:
	int firstMissingPositive(int A[],int n)
	{
		for(int i = 0,tmp = -1; i < n; i++)
		{
			while(A[i] - 1 >=0 && A[i] - 1 < n && A[i] - 1 !=i)
			{
				swap(A,i,A[i]-1);
				if(A[i] == tmp) break;
				else tmp = A[i];
			}
		}
		for(int i = 0; i < n; i++)
		{
			if(A[i] - 1 != i) return i+1;
		}
		return n+1;
	}

	void swap(int A[],int indx1, int indx2)
	{
		A[indx1] ^=A[indx2];
		A[indx2] ^=A[indx1];
		A[indx1] ^=A[indx2];
	}
};
