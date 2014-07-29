string longestPalindrome(string s)
{
    int n = s.length();
    int newn = 2*n+3;
    vector<char> data(newn);
    //还是要进行预处理，但是不得不说，这个预处理还是很值得的，省去了不少的麻烦
    int i,j=0;
    data[j++] = '$';    //为了不去判断边界，在首部添加一个特别的字符
    for(i=0; i<n; ++i)
    {
        data[j++] = '#';
        data[j++] = s[i];
    }
    data[j++] = '#';
    data[j] = '@';  ////为了不去判断边界，在尾部添加一个特别的字符
 
    vector<int> p(newn,1);  //p[i]表示以data[i]为中心的子串向左/向右扩展的最大长度（包括中心点）;
                            //因为每个点至少是长度为1的回文串，因此初始值为1
                            //注意：p[i]-1刚好是回文子串在原字符串中的长度
    int index=1, max=2; //max是目前已知的右边界最大的回文子串的右边界
                        //（注意：该边界是取不到的;同时max对应的中心点所形成的回文子串不一定是最长的）
    int ansIndex = index;
    for(i=2; i<newn-1; ++i)
    {
        int j = 2*index-i;  //i关于index的对称点
        if(max > i)
        {
            if(max-i > p[j])
                p[i] = p[j];
            else
                p[i] = max-i;
        }
        while(data[i-p[i]]==data[i+p[i]])
            p[i]++;
        if(i+p[i] > max)
        {
            max = i+p[i];
            index = i;
        }
        //直接在这里寻找最大值，不用等会再去循环一遍
        if(p[i] > p[ansIndex])
            ansIndex = i;
    }
    int x = (ansIndex-1)/2; //x为最长回文子串中心点在原字符串中的位置
    int y = p[ansIndex]-1;  //y为最长回文子串的长度
    return s.substr(x-y/2, y);
}
