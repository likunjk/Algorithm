#include<iostream>
#include<cstdio>
using namespace std;

int lowBit(int x)
{
	//举例：x = 1100
	//	   y = x&(x-1) = 1100&1011 = 1000	作用是将最后一个1变为0  
	//	   z = x^y =  1100^1000 = 0100	作用是只保留最后一个1
	return (x&(x-1))^x;
}

void FindOneUnique(int A[], int n)
{
	if(n < 1)	return ;
	int x = 0;
	for(int i=0; i<n; ++i)
		x ^= A[i];
	cout<<x<<endl;
}

void FindTwoUnique(int A[], int n)
{
	if(n < 2)	return ;
	int x = 0;
	for(int i=0; i<n; ++i)
		x ^= A[i];
	int flag = lowBit(x);
	int a = 0;
	for(int i=0; i<n; ++i)
	{
		if(A[i]&flag)	//判断当前元素的位置该位是否为1，也可以通过lowBit(A[i])==flag来判断
			a ^= A[i];
	}
	int b = x^a;
	cout<<a<<" "<<b<<endl;
}

void FindThreeUnique(int A[], int n)
{
	if(n < 3)	return ;
	int x = 0;
	for(int i=0; i<n; ++i)
		x ^= A[i];
	int k = 0;
	//k = lowBit(x^a) ^ lowBit(x^b) ^ lowBit(x^c);	因为其他数字出现偶数次，最后会相互异或掉
	for(int i=0; i<n; ++i)
		k ^= lowBit(x^A[i]);
	int flag = lowBit(k);
	int a = 0;
	for(int i=0; i<n; ++i)
	{
		if((x^A[i])&flag)	//判断x^A[i]对应的该位是否为1
			a ^= A[i];
	}
	cout<<a<<" ";
	for(int i=0; i<n; ++i)
	{
		if(A[i]==a)
		{
			swap(A[i],A[n-1]);	//将已经找到的元素移到最后面，这样免得删除带来移动整个输出
			break;
		}
	}
	FindTwoUnique(A,n-1);	//这里的长度要相应的减1
}	

int main(void)
{
	int data[] = {1,2,3,4,4,5,5,6,6,6,6};

	FindThreeUnique(data, sizeof(data)/sizeof(data[0]));

	return 0;
}
