#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;

void readDigit(const int data)
{
	//Fu yi Yi er Qian san Bai si Shi wu Wan liu Qian qi Bai ba Shi jiu
	char Chinese[20][10] = {"ling","yi","er","san","si","wu","liu","qi","ba","jiu"};
	char Unit[20][10] = {""  ,"Shi","Bai","Qian","Wan","Shi","Bai","Qian","Yi","Shi"};

	if(data==0)
	{
		printf("%s\n", Chinese[0]);
		return;
	}
	long long tt = data;
	if(tt < 0)
	{
		tt = -tt;
		printf("Fu ");
	}

	vector<int> dp;
	while(tt > 0)
	{
		dp.push_back(tt%10);
		tt /= 10;
	}
	//正式输出结果
	for(int i=dp.size()-1; i>=0; --i)
	{
		if(dp[i] != 0)
			printf("%s %s ", Chinese[dp[i]], Unit[i]);
		else
		{
			if(i==8)	//如果经过亿位，那么亿一定要输出
				printf("%s ", Unit[8]);
			else if(i==4)	//万位不一定会输出
			{
				int state = 0;	//标记十万、百万、千万位上是否有某位不为0
				for(int j=i+1; j<dp.size() && j<i+4; ++j)
				{
					if(dp[j] != 0)
					{
						state = 1;
						break;
					}
				}
				if(state==1)
					printf("%s ", Unit[4]);
			}
			// 处理连续0的情况
			if(i>0 && dp[i-1]!=0)
				printf("%s ", Chinese[0]);
		}
	}
	printf("\n");
}

// 人人2015浙江大学面试题--使用中文方式阅读数字
int main(void)
{
	int x;

	while(scanf("%d", &x)!=EOF)
	{
		readDigit(x);
	}

	return 0;
}

