#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#include<unordered_set>
#include<algorithm>
using namespace std;

struct Point
{
	int x,y;
	Point(){}
	Point(int _x, int _y):x(_x),y(_y){}
};

int area(Point *paper, int n)
{
	int i,k;
	int ans = 0;
	while(n > 0)
	{
		int x0 = paper[0].x;
		int y0 = paper[0].y;
		for(i=1; i<n; ++i)
		{
			// 每次寻找y值最大，当有多个最大时，选取x最大的那个点
			if(paper[i].y > y0 || (paper[i].y==y0 && paper[i].x > x0))
			{
				x0 = paper[i].x;
				y0 = paper[i].y;
			}
		}
		ans += x0*y0;
		for(i=0,k=0; i<n; ++i)
		{
			if(paper[i].x > x0)
			{
				// 将本次没有处理的点进行变换，准备下一次处理
				paper[k].x = paper[i].x - x0;
				paper[k++].y = paper[i].y;
			}
		}
		n = k;
	}

	return ans;
}

//Yahoo北研2015浙江大学笔试题，编程题第2题：矩形覆盖
int main(void)
{
	Point paper[] = {Point(1,2), Point(2,1)};

	int ans = area(paper, 2);

	return 0;
}
