#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

int data[100009];
int  tmp[100009];
long long ans = 0;

void mergeSort(int A[], int left, int right)
{
	if(left >= right)
		return ;
	int mid = (left+right)/2;
	mergeSort(A, left, mid);
	mergeSort(A, mid+1, right);

	int i,j,k = 0;	//在合并中寻找逆序对
	for(i=left,j=mid+1; i<=mid && j<=right; )
	{
		if(A[i] <= A[j])	//说明A[i]>A[j-1]的
		{
			tmp[k++] = A[i++];
			ans += (j-mid-1);
		}
		else
			tmp[k++] = A[j++];
	}
	while(i<=mid)	//在合并中寻找逆序对
	{
		tmp[k++] = A[i++];
		ans += (right-mid);
	}
	while(j<=right)
		tmp[k++] = A[j++];
	memcpy(A+left, tmp, sizeof(int)*k);
}

// 测试链接：http://ac.jobdu.com/problem.php?pid=1348
int main(void)
{
	int i,n;
	while(scanf("%d", &n)!=EOF)
	{
		for(i=0; i<n; ++i)
			scanf("%d", &data[i]);
		ans = 0;
		mergeSort(data, 0, n-1);
		printf("%lld\n", ans);
	}
	return 0;
}

