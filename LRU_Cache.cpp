struct DListNode
{
    int key;
    int value;
    DListNode *pre;
    DListNode *next;
    DListNode(){}
    DListNode(int k, int v):key(k),value(v),pre(NULL),next(NULL){}
};

class LRUCache{
public:
    LRUCache(int cap) 
    {
        size = 0;
        capacity = cap;
        
        head = new DListNode(0, 0);
        tail = head;
        ump.clear();
    }
    
    int get(int key) 
    {
        DListNode *p1, *p2;
        if(ump.find(key)!=ump.end())    //说明存在该key值，需要将其移到双链表的头部
        {
            DListNode *p = ump[key];
            if(p->pre!=head)    //如果该节点的前面一个是head节点，那么无需移动
            {
                if(p->next==NULL)   //说明该节点是最后一个节点
                {
                    tail = p->pre;
                    tail->next = NULL;
                    
                    p2 = head->next;
                    p->next = p2;
                    p2->pre = p;
                    head->next = p;
                    p->pre = head;
                }
                else    //说明该节点既不是头结点，也不是尾电话
                {
                    p1 = p->pre;
                    p2 = p->next;
                    
                    p1->next = p2;
                    p2->pre = p1;
                    
                    p2 = head->next;
                    p->next = p2;
                    p2->pre = p;
                    head->next = p;
                    p->pre = head;
                }
            }
            return p->value;
        }
        else
        {
            return -1;
        }
    }
    
    void set(int key, int value) 
    {
        DListNode *p, *p2;
        
        if(ump.find(key)!=ump.end())    //说明要设置的key已经存在, 那么只需要改变值，调整位置即可
        {
            p = ump[key];
            p->value = value;
            get(key);   //为了简便，直接调用get方法
            return;
        }
        
        ++size;
        if(size > capacity)
        {
            --size;
			p2 = tail->pre;
			p2->next = NULL;
            ump.erase(tail->key);
			delete tail;
			tail = p2;
        }
        if(size <= capacity)
        {
            p = new DListNode(key, value);
            if(head==tail)  //说明现在还没有内容
            {
                head->next = p;
                p->pre = head;
                tail = p;
            }
            else
            {
                p2 = head->next;
                p->next = p2;
                p2->pre = p;
            
                head->next = p;
                p->pre = head;
            }    
            ump[key] = p;
        }
    }
private:
    int size;
    int capacity;
    DListNode *head;
    DListNode *tail;
    unordered_map<int, DListNode*> ump;
};
