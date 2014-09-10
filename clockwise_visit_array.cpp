#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

#define N 1009

int data[N][N];

//测试链接：http://ac.jobdu.com/problem.php?pid=1391
int main(void)
{
	int i,j,n,m;
	while(scanf("%d %d", &n,&m)!=EOF)
	{
		for(i=0; i<n; ++i)
		{
			for(j=0; j<m; ++j)
				scanf("%d", &data[i][j]);
		}

		int x = 0;
		int y = -1;	//为了下面的代码更加通用, 初始点从(0,-1)开始
		int minX = 0, maxX = n-1;	//分别表示x和y的最小最大边界
		int minY = 0, maxY = m-1;
		while(true)
		{
			if(y+1 > maxY)	//判断下一次循环遍历能否进行, 若不能则直接退出
				break;
			while(y+1 <= maxY)	//尽可能进行遍历, 直到达到边界
				printf("%d ", data[x][++y]);
			--maxY;	//改变边界值

			if(x+1 > maxX)
				break;
			while(x+1 <= maxX)
				printf("%d ", data[++x][y]);
			--maxX;

			if(y-1 < minY)
				break;
			while(y-1 >= minY)
				printf("%d ", data[x][--y]);
			++minY;

			if(x-1 < minX+1)	//这里比较特殊, 否则每圈的第一个元素会遍历2次
				break;
			while(x-1 >= minX+1)
				printf("%d ", data[--x][y]);
			++minX;
		}
		printf("\n");
	}

	return 0;
}

