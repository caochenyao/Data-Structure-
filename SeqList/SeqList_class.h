#include<iostream>
using namespace std;

typedef int DataType;

class SeqList
{
public:
	SeqList(DataType* array, size_t size)
		:_array(new DataType[size])
		,_size(size)
		,_capacity(size)
	{
		memcpy(_array,array,sizeof(int)*size); 
	}
	~SeqList()
	{
		if (_array)
		{
			delete[] _array;
			_size = 0;
		}
	}
	//��������ʹ�����
	SeqList(SeqList& s)      
		:_array(NULL)
	{
		SeqList tmp(s._array, s._size);
		Swap(tmp);
	}
	//��ֵ���������ͬ��ʹ�����
	SeqList& operator=(const SeqList& s) 
	{
		if (_array != s._array)
		{
			SeqList tmp(s._array,s._size);
			Swap(tmp);
		}
		return *this;
	}
	//����[]
	DataType& operator[](size_t index)
	{
		return _array[index];
	}
	void Print()
	{
		for (size_t i = 0; i < _size; ++i)
		{
			cout << _array[i] <<"->";
		}
		cout << "NULL" << endl;
	}
	void PushBack(const DataType& x)
	{
		//�������,���������������
		_CheckCapacity();      
		_array[_size++] = x;
	}
	void PopBack()
	{
		if (_size > 0)
		{
			_size--;
		}
	}
	//��ָ��λ�ò�������
	void Insert(size_t pos,const DataType x)
	{
		_CheckCapacity();
		for (size_t i = _size; i > pos; --i)
		{
			_array[i] = _array[i - 1];
		}
		_array[pos] = x;
		_size++;
	}
	//ɾ��ָ��λ�õ�����
	void Earse(size_t pos)
	{
		for (size_t i = pos; i < _size-1;++i)
		{
			_array[i] = _array[i + 1];
		}
		_size--;
	}
	//����ָ������
	int Find(const DataType& x)
	{
		for (size_t i = 0; i < _size;++i)
		{
			if (_array[i] == x)
			{
				return i;
			}
		}
		return -1;
	}
	size_t Size()
	{
		return _size;
	}
	size_t Capacity()
	{
		return _capacity;
	}
	//����
	void Reserve(size_t size)
	{
		if (size > _capacity)
		{
			_capacity = size;
			DataType* tmp = new DataType[_capacity];
			memcpy(tmp, _array, sizeof(int)*_size);
			delete[] _array;
			_array = tmp;
		}
	}
	void Clear()
	{
		_size = 0;
	}
private:
	void Swap(SeqList& s)
	{
		swap(_array, s._array);
		swap(_size, s._size);
		swap(_capacity, s._capacity);
	}
	void _CheckCapacity()
	{
		if (_capacity <= _size)
		{
			_capacity = _capacity * 2 + 3;
			DataType* tmp = new DataType[_capacity];
			memcpy(tmp, _array, sizeof(int)*_size);
			delete[] _array;
			_array = tmp;
		}
	}
private:
	DataType* _array;
	size_t _size;
	size_t _capacity;
};