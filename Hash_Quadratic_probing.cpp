/******************************************************************/
// 参考《数据结构与算法分析：C语言描述》实现的HashTable(平方探测法)
// 支持查找，插入（过滤重复元素），删除（惰性），在散列，打印等操作
// 暂不支持自定义Hash函数，自定义比较函数（默认调用制定数据类型的比较函数）
/******************************************************************/

#include<iostream>
#include<cstdio>
using namespace std;

#define Error(str) printf("%s\n",str)
#define FatalError(str) Error(str),exit(1)
#define MinTableSize 5

typedef unsigned int Uint;
typedef unsigned int Size_t;
typedef unsigned int Position;
enum KindOfEntry
{
	LEGITIMATE, EMPTY, DELETED
};

template<typename Type>
class HashTable
{
public:
	struct HashEntry
	{
		Type element;
		KindOfEntry info;
	};
	HashTable();
	HashTable(Uint size);
	~HashTable();
	Uint NextPrime(Uint n);
	void Initialize(Uint size);
	Position Hash(Type element);
	Position Find(Type element);
	void Insert(Type element);
	bool Delete(Type element);
	Type Retrieve(Position pos);
	void ReHash();
	void PrintHashTable();
private:
	Size_t theSize;	//当前存放元素个数
	Size_t theCapacity;	//开辟的空间大小
	HashEntry* theCells;
};

template<typename Type>
HashTable<Type>::HashTable()
{
	Initialize(MinTableSize);
}

template<typename Type>
HashTable<Type>::HashTable(Uint size)
{
	Initialize(size);
}

template<typename Type>
HashTable<Type>::~HashTable()
{
	if(this->theCells!=NULL)
		delete []theCells;
	this->theCells = NULL;
}

template<typename Type>
Uint HashTable<Type>::NextPrime(Uint n)
{
	if(n%2==0) 
		n++;
	for( ; ; n+=2)
	{
		int state = 0;
		for(Uint i=3; i*i<=n; i++)
		{
			if(n%i==0)
			{
				state = 1;
				break;
			}
		}
		if(state==1)
			continue;
		else
			return n;
	}
}

template<typename Type>
void HashTable<Type>::Initialize(Uint size)
{
	if(size < MinTableSize)	//表的大小不能小于最小值
		size = MinTableSize;
	this->theSize = 0;
	this->theCapacity = NextPrime(size);
	this->theCells = new HashEntry[this->theCapacity];	//创建对象数组时只能调用默认构造函数
	if(NULL==this->theCells)
		FatalError("out 0f space!!!");
	//初始化申请的空间
	for(Uint i=0; i<this->theCapacity; ++i)
		this->theCells[i].info = EMPTY;
}

template<typename Type>
Position HashTable<Type>::Hash(Type element)
{
	return element % this->theCapacity;
}

template<typename Type>
Position HashTable<Type>::Find(Type element)
{
	//若element存在，则返回其位置；若不存在，则返回其将被插入的位置
	Position pos = Hash(element);
	Uint i = 0;
	while(theCells[pos].info!=EMPTY && theCells[pos].element!=element)
	{
		//平方探测法的快速实现
		pos += 2*(++i)-1;
		if(pos >= this->theCapacity)
			pos -= this->theCapacity;
	}
	return pos;
}

template<typename Type>
void HashTable<Type>::Insert(Type element)
{
	Position pos = Find(element);
	//不支持插入相同的元素
	if(this->theCells[pos].info!=LEGITIMATE)
	{  
		theCells[pos].element = element;
		theCells[pos].info = LEGITIMATE;
		this->theSize++;
	}
	//当元素个数超过容量一半大小时就需要扩容
	if(this->theSize >= this->theCapacity/2)
		ReHash();
}

template<typename Type>
bool HashTable<Type>::Delete(Type element)
{
	Position pos = Find(element);
	//若存在该元素，就采用惰性删除
	if(this->theCells[pos].info==LEGITIMATE)
	{
		this->theCells[pos].info = DELETED;
		return true;
	}
	else	//若不存在该元素，返回false
		return false;
}

template<typename Type>
Type HashTable<Type>::Retrieve(Position pos)
{
	return this->theCells[pos].element;
}

template<typename Type>
void HashTable<Type>::ReHash()
{
	Uint oldCapacity = this->theCapacity;
	HashEntry* oldCells = this->theCells;
	//默认扩容为原Hash表的2倍
	Initialize(2*oldCapacity);
	//将原有数据插入到新的Hash表中
	for(Uint i=0; i<oldCapacity; ++i)
	{
		if(oldCells[i].info==LEGITIMATE)
			Insert(oldCells[i].element);
	}
	//释放掉原有空间
	delete []oldCells;
}

template<typename Type>
void HashTable<Type>::PrintHashTable()
{
	for(Uint i=0; i<this->theCapacity; ++i)
	{
		if(theCells[i].info==LEGITIMATE)
			printf("HashTable[%d] : [%d]\n",i,theCells[i].element);
		else
			printf("HashTable[%d] : [ ]\n",i);
	}
}

//测试代码
int main(void)
{
	HashTable<int> h;
	int tt;
	printf("请输入需要插入的数据，-1查看Hash表内容，-2退出:\n");
	while(scanf("%d",&tt) && tt!=-2)
	{
		if(tt==-1)
			h.PrintHashTable();
		else
			h.Insert(tt);
	}

	return 0;
}
