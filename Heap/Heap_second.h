#pragma once
#include<vector>
#include<assert.h>

#pragma warning(disable:4018)

//ʹ�÷º��������ǽ���ѻ���С��
template<class T>
struct Less
{
	bool operator()(const T& a, const T& b)
	{
		return a < b;
	}
};

template<class T>
struct Greater
{
	bool operator()(const T& a, const T& b)
	{
		return a > b;
	}
};

template<class T, class Compare = Less<T>>
class Heap
{
public:
	Heap()                            //�޲εĹ��캯��
		:_array(NULL)
	{}
	Heap(const T* a, size_t size)     //���εĹ��캯��
	{
		for (size_t i = 0; i < size; ++i)
		{
			_array.push_back(a[i]);
		}
	}
	void Sort()
	{
		//���ϵ���
		AdUp(_array.size() - 1);
	}
	void Push(const T& x)                //��������
	{
		_array.push_back(x);
		AdUp(_array.size() - 1);
	}
	T& Top()                             //���ضѶ�������
	{
		assert(_array.size() > 0);
		return _array[0];
	}
	size_t Size()
	{
		return _array.size();
	}
	void Pop()                          //ɾ���Ѷ�����
	{
		assert(_array.size() > 0);
		swap(_array[0], _array[_array.size() - 1]);
		_array.pop_back();
		AdDown(0);                      //�ӶѶ����½��е���
	}
	bool IsEmpty()                      //�ж϶��Ƿ�Ϊ��
	{
		return _array.empty();
	}
protected:
	void AdUp(int child)
	{
		int parent = (child - 1) / 2;    //�ҵ��ѵĵ�һ����Ҷ�ӽڵ�
		while (parent >= 0)              //�Ӹýڵ��������Ͻ��е���
		{
			if (child < _array.size() - 1 && Compare()(_array[child + 1], _array[child]))
			{
				//�ҳ�����Ҷ�ӽڵ���С����һ��
				++child;
			}
			if (Compare()(_array[child], _array[parent]))
			{
				//�����ϴ�ѻ�С�ѵ�Ҫ�󣬽������ڵ㽻��
				swap(_array[child], _array[parent]);
				//��������ܻ����֮ǰ���������ֲ�����Ҫ������Ҫ�����µ���
				AdDown(child);
			}
			--parent;
			child = parent * 2 + 1;
		}
	}
	void AdDown(int root)
	{
		int child = root * 2 + 1;
		while (child < _array.size())
		{
			if (child < _array.size() - 1 && Compare()(_array[child + 1], _array[child]))
			{
				++child;
			}
			if (Compare()(_array[child], _array[root]))
			{
				swap(_array[child], _array[root]);
				root = child;
				child = root * 2 + 1;
			}
			else
			{
				//��ʱ˵������Ķ��Ѿ�����Ҫ���ˣ�����Ҫ�ٽ��е���
				break;
			}
		}
	}
protected:
	vector<T> _array;
};

void Test2()
{
	int array[10] = { 10, 16, 18, 12, 11, 13, 15, 17, 14, 15 };
	Heap<int,Greater<int>> h1(array, 10);

	h1.Sort();
	h1.Push(9);
	h1.Pop();
}