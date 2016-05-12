#include<assert.h>

typedef int DataType;
struct ListNode
{
	ListNode(const DataType x)
	: _data(x)
	, _next(NULL)
	, _prev(NULL)
	{
	}
	DataType _data;
	ListNode* _next;
	ListNode* _prev;
};

class List
{
public:
	List()
		:_head(NULL)
		, _tail(NULL)
	{
	}
	~List()
	{
		Clear();
	}
	//�������캯������β�庯��
	List(const List& l)
	{
		ListNode* begin = l._head;
		while (begin)
		{
			PushBack(begin->_data);
			begin = begin->_next;
		}
	}
	//��ֵ���������,��ԭ�е�ֱ������,����ͷ�庯��
	List& operator=(const List& l)
	{
		Clear();
		ListNode* begin = l._head;
		while (begin)
		{
			PushBack(begin->_data);
			begin = begin->_next;
		}
		return *this;
	}
	void Print()
	{
		ListNode* begin = _head;
		while (begin)
		{
			cout << begin->_data << "->";
			begin = begin->_next;
		}
		cout << "NULL" << endl;
	}
	void PushBack(const DataType x)
	{
		if (_head == NULL)
		{
			_head = new ListNode(x);
			_tail = _head;
		}
		else
		{
			ListNode* tmp = new ListNode(x);
			tmp->_prev = _tail;
			_tail->_next = tmp;
			_tail = tmp;
		}
	}
	void PopBack()
	{
		ListNode* begin = _head;
		if (_head == _tail)
		{
			delete _head;
			_head = NULL;
		}
		else
		{
			while (begin->_next != _tail)
			{
				begin = begin->_next;
			}
			delete _tail;
			_tail = begin;
			_tail->_next = NULL;
		}
	}
	//����ָ���ڵ�
	ListNode* Find(const DataType x)
	{
		ListNode* begin = _head;
		while (begin)
		{
			if (begin->_data == x)
			{
				return begin;
			}
			begin = begin->_next;
		}
		return NULL;
	}
	//��ĳ�ڵ�λ�ú�����½ڵ�
	void Insert(ListNode* pos,const DataType x)
	{
		assert(pos);
		if (pos->_next == NULL)
		{
			PushBack(x);
		}
		else
		{
			ListNode* tmp = new ListNode(x);
			ListNode* next = pos->_next;
			pos->_next = tmp;
			tmp->_next = next;
			next->_prev = tmp;
			tmp->_prev = pos;
		}
	}
	//ɾ��ĳ�ڵ�
	void Erase(ListNode* pos)
	{
		assert(pos);
		if (pos == _tail)
		{
			_tail = pos->_prev;
			_tail->_next = NULL;
		}
		else if (pos == _head)
		{
			_head = pos->_next;
			_head->_prev = NULL;
		}
		else
		{
			ListNode* next = pos->_next;
			ListNode* prev = pos->_prev;
			prev->_next = next;
			next->_prev = prev;
		}
		delete pos;
	}
	//��������
	void Reserve()
	{
		ListNode* left = _head;
		ListNode* right = _tail;
		while ((left != right) && (right->_next != left))
		{
			swap(left->_data,right->_data);
			left = left->_next;
			right = right->_prev;
		}
	}
private:
	void Clear()
	{
		while (_head)
		{
			ListNode* tmp = _head;
			_head = _head->_next;
			if (_head)
			{
				_head->_prev = NULL;
			}
			delete tmp;
		}
	}	

private:
	ListNode* _head;
	ListNode* _tail;
};