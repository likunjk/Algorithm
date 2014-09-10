#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

int tree[1009][2];
int value[1009];
vector<int> ans;

struct Node
{
	int index;
	Node *left;
	Node *right;
	Node(){}
	Node(int x):index(x),left(NULL),right(NULL){}
};

Node* helper(int root)
{
	if(root==0)
		return NULL;
	Node *p = new Node(root);
	p->left  = helper(tree[root][1]);
	p->right = helper(tree[root][0]);
	return p;
}

void preVisit(Node *root)
{
	if(root==NULL)
		return;

	ans.push_back(value[root->index]);
	preVisit(root->left);
	preVisit(root->right);
}

//测试链接：http://ac.jobdu.com/problem.php?pid=1521
int main(void)
{
	int i,n;
	char ch[3];
	int t1,t2;
	while(scanf("%d", &n)!=EOF)
	{
		if(n==0)
		{
			printf("NULL\n");
			continue;
		}
		memset(tree, 0, sizeof(tree));
		for(i=1; i<=n; ++i)
			scanf("%d", &value[i]);

		for(i=1; i<=n; ++i)
		{
			scanf("%s", ch);
			if(ch[0]=='d')
			{
				scanf("%d %d", &t1, &t2);
				tree[i][0] = t1;
				tree[i][1] = t2;
			}
			else if(ch[0]=='l')
			{
				scanf("%d", &t1);
				tree[i][0] = t1;
			}
			else if(ch[0]=='r')
			{
				scanf("%d", &t2);
				tree[i][1] = t2;
			}
			else
			{
			}
		}

		Node *root = helper(1);
		ans.clear();
		preVisit(root);

		printf("%d", ans[0]);
		for(i=1; i<n; ++i)
			printf(" %d", ans[i]);
		printf("\n");
	}

	return 0;
}

