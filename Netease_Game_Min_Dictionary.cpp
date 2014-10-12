#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
using namespace std;

// 给定一个字符串，每次从字符串的首尾选择一个字符，最终形成一个新的字符串
// 实现该方法，使得新字符串的字典序最小
string minDcitionary(string str)
{
	int n = str.length();
	if(n <= 1)
		return str;
	vector<char> dp;
	dp.reserve(n+1);
	for(int i=0,j=n-1; i<=j; )
	{
		if(str[i] < str[j])	//当左右不等时，选择最小的那一个
			dp.push_back(str[i++]);
		else if(str[i] > str[j])
			dp.push_back(str[j--]);
		else	//当左右相等时，使用贪心确定选择哪一边
		{
			int left = 1;	//默认选择左边字符
			for(int k=0; i+k<j-k; ++k)
			{
				if(str[i+k] < str[j-k])
					break;
				else if(str[i+k] > str[j-k])
				{
					left = 0;
					break;
				}
				else
					continue;
			}
			if(left == 1)
				dp.push_back(str[i++]);
			else
				dp.push_back(str[j--]);
		}
	}
	return string(dp.begin(), dp.end());
}

int main(void)
{
	string str;
	while(cin>>str)
	{
		string ans = minDcitionary(str);
		cout<<ans<<endl;
	}
	return 0;
}

