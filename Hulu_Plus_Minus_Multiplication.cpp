#include<iostream>
#include<cstdio>
#include<cstring>
#include<stack>
using namespace std;


int helper(int t1, int t2, char op)
{
	int ans = 0;
	switch(op)
	{
	case '+':
		ans = t1+t2;
		break;
	case '-':
		ans = t1-t2;
		break;
	case '*':
		ans = t1*t2;
		break;
	default:
		ans = 0;
		break;
	}
	return ans;
}

/*****************************************************
	功能：加减乘四则运算，带有括号，输入保证合法
	并且操作数都是非负整数, 但是操作数和操作符之间可能有空格
******************************************************/
int cal(char *A)
{
	int t1, t2;
	int n = strlen(A);
	stack<int> data;	//数据栈
	stack<char> op;		//符号栈
	for(int i=0; i<n; )
	{
		if(A[i]==' ')
		{
			++i;
		}
		else if(A[i]>='0' && A[i]<='9')
		{
			int tt = 0;
			while(i<n && A[i]>='0' && A[i]<='9')
				tt = tt*10 + (A[i++]-'0');
			data.push(tt);
			if(!op.empty() && op.top()=='*')	//当一个操作数入栈时，若其左边为*号，则需要立即计算
			{
				t2 = data.top(), data.pop();
				t1 = data.top(), data.pop();
				data.push( helper( t1, t2, op.top() ) );
				op.pop();
			}
		}
		else if(A[i]==')')	//遇到右括号则一直计算，直到找到第一个左括号
		{
			stack<int> data2;
			stack<char> op2;
			while(op.top()!='(')
			{
				data2.push( data.top() ), data.pop();
				op2.push( op.top() ), op.pop();
			}
			// 在一个括号内，有n个操作符时，只能有n+1个操作数
			data2.push( data.top() ), data.pop();	
			while(!op2.empty())
			{
				t1 = data2.top(), data2.pop();	//这里注意，操作数的顺序发生了变化
				t2 = data2.top(), data2.pop();
				data2.push( helper( t1, t2, op2.top() ) );
				op2.pop();
			}
			data.push( data2.top() );
			op.pop();	//弹出左括号
			++i;
		}
		else	//+ - * ( 直接入栈
		{
			op.push(A[i++]);
		}
	}

	// 扫描完之后，处理剩余的 + - 号, 这里不能直接计算，因为减法是区分左右操作数的
	stack<int> data2;
	stack<char> op2;
	while(!data.empty())
		data2.push( data.top() ), data.pop();
	while(!op.empty())
		op2.push( op.top() ), op.pop();

	while(!op2.empty())
	{
		t1 = data2.top(), data2.pop();	//这里注意，操作数的顺序发生了变化
		t2 = data2.top(), data2.pop();
		data2.push( helper(t1, t2, op2.top()) );
		op2.pop();
	}
	return data2.top();	//最后数据栈的元素就是结果
}

char str[10009];
// Hulu 2015浙江大学校园招聘面试题第2题
int main(void)
{
	while(gets(str))
	{
		printf("%d\n", cal(str));
	}
	return 0;
}
