#include<cstdio>
#include<iostream>
using namespace std;

int data[1000009];

//完备的二分解决方案, 可以通过所有测试案例
int helper(int A[], int left, int right)
{
	if(left==right || left+1==right)
		return A[left] < A[right] ? A[left] : A[right];
	
	int mid = (left+right)/2;
	
	if(A[left]==A[mid] && A[right]==A[mid])	//此处无法判断, 只能两边都二分查找
		return min(helper(A,left,mid), helper(A, mid+1,right));
	else
	{
		if(A[mid] >= A[left])	//此时mid只能在前半段,否则3个元素的值就相等,而相等的情况我们在上面已经处理了
			return helper(A, mid, right);
		else if(A[mid] <= A[right])	//同理此时mid只能在后半段
			return helper(A, left, mid);
	}
}

//测试链接：http://ac.jobdu.com/problem.php?pid=1386
int main(void)
{
	int i,n;
	while(scanf("%d",&n)!=EOF)
	{
		for(i=0; i<n; ++i)
			scanf("%d", &data[i]);
		if(data[0] < data[n-1])
			printf("%d\n", data[0]);
		else
			printf("%d\n", helper(data, 0, n-1));
	}
	return 0;
}

