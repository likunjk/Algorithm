class Solution {
public:
    //采取的策略：首先遍历二维数组，标记每行和每列是否该被置0
    void setZeroes(vector<vector<int> > &matrix) 
    {
        int n = matrix.size();
        if(n==0)
            return;
        int m = matrix[0].size();
        
        bool row = false;  //用于标记第一行是否有元素为0
        bool column = false;  //用于标记第一列是否有元素为0
        for(int j=0; j<m; ++j)
        {
            if(matrix[0][j]==0)
            {
                row = true;
                break;
            }
        }
        for(int i=0; i<n; ++i)
        {
            if(matrix[i][0]==0)
            {
                column = true;
                break;
            }
        }
        for(int i=1; i<n; ++i)
        {
            for(int j=1; j<m; ++j)
            {
                if(matrix[i][j]==0) //用第0行和第0列来存储每行和每列的0信息
                    matrix[i][0] = matrix[0][j] = 0;
            }
        }
        for(int i=1; i<n; ++i)
        {
            for(int j=1; j<m; ++j)
            {
                if(matrix[i][0]==0 || matrix[0][j]==0)
                    matrix[i][j] = 0;
            }
        }
        //下面处理第0行和第0列
        if(row==true)
        {
            for(int j=0; j<m; ++j)
                matrix[0][j] = 0;
        }
        if(column==true)
        {
            for(int i=0; i<n; ++i)
                matrix[i][0] = 0;
        }
    }
};
