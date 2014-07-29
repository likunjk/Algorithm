#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;


//结构体和全局变量
struct TreeNode
{
	char ch;	//当前节点的值
	bool end;	//标记当前节点是否为某单词结束点
	TreeNode *father;
	TreeNode *post;	//当前节点的后缀节点
	TreeNode* children[26];	//前期保存当前节点的子节点,后期保存a-z的后缀 

	TreeNode(char _ch, TreeNode* fa)
		:ch(_ch),end(false),father(fa),post(NULL)
	{
		memset(children, NULL, sizeof(children));
	}
};


char str[1000009];
char ask[1000009];
TreeNode *head = new TreeNode('A', NULL);
queue<TreeNode*> qu;

//构造Trie树
void buildTrie(char *str)
{
	TreeNode *p = head;
	int Len = strlen(str);
	for(int index=0; index < Len; ++index)
	{
		int tt = str[index]-'a';
		if(p->children[tt]!=NULL)
		{
			p = p->children[tt];
		}
		else
		{
			TreeNode *p1 = new TreeNode(str[index], p);
			p->children[tt] = p1;
			p = p1;
		}
	}
	p->end = true;
}


/*
计算后缀节点-广搜

规则:
1、如果它父亲结点是通过编号为char的一条边走向它的,那么只要找到它父亲的后缀结点并且走出编号为char的一条边,就能够找到它的后缀结点了.
2、如果父亲结点的后缀结点没有编号为char的一条边，那么我们可以找父亲节点的后缀结点的后缀结点.
3、在处理后缀的过程中，为了节省空间，将children用于存放后缀节点
4、后缀节点可以为自身
*/
void handlePost()
{
	head->post = head;

	for(int i=0; i<26; ++i)
	{
		if(head->children[i]==NULL)
			head->children[i] = head;
	}
	qu.push(head);

	while(!qu.empty())
	{
		TreeNode *p = qu.front();
		qu.pop();
		for(int index=0; index<26; ++index)
		{
			//此处判断时就不能用NULL来判断孩子节点
			if(p->children[index]->father!=p)
				continue;

			TreeNode *p1 = p->children[index];
			TreeNode *p2 = p1->father;
			if(p2==head)
				p1->post = head;
			else
				p1->post = p2->post->children[p1->ch-'a'];

			for(int i=0; i<26; ++i)
			{
				if(p1->children[i]==NULL)
					p1->children[i] = p1->post->children[i];
			}

			qu.push(p1);
		}
	}
}

//根据处理好的后缀节点集，来进行先行匹配
bool find(char *str)
{
	TreeNode *p = head;
	for(int index=0; str[index]; ++index)
	{	//children现在存储的是后缀节点，每次跳转到后缀节点即可，不用回退，其实也不能回退
		p = p->children[str[index]-'a'];

		if(p->end==true)
			return true;
	}
	return false;
}


//测试题目：http://hihocoder.com/contest/hiho4/problem/1
int main(void)
{
	int i,n;
	scanf("%d", &n);
	for(i=0; i<n; ++i)
	{
		scanf("%s", str);
		buildTrie(str);
	}
	
	handlePost();

	scanf("%s", ask);
	bool ans = find(ask);

	if(ans==true)
		printf("YES\n");
	else
		printf("NO\n");

	return 0;
}

