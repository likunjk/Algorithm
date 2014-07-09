class Solution {
public:
    //思路：通过查看3位格雷码生成顺序，知道了其生成规律：
    //1、改变最右边位元的值；2、改变最右边第一为1位元的左边的值；3、重复第一和第二步
    //下面是很朴素的一种实现方式，复杂度为O(n*2^n)
    vector<int> grayCode(int n) 
    {
        vector<int> data(n, 0); //最开始为全0序列
        
        int size = 1<<n;
        
        vector<int> ans;
        ans.reserve(size);
        ans.push_back(0);
        
        for(int i=1; i<size; ++i)
        {
            if(i&1==1)  //分奇偶数轮流执行
                data[n-1] = (data[n-1] == 1) ? 0 : 1;
            else
            {
                for(int j=n-1; j>=0; --j)
                {
                    if(data[j]==1)
                    {
                        data[j-1] = (data[j-1] == 1) ? 0 : 1;
                        break;
                    }
                }
            }
            int tt = 0;
            for(int j=0; j<n; ++j)
                tt = tt*2 + data[j];
            ans.push_back(tt);
        }
        return ans;
    }
};
