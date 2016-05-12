#include<iostream>
using namespace std;

typedef int DataType;

struct SlistNode
{
	SlistNode(const DataType x)
	:_data(x)
	, _next(NULL)
	{
	}
	DataType _data;
	SlistNode* _next;
};

class Slist
{
public:
	Slist()
	    :_head(NULL)
	    , _tail(NULL)
	{
	}
	//拷贝构造,一个节点一个节点的拷贝
	Slist(const Slist& s)
	{
		SlistNode* s_begin = s._head;
		_head = new SlistNode(s_begin->_data);
		s_begin = s_begin->_next;
		SlistNode* begin = _head;
		while (s_begin)
		{
			begin->_next = new SlistNode(s_begin->_data);
			begin = begin->_next;
			s_begin = s_begin->_next;
		}
		_tail = begin;
		_tail->_next = NULL;
	}
	//赋值运算符重载
	Slist& operator=(const Slist& s)
	{
		SlistNode* s_begin = s._head;
		if (_head == NULL)
		{
			_head = new SlistNode(s_begin->_data);
		}
		else
		{
			_head->_data = s_begin->_data;
		}
		SlistNode* begin = _head;
		while (s_begin->_next)
		{
			
			s_begin = s_begin->_next;
			if (begin->_next == NULL)
			{
				begin->_next = new SlistNode(s_begin->_data);
				begin = begin->_next;
			}
			else
			{
				begin = begin->_next;
				begin->_data = s_begin->_data;
			}	
		}
		_tail = begin;
		_tail->_next = NULL;
		return *this;
	}
	~Slist()
	{
		Destory();
	}
	void PushBack(const DataType x)
	{
		if (_head == NULL)
		{
			_head = new SlistNode(x);
			_tail = _head;
		}
		else
		{
			_tail->_next = new SlistNode(x);
			_tail = _tail->_next;
		}
	}
	void PopBack()
	{
		if (_head == NULL)
		{
			return;
		}
		else if (_head == _tail)
		{
			delete _head;
			_head = NULL;
		}
		else
		{
			SlistNode* begin = _head;
			while (begin)
			{
				if (begin->_next == _tail)
				{
					delete _tail;
					_tail = begin;
					_tail->_next = NULL;	
				}
				begin = begin->_next;
			}
		}
	}
	void Print()
	{
		SlistNode* begin = _head;
		while (begin)
		{
			cout << begin->_data << "->";
			begin = begin->_next;
		}
		cout << "NULL" << endl;
	}
	//释放
	void Destory()
	{
		SlistNode* begin = _head;
		while (begin)
		{
			SlistNode* tmp = begin;
			begin = begin->_next;
			delete tmp;
		}
	}
private:
	SlistNode* _head;
	SlistNode* _tail;
};
