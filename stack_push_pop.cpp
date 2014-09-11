#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<stack>
using namespace std;

#define N 100009


int data_in[N];
int data_out[N];
stack<int> st;

//本道题就是PAT上判断出栈序列是否合法的加强版，思路是一样的，O(n)的时间复杂度，可以不借助unordered_map
//测试链接：http://ac.jobdu.com/problem.php?pid=1366
int main(void)
{
	int i,j,n,tt;
	while(scanf("%d",&n)==1)
	{
		while(!st.empty())
			st.pop();

		for(i=0; i<n; ++i)
			scanf("%d", &data_in[i]);
		for(i=0; i<n; ++i)
			scanf("%d", &data_out[i]);

		int pos = -1;	//已经出栈元素的最大下标, 初始为-1，表示还没有元素出栈
		int state = 0;
		for(i=0; i<n; ++i)
		{
			//当栈不为空，且栈顶元素等于出栈值时，直接出栈
			if(st.size()>0 && st.top()==data_out[i])
				st.pop();
			else
			{
				//否则，要想是合法的出栈序列，则必须在后面的入栈序列中找到data_out[i]
				for(j=pos+1; j<n; ++j)
				{
					st.push(data_in[j]);
					if(data_in[j] == data_out[i])
						break;
				}
				pos = j;
				if(j==n)	//说明没有找到
				{
					state = 1;
					break;
				}
				else
					st.pop();
			}
		}
		if(state==0)
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}
