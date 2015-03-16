/*
 Given numRows, generate the first numRows of Pascal's triangle.
 For example, given numRows = 5
 return
 [
 [1]
 [1,1]
 [1,2,1]
 [1,3,3,1]
 [1,4,6,4,1]
 ]
 */

class solution
{
public:
	vector<vector<int>> generate(int numRows)
	{
		if(numRows == 0) return vector<vector<int>>();
		vector<int> level;
		vector<vector<int>> ret;
		for(int i = 1; i <= numRows; i++)
		{
			int k = (int)level.size();
			for(int j = k-1; j >= 1; j--)
				level[j] +=level[j-1];
			level.push_back(1);
			ret.push_back(level);
		}
		return ret;
	}
};
