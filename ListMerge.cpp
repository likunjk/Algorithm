#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;

typedef unsigned long long ull;

struct ListNode
{
	int val;
	ListNode *next;
	ListNode(){}
	ListNode(int x):val(x),next(NULL){}
};

ListNode* ListMerge(ListNode *head1, ListNode *head2)
{
	if(head1==NULL)
		return head2;
	if(head2==NULL)
		return head1;

	ListNode *p1 = head1;
	ListNode *p2 = head2;

	ListNode *head = new ListNode(0);	//使用一个多余的头节点更方便处理
	ListNode *p = head;
	while(p1!=NULL && p2!=NULL)
	{
		if(p1->val <= p2->val)
		{
			p->next = p1;
			p1 = p1->next;
		}
		else
		{
			p->next = p2;
			p2 = p2->next;
		}
		p = p->next;
	}
	
	if(p1!=NULL)
		p->next = p1;
	if(p2!=NULL)
		p->next = p2;
	
	return head->next;
}

//测试链接：http://ac.jobdu.com/problem.php?pid=1519
int main(void)
{
	int i,n,m;
	int tt;

	while(scanf("%d %d", &n, &m)!=EOF)
	{
		ListNode *Head1 = new ListNode(0);
		ListNode *Head2 = new ListNode(0);
		ListNode *p = NULL;

		p = Head1;
		for(i=0; i<n; ++i)
		{
			scanf("%d", &tt);
			p->next = new ListNode(tt);
			p = p->next;
		}

		p = Head2;
		for(i=0; i<m; ++i)
		{
			scanf("%d", &tt);
			p->next = new ListNode(tt);
			p = p->next;
		}

		p = ListMerge(Head1->next, Head2->next);
		int first = 0;
		while(p!=NULL)
		{
			if(first==0)
			{
				first = 1;
				printf("%d", p->val);
			}
			else
			{
				printf(" %d", p->val);
			}
			p = p->next;
		}

		if(first==0)
			printf("NULL");

		printf("\n");
	}

	return 0;
}

