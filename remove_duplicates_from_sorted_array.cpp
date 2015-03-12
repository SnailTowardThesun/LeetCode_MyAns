/*
 Given a sorted array,remove the duplicates in place such that each elemet appear only once and return the new length.
 Do not allocate extra space for another array,you must do this in place with constant memory.
 For example 
 Given input array A = [1,1,2],
 Your fuction should return length = 2,and A is now [1,2]
 */

class Solution 
{
public:
	int removeDeplicate(int A[],int n)
	{
		if(n <= 1) return n;
		int i = 0,j = 1;
		while(j < n)
		{
			if(A[i] == A[j]) j++;
			else A[++i] = A[j++];
		}
		return i+1;
	}
}
