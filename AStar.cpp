#include<iostream>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;

struct Node
{
	int x,y;
	int f;	//起点经过该点到终点的估算距离
	Node(){}
	Node(int _x, int _y):x(_x),y(_y){} 
	bool operator < (const Node &other)const
	{
		return this->f > other.f;
	}
	bool operator == (const Node &other)const
	{
		return this->x==other.x && this->y==other.y;
	}
};

const int N = 1000;

int direct[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};	//定义8个方向的差值
int n,m;	//地图的长和宽
bool Map[N][N];	//地图信息，	true-可以通过，false-不可以通过
bool closed_set[N][N];	//关闭集
priority_queue<Node> open_set;	//开放集
int came_from[N][N];	//记录来源点，若来源点为(x,y)，则存放值为x*N+y;
int f_score[N][N];
int g_score[N][N];
int h_score[N][N];
char record_route[N][N];

//这里的估价函数采用的是曼哈顿距离
int cost_estimate(Node &t1, Node &t2)
{
	//为了区别斜方向，并且不引入小数，基本单位为10
	return 10*( abs(t1.x-t2.x)+abs(t1.y-t2.y) );
}

//计算相邻点之间的实际距离
int distance_between(Node &t1, Node &t2)
{
	if(t1.x==t2.x || t1.y==t2.y)	//同行或者同列返回10，斜线返回14
		return 10;
	else
		return 14;
}

//根据记录的路径信息还原路径
void reconstruct_path(Node &start, Node &end)
{
	memset(record_route, '1', sizeof(record_route));
	Node tt = end;
	while( !(tt==start) )
	{
		record_route[tt.x][tt.y] = '*';
		int prex = came_from[tt.x][tt.y]/N;
		int prey = came_from[tt.x][tt.y]%N;
		tt.x = prex;
		tt.y = prey;
	}
	record_route[start.x][start.y] = 'S';
	record_route[end.x][end.y] = 'E';
	//打印路径
	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<m; ++j)
		{
			if(Map[i][j]==false)
				printf("0\t\t");
			else
				printf("%c\t\t",record_route[i][j]);
		}
		printf("\n\n\n");
	}
}

//参数分别为：起点，终点，地图的长和宽
int  AStar(Node &start, Node &end)
{
	//初始化：清空开放集、来源集、关闭集、g_score
	memset(closed_set, false, sizeof(closed_set));
	memset(came_from, -1, sizeof(came_from));
	while(!open_set.empty())
		open_set.pop();
	memset(g_score, -1, sizeof(g_score));

	//对起始点特殊处理
	g_score[start.x][start.y] = 0;
	h_score[start.x][start.y] = cost_estimate(start, end);
	f_score[start.x][start.y] = g_score[start.x][start.y] + h_score[start.x][start.y];
	start.f = f_score[start.x][start.y];
	open_set.push(start);

	while(!open_set.empty())
	{
		Node tt = open_set.top();
		open_set.pop();
		if(tt==end)
		{
			return 1;
		}
		closed_set[tt.x][tt.y] = true;
		for(int i=0; i<8; ++i)
		{
			int newx = tt.x + direct[i][0];
			int newy = tt.y + direct[i][1];
			//首先判断合法性
			if( !(newx>=0 && newx<n && newy>=0 && newy<m) )
				continue;
			//接着判断该点是否在关闭集中或者该点能否通过
			if(closed_set[newx][newy]==true || Map[newx][newy]==false)
				continue;
			Node next(newx,newy);
			int tmp_g = g_score[tt.x][tt.y] + distance_between(tt, next);
			//通过g_score的值是否为-1来判断该点是否加入到了open_set中
			if(g_score[newx][newy]==-1 || tmp_g < g_score[newx][newy])
			{
				came_from[newx][newy] = tt.x*N + tt.y;
				g_score[newx][newy] = tmp_g;
				h_score[newx][newy] = cost_estimate(end, next);
				f_score[newx][newy] = g_score[newx][newy] + h_score[newx][newy];
				next.f = f_score[newx][newy];
				open_set.push(next);	//一个点可能多次加入open_set，但是不影响结果
			}
		}
	}
	return 0;	//表示不可达
}

//根据给定文件，读取地图信息
void read_data(char *str, Node &start, Node &end)
{
	FILE *fp = fopen("input.txt", "r");
	int tt;
	fscanf(fp,"%d %d",&n,&m);
	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<m; ++j)
		{
			fscanf(fp,"%d",&tt);
			if(tt==2)	//起点
			{
				start.x = i;
				start.y = j;
				Map[i][j] = true;
			}
			else if(tt==4)	//终点
			{
				end.x = i;
				end.y = j;
				Map[i][j] = true;
			}
			else
				Map[i][j] = tt==1 ? true : false;
		}
	}
	fclose(fp);
}

int main(void)
{
	char fileName[20] = "input.txt";

	Node start, end;

	read_data(fileName, start, end);

	int state = AStar(start, end);

	if(state==1)
	{
		reconstruct_path(start,end);
	}
	else
	{
		printf("Can't reach target point!\n");
	}

	return 0;
}

//测试数据
5 7
1 1 1 1 1 1 1
1 1 1 0 1 1 1
1 2 1 0 1 4 1
1 1 1 0 1 1 1
1 1 1 1 1 1 1
