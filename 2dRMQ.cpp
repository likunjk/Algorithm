#include<iostream>
#include<cmath>
using namespace std;

const int N = 109;
const int M = 109;

int data[N][M];
int dp[N][M][7][7];	//dp[x][y][i][j]表示以点(x,y)为左上角,(x+1<<i-1, y+1<<j-1)为右下角的区域的最小值

void RMQ2D(int n, int m)
{
	int x,y,i,j;

	//初始化
	for(x=0; x<n; ++x)
	{
		for(y=0; y<m; ++y)
			dp[x][y][0][0] = data[x][y];
	}

	int k1 = (int)(log(1.0*n)/log(2.0))+1;
	int k2 = (int)(log(1.0*m)/log(2.0))+1;

	for(i=0; i<k1; ++i)
	{
		for(j=0; j<k2; ++j)
		{
			if(i==0 && j==0)	//这种情况已经处理过了
				continue;
			for(x=0; x+(1<<i)-1<n; ++x)
			{
				for(y=0; y+(1<<j)-1<m; ++y)
				{
					//这里计算时采取上下不动,左右交叉求极值的方法,这样当i==0时也是可以处理的
					//但是需要对j==0进行特殊处理
					if(j==0)
						dp[x][y][i][0] = min(dp[x][y][i-1][0], dp[x+1<<(i-1)][y][i-1][0]);
					else
					{
						//此处让i保持不动，通过j的变化求出极值
						//[x, y, x+2^i-1, y+2^j-1] = min{ [x, y, x+2^i-1, y+2^(j-1)-1],[x, y+2^(j-1), x+2^i-1, y+2^j-1] }
						dp[x][y][i][j] = min(dp[x][y][i][j-1], dp[x][y+1<<(j-1)][i][j-1]);
					}
				}
			}
		}
	}
}

int query(int x1, int y1, int x2, int y2)
{
	int i = (int)(log(x2-x1+1.0)/log(2.0));
	int j = (int)(log(y2-y1+1.0)/log(2.0));

	int ansMin = INT_MAX;
	ansMin = (ansMin, dp[x1][y1][i][j]);
	ansMin = (ansMin, dp[x2-(1<<i)+1][y1][i][j]);
	ansMin = (ansMin, dp[x1][y2-(1<<j)+1][i][j]);
	ansMin = (ansMin, dp[x2-(1<<i)+1][y2-(1<<j)+1][i][j]);

	return ansMin;
}

int main(void)
{
	int i,j,n,m,k;
	int x1,y1,x2,y2;
	scanf("%d %d",&n,&m);
	for(i=0; i<n; ++i)
	{
		for(j=0; j<m; ++j)
		{
			scanf("%d",&data[i][j]);
		}
	}

	RMQ2D(n,m);

	scanf("%d",&k);
	while(k--)
	{
		scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
		printf("%d\n",query(x1,y1,x2,y2));
	}

	return 0;
}

