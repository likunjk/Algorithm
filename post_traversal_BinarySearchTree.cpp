#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<stack>
using namespace std;

#define N 10009

int data[N];


bool helper(int left, int right)
{
	if(left >= right)
		return true;
	int i;
	int index = right-1;	//这样就不用担心所有元素都小于data[right],导致index无法赋值的情况
	for(i=left; i<right; ++i)	//前部分元素小于最后一个元素
	{
		if(data[i] > data[right])
		{
			index = i-1;
			break;
		}
	}
	for( ; i<right; ++i)	//后部分元素都要大于data[right]
	{
		if(data[i] < data[right])
			return false;
	}

	return helper(left, index) && helper(index+1, right-1);
}

//测试链接：http://ac.jobdu.com/problem.php?pid=1367
int main(void)
{
	int i,j,n,tt;
	while(scanf("%d",&n)==1)
	{
		for(i=0; i<n; ++i)
			scanf("%d", &data[i]);
		bool ans = helper(0, n-1);
		if(ans==true)
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}
