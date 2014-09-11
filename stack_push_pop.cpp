#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<stack>
#include<map>
using namespace std;

#define N 100009

//可惜九度不支持unordered_map，不然的话效率更高
map<int, int> ump;

int data[N];
stack<int> st;

//本道题就是PAT上1051判断出栈序列是否合法的加强版，思路是一样的，O(n)的时间复杂度,前提是用unordered_map
//测试链接：http://ac.jobdu.com/problem.php?pid=1366
int main(void)
{
	int i,n,tt;
	while(scanf("%d",&n)==1)
	{
		while(!st.empty())
			st.pop();
		ump.clear();

		for(i=0; i<n; ++i)
		{
			scanf("%d", &data[i]);
			ump[data[i]] = i;
		}
		int pos = -1;
		int index;
		int state = 0;
		for(i=0; i<n; ++i)
		{
			scanf("%d", &tt);
			index = ump[tt];
			if(index > pos)
			{
				for(int j=pos+1; j<=index; ++j)
					st.push(data[j]);
				pos = index;
				st.pop();
			}
			else
			{
				if(st.top() != tt)
					state = 1;
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
