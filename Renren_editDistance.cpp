#include<iostream>
#include<cstring>
#include<vector>
using namespace std;


int editDistance(char *A, char *B)
{
	int n = strlen(A);
	int m = strlen(B);
	if(n==0)
		return m;
	if(m==0)
		return n;
	vector<vector<int> > dp(n+1, vector<int>(m+1, 0));
	for(int i=0; i<=n; ++i)
		dp[i][0] = i;
	for(int j=0; j<=m; ++j)
		dp[0][j] = j;
	for(int i=1; i<=n; ++i)
	{
		for(int j=1; j<=m; ++j)
		{
			if(A[i-1]==B[j-1])
				dp[i][j] = dp[i-1][j-1];
			else
			{
				dp[i][j] = dp[i-1][j-1]+1;	//替换一个字符, 如果替换的代价为2倍，那么这里改为+2
				int tt = min(dp[i-1][j], dp[i][j-1])+1;	//删除或插入一个字符
				dp[i][j] = min(dp[i][j], tt);
			}
		}
	}
	return dp[n][m];
}


//人人2015浙江大学笔试题第2题：字符串的编辑距离
int main(void)
{
	char *A = "dabc";
	char *B = "defc";

	int ans = editDistance(A, B);

	return 0;
}

