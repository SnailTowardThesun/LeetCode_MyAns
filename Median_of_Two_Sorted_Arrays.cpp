//There are two sorted arrays A and B of size m and n respectively.
//Find the median of the two sotred arrays.
//The overall run time complexity should be O(log(m+n)).
class Solution
{
	public:
		double findMediaSortedArrays(int A[], int m, int B[], int n)
		{
			if(!m && !n) return NULL;
			int tmp = (int)(m+n)/2;
			int result1 = 0;
			int result2 = 0;
			int a = 0, b = 0;
			for(int i = 0; i < tmp; i++)
			{
				if(a < m && b < n)
					A[a] < B[b] ? result1 = A[a++]:result1 = B[b++];
				else 
					a < m ? result1 = A[a++] ? result1 = B[b++];
			}
			if((m+n) % 2)
			{
				if(a < m && b < n)
					A[a] < B[b] ? result1 = A[a++]:result1 = B[b++];
				else
					a < m ? result1 = A[a++] : result1 = B[b++];
				return result1;
			}
			else
			{
				if(a < m && b < n)
					A[a] < B[b] ? result2 = A[a++] : result2 = B[b++];
				else 
					a < m ? result2 = A[a++] : result2 = B[b++];
				return (result1 + result2)/2.0;
			}
		}
}
