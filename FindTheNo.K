#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

//100以内的质数
int prime[25] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};

int helper(int n, int m)
{
	if(n==0 || m==0)
		return 1;

	if(n < m)
		swap(n,m);

	vector<int> dp(100,0);

	int i,j;
	for(i=0; i<m; ++i)
	{
		int tt = n+m-i;
		for(j=0; tt>1; ++j)
		{
			while(tt%prime[j]==0)
			{
				++dp[prime[j]];
				tt /= prime[j];
			}
		}
	}
	for(i=0; i<m; ++i)
	{
		int tt = m-i;
		for(j=0; tt>1; ++j)
		{
			while(tt%prime[j]==0)
			{
				--dp[prime[j]];
				tt /= prime[j];
			}
		}
	}
	//计算最终的结果
	long long ans = 1;
	for(i=2; i<25; ++i)
	{
		for(j=0; j<dp[i]; ++j)
		{
			ans *= i;
			if(ans > INT_MAX)
				break;
		}
	}
	//因为给定的k值在int范围内，因此当ans超过int时直接返回INT_MAX
	return ans > INT_MAX ? INT_MAX : static_cast<int>(ans);
}

/*
	找出给定0、1组合的第K大序列
	思路：从第1位开始，不断的使用0和1进行尝试，逐步确定每一位
	注意：需要小心题目给定数据范围，有可能在求排列组合时会数据溢出。
		 若题目数据规模比较小，可以使用库函数next_permutation暴力求解
*/
void find_NoK_From_0And1(int n, int m, int k)
{
	//第一步，验证给定的k是否大于可能的组合数
	if(helper(n,m) < k)
	{
		printf("Sorry, K is too large!\n");
		return;
	}
	while(true)
	{	
		//当0或1用完，或者k==1时，直接输出剩余元素
		if(n==0 || m==0 || k==1)	
		{
			for(int i=0; i<n; ++i)
				printf("0");
			for(int i=0; i<m; ++i)
				printf("1");
			break;
		}
		//当前位置放0，看最多有多少个序列
		int tt = helper(n-1, m);
		if(tt > k)	//说明当前位置放0是可以的
		{
			printf("0");
			--n;
		}
		else if(tt < k)	//说明当前位置只能放1，但是要相应的减去放0时产生的组合数
		{
			printf("1");
			--m;
			k -= tt;
		}
		else	//说明当前位置放0，其最大组合刚好满足要求
		{
			printf("0");
			--n;
			for(int i=0; i<m; ++i)
				printf("1");
			for(int i=0; i<n; ++i)
				printf("0");
			break;
		}
	}
	printf("\n");
}

/*
	给你1到n的n个不重复数字，找出它们组合的第K大序列
	思路：从第1位开始，不断从剩余数字中从小到大进行计算比较，逐步确定每一位
	注意：需要小心题目给定数据范围，有可能在求排列组合时会数据溢出。
		 若题目数据规模比较小，可以使用库函数next_permutation暴力求解
*/
void find_NoK_From_1ToN(int n, int k)
{
	//首先判断给定的k是否过大
	int t1 = 1;
	for(int i=2; i<=n; ++i)
		t1 *= i;

	if(t1 < k)
	{
		printf("Sorry, K is two large!\n");
		return;
	}
	vector<int> data(n);
	for(int i=0; i<n; ++i)
		data[i] = i+1;
	int t2 = t1;
	while(k)
	{
		t2 /= n;	//避免重复计算
		for(int i=0; i<n; ++i)
		{
			if(t2 > k)	//说明以该数字开始的排列组合数满足要求
			{
				printf("%d",data[i]);
				data.erase(data.begin()+i);	//将使用过的元素去掉
				break;
			}
			else if(t2 < k)
			{
				k -= t2;	//将该元素为首时产生的排列数减掉
			}
			else
			{
				printf("%d",data[i]);
				data.erase(data.begin()+i);	//将使用过的元素去掉
				for(int j=data.size()-1; j>=0; --j)
					printf("%d",data[j]);
				k = 0;
				break;
			}
		}
		--n;	//每次都会消耗掉一个数字
	}
	printf("\n");
}

int main(void)
{
	int n,m,k;	//n-0个数  m-1的个数

	while(scanf("%d %d %d",&n,&m,&k)==3)
		find_NoK_From_0And1(n, m, k);

	while(scanf("%d %d",&n,&k)==2)
		find_NoK_From_1ToN(n, k);

	return 0;
}
