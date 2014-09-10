#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

typedef unsigned long long ull;

const int N = 1009;

int A[N][2];	//因为是二叉树，因此不必使用数组
int B[N][2];
int valueA[N];
int valueB[N];

bool dfs(int a, int b)
{
	if(b==0)	//为0表示不存在该节点
		return true;

	//若要是子树, 则必须左右子树一一对应
	if(a==0 || valueA[a]!=valueB[b] || dfs(A[a][0], B[b][0])==false || dfs(A[a][1], B[b][1])==false)
		return false;
	
	return true;
}

bool is_Sub(int n)
{
	for(int i=1; i<=n; ++i)
	{
		if(valueA[i]==valueB[1])	//默认1为B树的根节点
		{
			if(dfs(i,1))
				return true;
		}
	}
	return false;
}


//测试链接：http://ac.jobdu.com/problem.php?pid=1520
int main(void)
{
	int i,j,n,m,k;
	int tt;

	while(scanf("%d %d", &n, &m)!=EOF)
	{
		memset(A, 0, sizeof(A));
		memset(B, 0, sizeof(B));

		for(i=1; i<=n; ++i)
			scanf("%d", &valueA[i]);
		for(i=1; i<=n; ++i)
		{
			scanf("%d", &k);
			for(j=0; j<k; ++j)
			{
				scanf("%d", &tt);
				A[i][j] = tt;
			}
		}

		for(i=1; i<=m; ++i)
			scanf("%d", &valueB[i]);
		for(i=1; i<=m; ++i)
		{
			scanf("%d", &k);
			for(j=0; j<k; ++j)
			{
				scanf("%d", &tt);
				B[i][j] = tt;
			}
		}

		if(n!=0 && m!=0 && is_Sub(n)==true)
			printf("YES\n");
		else
			printf("NO\n");
	}

	return 0;
}
