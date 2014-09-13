#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<stack>
using namespace std;


const int N = 10009;
int tree[N][2];
int data[N];

vector<int> dp;

void helper(int root, int k, int sum)
{
	dp.push_back(root);
	sum += data[root];

	//找到了叶子节点
	if(tree[root][0]==-1 && tree[root][1]==-1)
	{
		if(sum==k)
		{
			printf("A path is found:");
			for(int i=0; i<dp.size(); ++i)
				printf(" %d", dp[i]);
			printf("\n");
		}
	}
	else
	{
		if(tree[root][0]!=-1)
			helper(tree[root][0], k, sum);
		if(tree[root][1]!=-1)
			helper(tree[root][1], k, sum);
	}
	dp.pop_back();
}


// 测试链接：http://ac.jobdu.com/problem.php?pid=1368
// 这道题一点不严谨，也没说清楚按照字典顺序说出。从给的样例来看，还可能是按照先左子树后右子树来进行遍历输出呢.
int main(void)
{
	int i,n,k;
	while(scanf("%d %d",&n,&k)!=EOF)
	{
		for(i=1; i<=n; ++i)
		{
			scanf("%d %d %d", &data[i], &tree[i][0], &tree[i][1]);
			if(tree[i][0] > tree[i][1])
				swap(tree[i][0], tree[i][1]);
		}

		printf("result:\n");
		
		helper(1, k, 0);
	}

	return 0;
}

