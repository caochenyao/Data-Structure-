#pragma once
#include<vector>
#include<assert.h>

template<class T>
class Heap
{
public:
	Heap()
		:_array(NULL)
	{}
	Heap(const T* a,size_t size)
	{
		for (size_t i = 0; i < size;++i)
		{
			_array.push_back(a[i]);
		}	
	}
	void Sort()
	{
		Addown(_array);
	}
	void Push(const T& x)
	{
		_array.push_back(x);
		size_t parent = (_array.size() - 2) / 2;
		size_t child = parent * 2 + 1;
		while (child > 0)
		{
			if (child < _array.size() - 1 && _array[child] > _array[child + 1])
			{
				++child;
			}
			if (_array[child] < _array[parent])
			{
				swap(_array[child], _array[parent]);
			}
			child = parent;
			parent = (child - 1) / 2;
		}
	}
	void Pop()
	{
		assert(_array.size() > 0);
		swap(_array[0], _array[_array.size() - 1]);
		_array.pop_back();
		Sort();
	}
	bool IsEmpty()
	{
		if (_array.size() == 0)
		{
			return true;
		}
		return false;
	}
protected:
	void Addown(vector<T>& array)
	{
		assert(array.size() > 0);
		size_t parent = (array.size() - 2)/2;
		size_t child = parent * 2 + 1;
		while (child > parent)
		{
			if (child < array.size() - 1 && array[child] > array[child + 1])
			{
				++child;
			}
			if (array[child] < array[parent])
			{
				swap(array[child],array[parent]);
				Adup(child);
			}
			--parent;
			child = parent * 2 + 1;
		}
	}
	void Adup(size_t _child)
	{
		assert(_array.size() > 0);
		size_t parent = _child;
		size_t child = parent * 2 + 1;
		while (child < _array.size())
		{
			if (child < _array.size() - 1 && _array[child] > _array[child + 1])
			{
				++child;
			}
			if (_array[child] < _array[parent])
			{
				swap(_array[child], _array[parent]);
			}
			else
			{
				break;
			}
			parent = child;
			child = parent * 2 + 1;
		}
	}
protected:
	vector<T> _array;
};

void Test1()
{
	int array[10] = {10,16,18,12,11,13,15,17,14,15};
	Heap<int> h1(array,10);

	h1.Sort();
	h1.Push(9);
	h1.Pop();
}