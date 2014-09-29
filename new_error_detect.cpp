#include<iostream>
using namespace std;

/* 功能: 测试当new失败时究竟是抛出异常还是返回空指针 */
void testException(size_t size)
{
	int *p;
	while(1)
	{
		try
		{
			p = new int[size];
		}catch ( const bad_alloc& e) {
			cout<<"testException: Throw Exception\n";
			return;
		}
		if(p==NULL)
		{
			cout<<"testException: p is NULL\n";
			return;
		}
	}
}


/* 功能: 测试std:noexception */
void testNothrow(size_t size)
{
	int *p;
	while(1)
	{
		try
		{
			p = new(std::nothrow) int[size];
		}catch ( const bad_alloc& e) {
			cout<<"testExceptionOrNull: Throw Exception\n";
			return;
		}
		if(p==NULL)
		{
			cout<<"testNothrow: p is NULL\n";
			return;
		}
	}
}

int main(void)
{	
	testException(0xfffffff);	//Throw Exception

	testNothrow(0xfffffff);	//testNothrow: p is NULL

	return 0;
}

