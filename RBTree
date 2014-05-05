/*
	**********红黑树的5个规则*************************
	1、每个节点不是红色就是黑色
	2、根节点为黑色
	3、红色节点的孩子必须是黑色
	4、每个节点到NULL节点的所有路径上的黑色节点个数相同
	5、NULL节点为黑色
	*************************************************
*/

#ifndef _RBTree_H_
#define _RBTree_H_

#include<iostream>
#include<vector>
#include<stack>
using namespace std;

template<typename Type>
class RBTree
{
public:
	enum ColorType{Red, Black};
	//避免每次新建节点时都需要指定类型
	struct RBTreeNode
	{
		Type val;
		RBTreeNode* left;
		RBTreeNode* right;
		RBTreeNode* parent;
		ColorType color;
		RBTreeNode(){}
		RBTreeNode(Type _val, RBTreeNode* _parent)	//新建立节点统一为红色
			:val(_val),left(NULL),right(NULL),parent(_parent),color(Red){}
	};
	RBTree();	//空构造函数
	RBTree(Type value);	//带root值的构造函数
	~RBTree();
	bool Insert(Type value);
	bool Find(Type value);
	bool Delete(Type value);
	void Traverse(vector<Type> &v);
	void Adjust(RBTreeNode* p);
	void SingleRotateWithLeft(RBTreeNode* p);	//左旋
	void SingleRotateWithRight(RBTreeNode* p);	//右旋
	void Destroy(RBTreeNode* &p);
private:
	RBTreeNode* root;
};

template<typename Type>
RBTree<Type>::RBTree()
{
	root = NULL;
}

template<typename Type>
RBTree<Type>::RBTree(Type value)
{
	root = new RBTreeNode(value,NULL);
	root->color = Black;	//根节点为黑色
}

template<typename Type>
RBTree<Type>::~RBTree()
{
	Destroy(root);
}

template<typename Type>
bool RBTree<Type>::Insert(Type value)
{
	if(root==NULL)	//对根节点特殊处理
	{
		root = new RBTreeNode(value,NULL);
		root->color = Black;	//根节点为黑色
		return true;
	}
	RBTreeNode* p1 = root;
	RBTreeNode* p2 = NULL;	//父节点
	while(p1 != NULL)	//利用迭代进行查找，避免递归花费大量时间
	{
		p2 = p1;
		if(p1->val > value)
			p1 = p1->left;
		else if(p1->val < value)
			p1 = p1->right;
		else
			return false;
	}
	//while循环退出时p2为即将插入节点的父节点，并且同时为叶节点
	p1 = new RBTreeNode(value,p2);
	if(p2->val > value)
		p2->left = p1;
	else
		p2->right = p1;
	
	Adjust(p1);
	
	return true;
}

template<typename Type>
bool RBTree<Type>::Find(Type value)
{
	RBTreeNode* p = root;
	while(p!=NULL)
	{
		if(p->val > value)
			p = p->left;
		else if(p->val < value)
			p = p->right;
		else
			break;
	}
	if(p!=NULL)
		return true;
	else
		return false;
}

template<typename Type>
bool RBTree<Type>::Delete(Type value)
{
	RBTreeNode* p1 = root;
	RBTreeNode* p2 = NULL;
	while(p1!=NULL)
	{
		if(p1->val > value)
			p1 = p1->left;
		else if(p1->val < value)
			p1 = p1->right;
		else
			break;
	}
	if(p1==NULL)
		return false;
	//找到了需要被删除的点，下面进行删除操作
	p2 = p1->parent;
	ColorType color = p1->color;	//保留颜色信息，如果被删除节点是黑色，则需要进行调整
	//第一种情况：删除节点为叶子节点
	if(p1->left==NULL && p1->right==NULL)
	{
		if(p1==root)
		{
			delete root;
			root = NULL;
		}
		else
		{
			if(p2->left==p1)
				p2->left = NULL;
			else
				p2->right = NULL;
			delete p1;
			p1 = NULL;
			//如果被删除的节点为黑色，那么需要从其儿子节点（叶子节点就是父亲节点）开始调整,根节点被删除后不需要调整
			if(color==Black)
				Adjust(p2);
		}
	}
	//第二种情况：删除的节点为单孩子节点
	else if(p1->left==NULL || p1->right==NULL)
	{
		if(p1->left!=NULL)
		{
			if(p1==root)
			{
				p1->left->parent = NULL;//这里要注意更新其父亲节点为NULL
				root = p1->left;
				delete p1;
				p1 = NULL;
			}
			else
			{
				p1->left->parent = p2;
				if(p2->left==p1)
					p2->left = p1->left;
				else
					p2->right = p1->left;
				p2 = p1->left;
				delete p1;
				p1 = NULL;
				//如果被删除的节点为黑色，那么需要从其儿子节点（叶子节点就是父亲节点）开始调整,根节点被删除后不需要调整
				if(color==Black)
					Adjust(p2);
			}
		}
		else
		{
			if(p1==root)
			{
				p1->right->parent = NULL;
				root = p1->right;
				delete p1;
				p1 = NULL;
			}
			else
			{
				p1->right->parent = p2;
				if(p2->left==p1)
					p2->left = p1->right;
				else
					p2->right = p1->right;
				p2 = p1->right;
				delete p1;
				p1 = NULL;
				//如果被删除的节点为黑色，那么需要从其儿子节点（叶子节点就是父亲节点）开始调整,根节点被删除后不需要调整
				if(color==Black)
					Adjust(p2);
			}
		}
	}
	//第三种情况：被删除节点有2个孩子，用其右子树的
	else
	{
		RBTreeNode* p = p1;
		p1 = p1->right;
		while(p1->left!=NULL)
			p1 = p1->left;
		p->val = p1->val;	//用其右子树的最小节点的值进行替换，然后删除右子树的最小节点
		//分两种情况：叶子节点，或只有右孩子的节点
		color = p1->color;
		if(p1->left==NULL && p1->right==NULL)
		{
			p2 = p1->parent;
			if(p2->left==p1)
				p2->left = NULL;
			else
				p2->right = NULL;
			delete p1;
			p1 = NULL;		
			//如果被删除的节点为黑色，那么需要从其儿子节点（叶子节点就是父亲节点）开始调整,根节点被删除后不需要调整
			if(color==Black)
				Adjust(p2);
		}
		else
		{
			p2 = p1->parent;
			p1->right->parent = p2;
			if(p2->left==p1)
				p2->left = p1->right;
			else
				p2->right = p1->right;
			p2 = p1->right;
			delete p1;
			p1 = NULL;
			//如果被删除的节点为黑色，那么需要从其儿子节点（叶子节点就是父亲节点）开始调整,根节点被删除后不需要调整
			if(color==Black)
				Adjust(p2);
		}
	}
	return true;
}

template<typename Type>
void RBTree<Type>::Traverse(vector<Type> &v)
{
	//采用的是非递归前序遍历
	stack<RBTreeNode*> st;
	RBTreeNode* p = root;
	while(p!=NULL || !st.empty())
	{
		while(p!=NULL)
		{
			st.push(p);
			p = p->left;
		}
		if(!st.empty())
		{
			p = st.top();
			st.pop();
			v.push_back(p->val);
			p = p->right;
		}
	}
}

template<typename Type>
void RBTree<Type>::Adjust(RBTreeNode* p)
{
	//p为新添加的节点，其颜色为红色
	RBTreeNode* p1 = p;
	RBTreeNode* p2 = p->parent;
	RBTreeNode* uncle = NULL;
	while(p!=root && p->color==Red && p2->color==Red)//此处必须加p!=root的判断，不然可能会出现p2为空，空指针异常
	{
		//此处子所以不用考虑p2的父亲不存在的情况，是因为只有p2为root，其父亲才会为NULL，而p2为root，p和p2的颜色都为空的情况是不可能在此时出现的，
		//因为我们保证了根节点为黑色。即使根节点在中途被调整为红色，此时的p1也是为根节点，而不是根节点的儿子
		if(p2->parent->left==p2)//父亲节点为祖父节点的左孩子
		{
			uncle = p2->parent->right;
			if(uncle!=NULL && uncle->color==Red)//此处必须要叔叔节点存在，不然会让祖父节点违反第4条规定
			{
				p2->parent->color = Red;
				p2->color = uncle->color = Black;
				p = p2->parent;
				p2 = p->parent;
			}
			else	//无叔叔节点，或叔叔节点为黑色
			{
				if(p1==p2->right)	//p1是父节点的右孩子，要先进行左旋
				{
					SingleRotateWithLeft(p2);
					p2 = p1;	//变换之后p1是p2的父亲，为了下面代码的统一，这里进行赋值
				}
				SingleRotateWithRight(p2->parent);	//节点颜色的变换在旋转函数中完成
				p = p2;
				p2 = p->parent;
			}
		}
		else//父亲节点为祖父节点的右孩子
		{
			uncle = p2->parent->left;
			if(uncle!=NULL && uncle->color==Red)
			{
				p2->parent->color = Red;
				p2->color = uncle->color = Black;
				p = p2->parent;
				p2 = p->parent;
			}
			else
			{
				if(p1==p2->left)	//p1是p2的左孩子
				{
					SingleRotateWithRight(p2);
					p2 = p1;
				}
				SingleRotateWithLeft(p2->parent);
				p = p2;
				p2 = p->parent;
			}
		}
	}
	//将根节点始终变为黑色总是没错。若根节点原本为红色，变成黑色后黑色节点有2个黑色不违规；
	//根节点自己到每个NULL端都加1，也不违规
	root->color = Black;	
}

template<typename Type>
void RBTree<Type>::SingleRotateWithRight(RBTreeNode* p)
{
	RBTreeNode* tmp = p->left;
	p->left = tmp->right;
	if(tmp->right!=NULL)
		tmp->right->parent = p;

	tmp->right = p;
	//在将p变成tmp的孩子前，需要让tmp接收其父子关系
	if(p==root)//针对根需哟特殊处理
		root = tmp, root->parent=NULL;
	else if(p->parent->left==p)
		p->parent->left = tmp, tmp->parent=p->parent;
	else
		p->parent->right = tmp, tmp->parent=p->parent;
	p->parent = tmp;
	//变换节点颜色
	p->color = Red;
	tmp->color = Black;
}

template<typename Type>
void RBTree<Type>::SingleRotateWithLeft(RBTreeNode* p)
{
	RBTreeNode* tmp = p->right;
	p->right = tmp->left;
	if(tmp->left!=NULL)
		tmp->left->parent = p;
	tmp->left = p;
	//在将p变成tmp的孩子前，需要让tmp接收其父子关系
	if(p==root)//针对根需哟特殊处理
		root = tmp, root->parent=NULL;
	else if(p->parent->left==p)
		p->parent->left = tmp, tmp->parent=p->parent;
	else
		p->parent->right = tmp, tmp->parent=p->parent;
	p->parent = tmp;
	//变换节点颜色
	p->color = Red;
	tmp->color = Black;
}

template<typename Type>
void RBTree<Type>::Destroy(RBTreeNode* &p)
{
	if(p->left)
		Destroy(p->left);
	if(p->right)
		Destroy(p->right);
	delete p;
}



#endif
