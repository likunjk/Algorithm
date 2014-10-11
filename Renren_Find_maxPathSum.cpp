#include<iostream>
using namespace std;

struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(){}
	TreeNode(int x):val(x),left(NULL),right(NULL){}
};

int helper(TreeNode *root, int &ans)
{
	if(root==NULL)
		return 0;
	int left = helper(root->left, ans);
	int right = helper(root->right, ans);
	// 枚举以每个节点为中心形成的最大路径和
	int tt = left+right+root->val;
	if(tt > ans)
		ans = tt;
	// 保证返回值一定大于等于0，并且是只能返回左右子树一边的值
	return max( 0, max(left+root->val, right+root->val) );
}

/*规定：
	1、若给定二叉树为空，返回0
	2、若给定二叉树只有根节点，返回根节点的值
	3、其他情况返回最大路径和
*/
int maxPathSum(TreeNode *root)
{
	if(root==NULL)
		return 0;
	int ans = INT_MIN;	//此处注意不能是0，因为有可能最终结果为负数
	helper(root, ans);
	return ans;
}

/*人人2015浙江大学笔试题第1题：求给定二叉树的最大路径和.
  比如下面的最大路径和为8 = 4 + -2 + 1 + 5
	 1
	/ \
  -2   5
  / \
 3   4
*************************************************/
int main(void)
{
	TreeNode *A = new TreeNode(1);
	TreeNode *B = new TreeNode(-2);
	TreeNode *C = new TreeNode(5);
	TreeNode *D = new TreeNode(3);
	TreeNode *E = new TreeNode(4);
	
	A->left = B;
	A->right = C;
	B->left = D;
	B->right = E;

	int ans = maxPathSum(A);
	
	return 0;
}
