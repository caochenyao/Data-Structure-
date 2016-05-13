#pragma once
#include<string>

enum Status
{
	EXITS,
	DELETED,
	EMPTY,
};

template<class K>
struct HashFuner
{
	size_t operator()(const K& key)
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

template<class K, class V>
struct KeyValueNode
{
	K key;
	V value;
	KeyValueNode()
	{}
	KeyValueNode(const K& key, const V& value)
		:key(key)
		,value(value)
	{}
};

template<class K, class V, class HashFun = HashFuner<K>>
class HashTable
{
	typedef KeyValueNode<K, V> KVNode;
public:
	HashTable()
		:_array(NULL)
		, _status(0)
		, _size(0)
		, _capacity(0)
	{}
	HashTable(const size_t size)
		:_array(new KVNode[size])
		, _status(new Status[size])
		, _size(0)
		, _capacity(size)
	{
		for (size_t i = 0; i < size; ++i)
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
	HashTable(const HashTable<K,V>& ht)
	{
		HashTable<K, V> newHT(ht._capacity);
		for (size_t i = 0; i < ht._capacity; ++i)
		{
			if (ht._status[i] == EXITS)
			{
				newHT.Insert(ht._array[i].key, ht._array[i].value);
			}
		}
		Swap(newHT);
	}
	HashTable<K, V>& operator=(const HashTable<K, V>& ht)
	{
		HashTable<K, V> newTable(ht);
		Swap(newTable);
		return *this;
	}
public:
	bool Insert(const K& key,const V& value)
	{
		if (_size * 10 / _capacity == 8)
		{
			HashTable<K, V> newHT(_capacity * 2);
			for (size_t i = 0; i < _capacity; ++i)
			{
				if (_status[i] == EXITS)
				{
					newHT.Insert(_array[i].key, _array[i].value);
				}
			}
			Swap(newHT);
		}
		size_t index = Location0(key);
		size_t i = 1;
		while (_status[index] == EXITS)
		{
			index = Location2(index,i++);
			if (index == _capacity)
			{
				index = 0;
			}
		}
		_array[index].key = key;
		_array[index].value = value;
		_status[index] = EXITS;
		++_size;
		return true;
	}
	size_t Location0(const K& key)
	{
		HashFun hash;
		return hash(key) % _capacity;
	}
	size_t Location2(size_t prev,size_t i)
	{
		return (prev + 2 * i - 1) % _capacity;
	}
	bool Remove(const K& key,size_t n)
	{
		size_t index = Location0(key);
		size_t i = 1;
		while (_status[index] != EMPTY)
		{
			if (_array[index].key == key && _status[index] == EXITS)
			{
				_status[index] = DELETED;
				_size--;
			}
			index = Location2(index, i++);
			if (index == _capacity)
			{
				index = 0;
			}
		}
		return false;
	}
	size_t Find(const K& key, size_t n)
	{
		size_t index = Location(key);
		size_t i = 1;
		while (_status[index] != EMPTY)
		{
			if (_array[index].key == key && _status[index] == EXITS)
			{
				return index;
			}
			index = Location2(index, i++);
			if (index == _capacity)
			{
				index = 0;
			}
		}
		return -1;
	}
	void Print()
	{
		for (size_t i = 0; i < _capacity; ++i)
		{
			cout << "[" << i << "]" << ":";
			cout << _array[i].key << "-";
			cout << _array[i].value << ":";
			cout << _status[i] << endl;
		}
		cout << "----------------------------------" << endl;
	}
	void PrintStr()
	{
		for (size_t i = 0; i < _capacity; ++i)
		{
			cout << "[" << i << "]" << ":";
			cout << _array[i].key.c_str() << "-";
			cout << _array[i].value.c_str() << ":";
			cout << _status[i] << endl;
		}
		cout << "----------------------------------" << endl;
	}
protected:
	void Swap(HashTable<K,V>& ht)
	{
		swap(ht._array, _array);
		swap(ht._status, _status);
		swap(ht._size, _size);
		swap(ht._capacity, _capacity);
	}
protected:
	KVNode* _array;
	Status* _status;
	size_t _size;
	size_t _capacity;
};

void TestTwice()
{
	HashTable<int, int> ht(5);
	ht.Insert(12,14);
	ht.Insert(11,50);
	ht.Insert(24,22);
	ht.Insert(1,18);
	ht.Insert(4,55);
	ht.Print();

	HashTable<int, int> ht1(ht);
	ht1.Print();

	HashTable<int, int> ht2;
	ht2 = ht;
	ht2.Print();

	HashTable<string, string> htstr(10);
	htstr.Insert("×Öµä", "dictionary");
	htstr.Insert("Çå³ý", "clear,destroy");
	htstr.Insert("ÊÖ»ú", "mobilephone");
	htstr.Insert("µçÄÔ", "pc");
	htstr.Insert("ÎüÑª¹í", "vampire");
	htstr.PrintStr();

	HashTable<string, string> htstr1(htstr);
	htstr1.PrintStr();
}