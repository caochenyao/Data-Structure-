#include<iostream>
#include<assert.h>
#include<string>
using namespace std;

template<class T>
class Stack
{
public:
	Stack()
		:array(NULL)
		, size(0)
		, capacity(0)
	{
	}
	~Stack()
	{
		if (array)
		{
			delete[] array;
		}
	}
	Stack(const Stack<T>& s)
	{
		array = new T[s.size];
		for (size_t i = 0; i < s.size; ++i)
		{
			array[i] = s.array[i];
		}
		size = s.size;
		capacity = s.size;
	}
	Stack<T>& operator=(const Stack<T>& s)
	{
		array = new T[s.size];
		for (size_t i = 0; i < s.size; ++i)
		{
			array[i] = s.array[i];
		}
		size = s.size;
		capacity = s.capacity;
		return *this;
	}
public:
	void Print()
	{
		for (size_t i = 0; i < size; ++i)
		{
			cout << array[i] << " ";
		}
		cout << endl;
	}
	void Push(const T& x)
	{
		CheckCapacity();
		array[size++] = x;
	}
	void Pop()
	{
		assert(size > 0);
		--size;
	}
	bool Empty()
	{
		if (size == 0)
		{
			return true;
		}
		else()
		{
			return false;
		}
	}
	size_t Size()
	{
		return size;
	}
	T& Top()
	{
		return array[size - 1];
	}
protected:
	void CheckCapacity()
	{
		if (size >= capacity)
		{
			capacity = capacity * 2 + 3;
			T* tmp = new T[capacity];
			for (size_t i = 0; i < size;++i)
			{
				tmp[i] = array[i];
			}
			delete[] array;
			array = tmp;
		}
	}
protected:
	T* array;
	size_t size;
	size_t capacity;
};

void StackTest1()
{
	Stack<int> s1;
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s1.Push(4);
	s1.Push(5);
	s1.Print();

	s1.Pop();
	s1.Pop();
	s1.Print();

	Stack<int> s2(s1);
	s2.Print();

	Stack<int> s3;
	s3 = s1;
	s3.Print();

	int t = s1.Top();
	cout << t << endl;
}

void StackTest2()
{
	Stack<string> s1;
	s1.Push("aaaaaa");
	s1.Push("bbbbbbbb");
	s1.Push("ccc");
	s1.Push("ddddd");
	s1.Push("eeeeeeeee");
	s1.Print();

	s1.Pop();
	s1.Pop();
	s1.Print();

	Stack<string> s2(s1);
	s2.Print();

	Stack<string> s3;
	s3 = s1;
	s3.Print();

	string t = s1.Top();
	cout << t << endl;
}
