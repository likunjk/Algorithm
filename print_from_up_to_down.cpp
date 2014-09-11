#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;

#define N 1009

int tree[N][2];
int data[N];
vector<int> dp;
queue<int> q;

void helper(int n)
{
	dp.clear();
	dp.reserve(n+9);

	q.push(1);
	while(!q.empty())
	{
		int index = q.front();
		q.pop();
		dp.push_back( data[index] );
		if(tree[index][0] != 0)
			q.push(tree[index][0]);
		if(tree[index][1] != 0)
			q.push(tree[index][1]);
	}

	printf("%d", dp[0]);
	for(int i=1; i<n; ++i)
		printf(" %d", dp[i]);
	printf("\n");
}

int main(void)
{
	int i,n;
	char str[3];
	int t1, t2;
	while(scanf("%d",&n)==1)
	{
		memset(tree, 0, sizeof(tree));
		for(i=1; i<=n; ++i)
			scanf("%d", &data[i]);
		for(i=1; i<=n; ++i)
		{
			scanf("%s", str);
			if(str[0]=='d')
			{
				scanf("%d %d", &t1, &t2);
				tree[i][0] = t1;
				tree[i][1] = t2;
			}
			else if(str[0]=='l')
			{
				scanf("%d", &t1);
				tree[i][0] = t1;
			}
			else if(str[0]=='r')
			{
				scanf("%d", &t2);
				tree[i][1] = t2;
			}
			else
			{

			}
		}
		helper(n);
	}
	return 0;
}
