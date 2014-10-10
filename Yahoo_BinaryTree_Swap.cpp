#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;


struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(){}
	TreeNode(int x):val(x),left(NULL),right(NULL){}
};

/* 不能使用贪心。比如下面两棵树，在第二层时，左右子树的值都相等.
   但是这时必须左右、右左匹配之后，才能将treeA变换成treeB
    1                  1
   / \                / \
  2   2              2   2
 / \                    / \
3   4                  3   4
****************************************************/
int minCSwap(TreeNode *treeA, TreeNode *treeB)
{
	if(treeA==NULL && treeB==NULL)
		return 0;
	if(treeA==NULL && treeB!=NULL)
		return -1;
	if(treeA!=NULL && treeB==NULL)
		return -1;
	if(treeA->val!=treeB->val)
		return -1;

	int ans = -1;	//-1表示treeA不能变换成treeB
	int t1 = minCSwap(treeA->left, treeB->left);	//左左
	int t2 = minCSwap(treeA->right, treeB->right);	//右右
	if(t1!=-1 && t2!=-1)
		ans = t1+t2;

	int t3 = minCSwap(treeA->left, treeB->right);	//左右
	int t4 = minCSwap(treeA->right, treeB->left);	//右左
	if(t3!=-1 && t4!=-1)
	{
		if(ans==-1 || ans > t3+t4+1) //此处要加1，因为本层有交换
			ans = t3+t4+1;
	}
	return ans;
}



//Yahoo北研2015浙江大学笔试题，编程题第1题：二叉树交换左右孩子
int main(void)
{
	TreeNode *A1 = new TreeNode(1);
	TreeNode *B1 = new TreeNode(2);
	TreeNode *C1 = new TreeNode(2);
	A1->left = B1;
	A1->right = C1;
	TreeNode *D1 = new TreeNode(3);
	TreeNode *E1 = new TreeNode(4);
	B1->left = D1;
	B1->right = E1;

	TreeNode *A2 = new TreeNode(1);
	TreeNode *B2 = new TreeNode(2);
	TreeNode *C2 = new TreeNode(2);
	A2->left = B2;
	A2->right = C2;
	TreeNode *D2 = new TreeNode(3);
	TreeNode *E2 = new TreeNode(4);
	C2->left = D2;
	C2->right = E2;

	int ans = minCSwap(A1, A2);

	return 0;
}
