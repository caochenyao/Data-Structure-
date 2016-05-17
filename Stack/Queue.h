#include<iostream>
#include<assert.h>
using namespace std;

template<class T>
struct Node
{
	Node(const T& x)
	:_data(x)
	, _next(NULL)
	{
	}
	T _data;
	Node<T>* _next;
};
template<class T>
class Queue
{
public:
	Queue()
		:_head(NULL)
		, _tail(NULL)
	{
	}
	~Queue()
	{
		Node<T>* begin = _head;
		while (begin)
		{
			Node<T>* tmp = begin;
			begin = begin->_next;
			delete tmp;
		}
	}
	Queue(const Queue<T>& q)
	{
		Node<T>* begin = q._head;
		_head = new Node<T>(begin->_data);
		_tail = _head;
		begin = begin->_next;
		while (begin)
		{
			_tail->_next = new Node<T>(begin->_data);
			_tail = _tail->_next;
			begin = begin->_next;
		}
	}
	Queue<T>& operator=(const Queue<T>& q)
	{
		Node<T>* begin = q._head;
		_head = new Node<T>(begin->_data);
		_tail = _head;
		begin = begin->_next;
		while (begin)
		{
			_tail->_next = new Node<T>(begin->_data);
			_tail = _tail->_next;
			begin = begin->_next;
		}
		return *this;
	}
public:
	void Push(const T& x)
	{
		if (_head == NULL)
		{
			_head = new Node<T>(x);
			_tail = _head;
		}
		else
		{
			_tail->_next = new Node<T>(x);
			_tail = _tail->_next;
		}
	}
	void Pop()
	{
		assert(_head);
		Node<T>* tmp = _head;
		_head = _head->_next;
		delete tmp;
	}
	bool Empty()
	{
		if (_head == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	T& Size()
	{
		int size = 0;
		Node<T>* tmp = _head;
		while (tmp)
		{
			size++;
			tmp = tmp->_next;
		}
		return size;
	}
	Node<T>*& Front()
	{
		return _head;
	}
	Node<T>*& Back()
	{
		return _tail;
	}
	void Print()
	{
		Node<T>* tmp = _head;
		while (tmp)
		{
			cout << tmp->_data << "->";
			tmp = tmp->_next;
		}
		cout << "NULL" << endl;
	}
protected:
	Node<T>* _head;
	Node<T>* _tail;
};

void QueueTest()
{
	Queue<int> q1;
	q1.Push(1);
	q1.Push(2);
	q1.Push(3);
	q1.Push(4);
	q1.Push(5);
	q1.Print();

	q1.Pop();
	q1.Pop();
	q1.Print();

	Queue<int> q2(q1);
	q2.Print();

	Queue<int> q3;
	q3 = q1;
	q3.Print();

	int t = q1.Size();
	cout << t << endl;

	Node<int>* tmp = q1.Front();
	cout << tmp->_data << endl;

	tmp = q1.Back();
	cout << tmp->_data << endl;
}
