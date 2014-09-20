#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

typedef unsigned long long ull;

const int N = 100009;
int A[N], B[N];

// 寻找A和B两两相加之后小于等于target的有多少个数
ull func(int n, int m, ull target)
{
	// 采用贪心算法，复杂度O(n+m),分析复杂度采用均摊思想，与KMP类似
	ull total = 0;
	for(int i=0, j=m-1; i<n; ++i)
	{
		// A和B数组都是有序的，从小到大
		// 当A[i]+B[j]<=target时，A[i]+B[k](0<k<j)肯定也是小于等于target的。
		// 又因为A[i+1]>=A[i], 因此下一次的寻找就可以直接从j开始，而不用重新从j=m-1开始
		while(j>=0 && A[i]+B[j] > target)
			--j;
		if(j < 0)	//一个小优化
			break;
		total += (j+1);	//因为下标从0开始，所以是j+1
	}

	return total;
}

// 二分查找A和B两两相加之后的第k小的数
ull helper(int n, int m, ull k)
{
	ull left = 0;
	ull right = A[n-1] + B[m-1];
	while(left <= right)
	{
		ull mid = (left+right)/2;
		//当相等时仍然往左边走，如果当前的mid值的确是最终的结果的话，在进行下一次的循环中，肯定会执行left = mid+1
		if(func(n, m, mid) >= k)
			right = mid-1;
		else
			left = mid+1;
	}
	return left;
}

// 测试链接：http://ac.jobdu.com/problem.php?pid=1534
int main(void)
{
	int i,n,m;
	ull k;
	
	while( scanf("%d %d %llu", &n, &m, &k)!=EOF )
	{
		for(i=0; i<n; ++i)
			scanf("%d", &A[i]);

		for(i=0; i<m; ++i)
			scanf("%d", &B[i]);

		sort(A, A+n);
		sort(B, B+m);

		printf("%llu\n", helper(n, m, k));
	}

	return 0;
}

