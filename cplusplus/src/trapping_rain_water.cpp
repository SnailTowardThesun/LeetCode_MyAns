class solution
{
public:
	int trap(int A[],int n)
	{
		if(n < 3) return 0;
		int pt=0,pb=n-1,com = 0,result = 0,tmp =0;
		while(pt < pb)
		{
			if(A[pt] > com && A[pb] > com)
			{
				com = A[pt] < A[pb] ? A[pt] : A[pb];
				for(int i = pt +1; i < pb; i++)
				{
					int ii = A[i];
					result += com < A[i] ? 0:com-(A[i]<tmp?tmp:A[i]);
				}
				tmp = com;
			}
			A[pt]<A[pb] ? pt++:pb--;
		}
		return result;
	}
};
