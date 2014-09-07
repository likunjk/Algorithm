#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<stack>
#include<cstring>
#include<algorithm>
using namespace std;

typedef unsigned long long ull;

ull data[79];


void matrixMultiply(ull a[2][2], ull b[2][2])
{
	ull c[2][2];
	for(int i=0; i<2; ++i)
	{
		for(int j=0; j<2; ++j)
		{
			c[i][j] = 0;
			for(int k=0; k<2; ++k)
				c[i][j] += a[i][k]*b[k][j];
		}
	}
	for(int i=0; i<2; ++i)
	{
		for(int j=0; j<2; ++j)
			a[i][j] = c[i][j];
	}
}

//此方法源自于整数幂的非递归实现, 可以解决n很大的情况
ull helper(int n)
{
	ull p[2][2] = {{1,1},{1,0}};
	ull ans[2][2] = {{1,0},{0,1}};	//最开始为单位矩阵
	while(n)
	{
		if(n&1==1)
			matrixMultiply(ans, p);
		
		n = n >> 1;
		matrixMultiply(p, p);	//p是一个辅助变量，每次都要增长1倍
	}
	return ans[0][0];
}


// 测试链接：http://ac.jobdu.com/problem.php?pid=1387
int main(void)
{
	int n;
	while(scanf("%d", &n)!=EOF)
	{
		if(n <= 1)
			printf("%d\n", n);
		else
			printf("%llu\n", helper(n-1));
	}

	return 0;
}
