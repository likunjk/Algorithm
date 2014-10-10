#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#include<unordered_set>
#include<algorithm>
using namespace std;

class Solution {
public:
    int helper(unordered_set<string> &dict, vector<int> &dp, string &s, int index)
    {
        if(dp[index]!=-1)   //直接返回结果，避免大量重复子问题的计算
            return dp[index];
        
		dp[index] = 0;
        int n = s.length();
        if(dict.find(s.substr(index, n-index))!=dict.end()) //说明整个串就是一个合法单词
            dp[index]++;
        
        for(int i=index; i<n-1; ++i)    //这里要注意不能取整个串，调用helper必须要保证index的合法性
        {
            if(dict.find(s.substr(index, i-index+1))!=dict.end())
            {
				int tt = helper(dict, dp, s, i+1);
                dp[index] += tt;
            }
        }
        return dp[index]; 
    }
    int wordBreak(string &s, unordered_set<string> &dict) 
    {
        int n = s.length();
        if(n==0)
            return 0;
        
		//dp[i]表示从位置i开始到末尾的字符串有几种划分方式, -1表示还未确定
        vector<int> dp(n, -1);  
        helper(dict, dp, s, 0);
        
        return dp[0];
    }
};

// Yahoo北研2015校园招聘浙江大学笔试题，笔试当时没有用备忘录，SB了
int main(void)
{
	//= ["cat", "cats", "and", "sand", "dog"];
	string s = "catsanddog";
	unordered_set<string> dict;
	dict.insert("cat");
	dict.insert("cats");
	dict.insert("and");
	dict.insert("sand");
	dict.insert("dog");
	
	Solution obj;
	obj.wordBreak(s, dict);
	
	return 0;
}
