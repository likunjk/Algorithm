class Solution {
public:
    //采取的策略：首先遍历二维数组，标记每行和每列是否该被置0
    void setZeroes(vector<vector<int> > &matrix) 
    {
        int n = matrix.size();
        if(n==0)
            return;
        int m = matrix[0].size();
        vector<int> row(n, 0);
        vector<int> column(m, 0);
        
        for(int i=0; i<n; ++i)
        {
            for(int j=0; j<m; ++j)
            {
                if(matrix[i][j]==0)
                    row[i] = column[j] = 1;
            }
        }
        for(int i=0; i<n; ++i)
        {
            for(int j=0; j<m; ++j)
            {
                if(row[i]==1 || column[j]==1)
                {
                    matrix[i][j] = 0;
                }
            }
        }
    }
};
