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


ListNode* ListReverse(ListNode *head)
{
	if(head==NULL || head->next==NULL)
		return head;

	ListNode *p1 = head;
	ListNode *p2 = NULL;
	
	while(p1->next!=NULL)	//p1->next为下一个需要反转的节点
	{
		p2 = p1->next;
		p1->next = p2->next;
		p2->next = head;
		head = p2;
	}
	return head;
}

//测试链接：http://ac.jobdu.com/problem.php?pid=1518
int main(void)
{
	int i,n;

	while(scanf("%d", &n)!=EOF)
	{
		ListNode *Head = new ListNode(0);
		ListNode *p = Head;
		int tt;

		for(i=0; i<n; ++i)
		{
			scanf("%d", &tt);
			p->next = new ListNode(tt);
			p = p->next;
		}
		p = ListReverse(Head->next);
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

