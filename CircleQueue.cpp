#include<iostream>
using namespace std;

// 循环队列的定义和实现
class CircleQueue
{
public:
	CircleQueue(size_t size=5):front(0), rear(0)
	{
		// 规定一个循环队列的最小空间, 实际有效空间为size-1
		size = (size < 5) ? 5 : size;
		capacity = size;
		data = new(std::nothrow)int[capacity];
		if(data==NULL)
			exit(1);
	}
	~CircleQueue()
	{
		if(this->data!=NULL)
		{
			delete []this->data;
			this->data = NULL;
		}
	}
	bool isEmpty()	//判空
	{
		return this->front == this->rear;
	}
	bool isFull()	//判满
	{
		return (this->rear+1) % capacity == this->front;
	}
	size_t size()	//获取队列当前有效元素个数
	{
		return (rear-front+capacity) % capacity;
	}
	bool push(int x)
	{
		if(true==isFull())
			return false;
		data[rear] = x;
		rear = (rear+1) % capacity;
		return true;
	}
	int pop()
	{
		if(true==isEmpty())
			exit(1);
		int tt = data[front];
		front = (front+1) % capacity;
		return tt;
	}
private:
	size_t capacity;
	int *data;
	int front;
	int rear;
};


int main(void)
{
	CircleQueue q(25);

	CircleQueue p;

	return 0;
}

