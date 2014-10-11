#include<iostream>
#include<unordered_set>
using namespace std;


/*************************************************************
  p1指针跟普通链表的next指针一样，沿着p1可以遍历完整个链表
  p2指针指向其他任意一个节点，但是没有两个节点的p2指针指向同一个节点
*************************************************************/
struct Node
{
	int val;
	Node *p1;	
	Node *p2;
	Node(){}
	Node(int x):val(x),p1(NULL),p2(NULL){}
};


// 普通链表的反转，这里是反转p1指针
Node *listReverse(Node *head)
{
	if(head==NULL || head->p1==NULL)
		return head;
	Node *p = head;
	while(p->p1!=NULL)
	{
		Node *q = p->p1;
		p->p1 = q->p1;
		q->p1 = head;
		head = q;
	}
	return head;
}


//要求：同时反转p1和p2指针
Node* Node_Reverse(Node *head)
{
	if(head==NULL || head->p1==NULL)
		return head;
	//首先反转p2指针，借助Hash表标记已经反转过的节点
	unordered_set<Node*> ust;
	Node *p = head;
	while(p!=NULL)
	{
		// 说明该节点的p2指针还没有反转
		if(ust.find(p)==ust.end())
		{
			vector<Node*> dp;
			dp.push_back(p);
			ust.insert(p);

			Node *q = p->p2;
			while(q != p)	//因为p2指针最终会形成一个环
			{
				dp.push_back(q);
				ust.insert(q);
				q = q->p2;
			}
			dp.push_back(p);	//为了方便处理,将环的入口再次加入vector
			for(int i=dp.size()-1; i>0; --i)
				dp[i]->p2 = dp[i-1];
		}
		p = p->p1;
	}
	
	//反转p1指针
	head = listReverse(head);

	return head;
}


/*人人2015浙江大学笔试题第2题：反转p1和p2指针
**************************************************/
int main(void)
{
	Node *A = new Node(1);
	Node *B = new Node(2);
	Node *C = new Node(3);
	
	A->p1 = B;
	B->p1 = C;

	A->p2 = B;
	B->p2 = C;
	C->p2 = A;

	Node *head = Node_Reverse(A);
	
	return 0;
}

