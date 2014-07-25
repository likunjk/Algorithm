/*---------递归版本----------*/

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {  
public:
    bool helper(TreeNode *p1, TreeNode *p2)
    {
        if(p1==NULL)
            return p2==NULL;
        else
        {
            if(p2==NULL)
                return false;
            else
            {
                if(p1->val != p2->val)
                    return false;
                else
                    return helper(p1->left, p2->right) && helper(p1->right, p2->left);
            }
        }
    }
    bool isSymmetric(TreeNode *root) 
    {
        if(root==NULL)
            return true;
        return helper(root->left, root->right);
    }
};

/*---------非递归版本----------*/


/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isSymmetric(TreeNode *root) 
    {
        if(root==NULL)
            return true;
        
        queue<TreeNode*> q;
        q.push(root->left);
        q.push(root->right);
        
        int state = 0;
        //非递归方法使用堆栈
        while(!q.empty())
        {
            TreeNode *p1 = q.front();
            q.pop();
            TreeNode *p2 = q.front();
            q.pop();
            
            //正常判断
            if(p1==NULL)
            {
                if(p2!=NULL)
                {
                    state = 1;
                    break;
                }
            }
            else    //p1!=NULL
            {
                if(p2==NULL || p1->val!=p2->val)
                {
                    state = 1;
                    break;
                }
                else
                {
                    q.push(p1->left);
                    q.push(p2->right);
                    q.push(p1->right);
                    q.push(p2->left);
                }
            }
        }
        if(state==1)
            return false;
        else
            return true;
    }
};
