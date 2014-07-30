#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

struct Node
{
	int ID;
	int sum;
	int perfect;
	int score[9];
	int successSubmit;
	Node()
	{
		ID = 99999;
		sum = 0;
		perfect = 0;
		successSubmit = 0;
		fill(score, score+9, -2);
	}
};

inline bool comp(const Node &a, const Node &b)
{
	if(a.sum==b.sum)
	{
		if(a.perfect==b.perfect)
			return a.ID < b.ID;
		else
			return a.perfect > b.perfect;
	}
	else
	{
		return a.sum > b.sum;
	}
}

Node data[10009];
int full[9];

int main(void)
{
	int i,j,n,k,m;
	scanf("%d %d %d", &n, &k, &m);
	for(i=1; i<=k; ++i)
	{
		scanf("%d", &full[i]);
	}

	int t1, t2, t3;
	for(i=0; i<m; ++i)
	{
		scanf("%d %d %d", &t1, &t2, &t3);
		if(data[t1].score[t2] < t3)
			data[t1].score[t2] = t3;
	}
	//在这里计算总分
	for(i=1; i<=n; ++i)
	{
		data[i].ID = i;
		for(j=1; j<=k; ++j)
		{
			if(data[i].score[j] >= 0)
			{
				data[i].successSubmit += 1;
				data[i].sum += data[i].score[j];
			}
			if(data[i].score[j]==full[j])
				data[i].perfect++;
		}
		//将没有成功提交的人安排在后面
		if(data[i].successSubmit==0)
			data[i].sum = -10;
	}

	sort(data+1, data+n+1, comp);

	int index = 1;
	for(i=1; i<=n; ++i)
	{
		if(data[i].successSubmit==0)
			break;

		if(i>1 && data[i].sum!=data[i-1].sum)
			index = i;

		printf("%d %05d %d", index, data[i].ID, data[i].sum);
		for(j=1; j<=k; ++j)
		{
			if(data[i].score[j]==-2)
				printf(" -");
			else if(data[i].score[j]==-1)
				printf(" 0");
			else
				printf(" %d", data[i].score[j]);
		}
		printf("\n");
	}

	return 0;
}
