#pragma once
#include<string>

enum Status
{
	EXITS,
	DELETED,
	EMPTY,
};

template<class T>
struct HashFuner
{
	size_t operator()(const T& key)
	{
		return key;
	}
};

static size_t BKDRHash(const char* str)
{
	size_t seed = 131;
	size_t hash = 0;
	while (*str)
	{
		hash = hash * seed + (*str++);
	}
	return (hash & 0x7FFFFFFF);
}

template<>
struct HashFuner<string>
{
	size_t operator()(const string& key)
	{
		return BKDRHash(key.c_str());
	}	
};


template<class T,class HashFun = HashFuner<T>>
class HashTable
{
public:
	HashTable()
		:_array(NULL)
		, _status(0)
		, _size(0)
		, _capacity(0)
	{}
	HashTable(const size_t size)
		:_array(new T[size])
		, _status(new Status[size])
		, _size(0)
		, _capacity(size)
	{
		for (size_t i = 0; i < size;++i)
		{
			_status[i] = EMPTY;
		}
	}
	~HashTable()
	{
		if (_array)
		{
			delete[] _array;
			delete[] _status;
		}
	}
public:
	bool Insert(const T& key)
	{
		if (_size*10/_capacity == 8)     //ÔöÈÝ
		{
			HashTable<T,HashFun> newHT(_capacity * 2);
			for (size_t i = 0; i < _capacity;++i)
			{
				if (_status[i] == EXITS)
				{
					newHT.Insert(_array[i]);
				}
			}
			Swap(newHT);
		}
		size_t index = Location(key);
		while (_status[index] == EXITS)
		{
			++index;
			if (index == _capacity)
			{
				index = 0;
			}	
		}
		_array[index] = key;
		_status[index] = EXITS;
		++_size;
		return true;
	}
	size_t Location(const T& key)
	{
		HashFun hash;
		return hash(key)%_capacity;
	}
	bool Remove(const T& key)
	{
		size_t index = Location(key);
		while (_status[index] != EMPTY)
		{
			if (_array[index] == key && _status[index] == EXITS)
			{
				_status[index] = DELETED;
				_size--;
			}
			++index;
			if (index == _capacity)
			{
				index = 0;
			}
		}
		return false;
	}
	size_t Find(const T& key)
	{
		size_t index = Location(key);
		while (_status[index] != EMPTY)
		{
			if (_array[index] == key && _status[index] == EXITS)
			{
				return index;
			}
			++index;
			if (index == _capacity)
			{
				index = 0;
			}
		}
		return -1;
	}
	void Print()
	{
		for (size_t i = 0; i < _capacity;++i)
		{
			cout << "[" << i << "]" << ":";
			cout << _array[i] << ":";
			cout << _status[i] << endl;
		}
		cout << "----------------------------------"<<endl;
	}
	void PrintStr()
	{
		for (size_t i = 0; i < _capacity; ++i)
		{
			cout << "[" << i << "]" << ":";
			cout << _array[i].c_str() << ":";
			cout << _status[i] << endl;
		}
		cout << "----------------------------------" << endl;
	}
protected:
	void Swap(HashTable<T,HashFun>& ht)
	{
		swap(ht._array,_array);
		swap(ht._status,_status);
		swap(ht._size,_size);
		swap(ht._capacity,_capacity);
	}
protected:
	T* _array;
	Status* _status;
	size_t _size;
	size_t _capacity;
};

void TestLiner()
{
	HashTable<int> h1(10);
	h1.Insert(89);
	h1.Insert(19);
	h1.Insert(49);
	h1.Insert(18);
	h1.Insert(9);
	h1.Insert(89);
	h1.Insert(19);
	h1.Insert(49);
	h1.Insert(18); 
	h1.Insert(9);

	h1.Print();

	h1.Remove(9);
	h1.Remove(29);

	h1.Print();

	size_t pos = h1.Find(18);
	cout << "Find():" << pos << endl;

	HashTable<string> h2(5);
	h2.Insert("abcd");
	h2.Insert("dbca");

	h2.PrintStr();
}