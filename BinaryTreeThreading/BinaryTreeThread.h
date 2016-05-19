#pragma once
#include<assert.h>

typedef enum
{
	LINK,
	THREAD
}PointerTag;

template<class T>
struct BinaryTreeThdNode
{
	T _data;
	BinaryTreeThdNode<T>* _left;
	BinaryTreeThdNode<T>* _right;
	PointerTag leftTag;
	PointerTag rightTag;
	BinaryTreeThdNode(const T& x)
		:_data(x)
		,_left(NULL)
		, _right(NULL)
		, leftTag(LINK)
		, rightTag(LINK)
	{}
};

template<class T>
class BinaryTreeThd
{
public:
	BinaryTreeThd()
		:_root(NULL)
	{
	}
	BinaryTreeThd(const T* array,size_t size)
	{
		size_t index = 0;
		_root = _Create(array,size,index);
	}
	void InOrderThreading()
	{
		BinaryTreeThdNode<T>* prev = NULL;
		_InOrderThreading(_root,prev);
	}
	void PrevInOrderThreading()
	{
		BinaryTreeThdNode<T>* prev = NULL;
		_PrevInOrderThreading(_root, prev);
	}
	void PostOrderThreading()
	{
		BinaryTreeThdNode<T>* prev = NULL;
		_PostOrderThreading(_root, prev);
	}
	void InOrderThread()
	{
		BinaryTreeThdNode<T>* cur = _root;
		while (cur)
		{
			while(cur && cur->leftTag == LINK)
			{
				cur = cur->_left;
			}

			cout << cur->_data << " ";

			while (cur && cur->rightTag == THREAD)
			{
				cur = cur->_right;
				cout << cur->_data << " ";
			}
			cur = cur->_right;
			
		}
		cout << endl;
	}
	
	void PrevOrderThd()
	{
		BinaryTreeNodeThd<T>* cur = _root;
		while (cur)
		{
			while (cur && cur->_leftTag == LINK)
			{
				cout << cur->_data << " ";
				cur = cur->_left;
			}
			cout << cur->_data << " ";

			cur = cur->_right;

			/*	while(cur && cur->_rightTag == THREAD)
			{
			cur = cur->_right;
			cout<<cur->_data<<" ";
			}

			if(cur->_leftTag == LINK)
			cur = cur->_left;
			else
			cur = cur->_right;*/
		}

		cout << endl;
	}
protected:
	BinaryTreeThdNode<T>* _Create(const T* array,size_t size,size_t& index)
	{
		assert(array);
		BinaryTreeThdNode<T>* newroot = NULL;
		if (index < size && array[index] != '#')
		{
			newroot = new BinaryTreeThdNode<T>(array[index]);
			newroot->_left = _Create(array, size, ++index);
			newroot->_right = _Create(array, size, ++index);
		}
		return newroot;
	}
	void _InOrderThreading(BinaryTreeThdNode<T>* cur,BinaryTreeThdNode<T>*& prev)
	{
		if (cur == NULL)
			return;

		_InOrderThreading(cur->_left, prev);

		if (cur->_left == NULL)
		{
			cur->leftTag = THREAD;
			cur->_left = prev;
		}
		if (prev && prev->_right == NULL)
		{
			prev->rightTag = THREAD;
			prev->_right = cur;
		}

		prev = cur;

		_InOrderThreading(cur->_right, prev);
	}
	void _PrevInOrderThreading(BinaryTreeThdNode<T>* cur, BinaryTreeThdNode<T>* prev)
	{
		if (cur == NULL)
			return;
		if (cur->_left == NULL)
		{
			cur->leftTag = THREAD;
			cur->_left = prev;
		}
		if (prev && prev->_right == NULL)
		{
			prev->rightTag = THREAD;
			prev->_right = cur;
		}
		prev = cur;
		if (cur->leftTag == LINK)
		{
			_PrevInOrderThreading(cur->_left, prev);
		}
		if (cur->rightTag == LINK)
		{
			_PrevInOrderThreading(cur->_right, prev);
		}
	}

	void _PostOrderThreading(BinaryTreeThdNode<T>* cur, BinaryTreeThdNode<T>* prev)
	{
		if (cur == NULL)
		{
			return;
		}

		_PostOrderThreading(cur->_left, prev);
		_PostOrderThreading(cur->_right, prev);

		if (cur->_left == NULL)
		{
			cur->leftTag = THREAD;
			cur->_left = prev;
		}

		if (prev && prev->_right == NULL)
		{
			prev->rightTag = THREAD;
			prev->_right = cur;
		}

		prev = cur;
	}
protected:
	BinaryTreeThdNode<T>* _root;
};

void Test()
{
	int array[10] = {1,2,3,'#','#',4,'#','#',5,6};
	BinaryTreeThd<int> t1(array,10);
	//t1.InOrderThreading();
	//t1.InOrderThread();
	t1.PrevInOrderThreading();
}