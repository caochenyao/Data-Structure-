#pragma once
#include<vector>
#include<string>

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

template<class K,class V>
struct HashTableNode
{
	K _key;
	V _value;
	HashTableNode<K,V>* _next;
	HashTableNode(const K& key, const V& value)
		:_key(key)
		, _value(value)
		, _next(NULL)
	{}
};

template<class K, class V, class HashFun = HashFuner<K>>
class HashTable
{
public:
	typedef HashTableNode<K, V> KVNode;
public:
	HashTable()
		:_size(0)
	{}
	HashTable(size_t size)
	{
		_tables.resize(size);
	}
	~HashTable()
	{
		Destroy();
	}
	HashTable(const HashTable<K, V>& ht)
	{
		HashTable<K, V> newTable(ht._tables.size());	 
		for (size_t i = 0; i < ht._tables.size();++i)
		{
			//KVNode* & head = newTable._tables[i];
			KVNode* cur = ht._tables[i];
			if (cur == NULL)
			{
				continue;
			}
			while (cur)
			{
				/*KVNode* tmp = cur;
				cur = cur->_next;
				tmp->_next = head;
				head = tmp;*/
				newTable.Insert(cur->_key,cur->_value);
				cur = cur->_next;
			}
			
		}
		Swap(newTable);
	}
	HashTable<K, V>& operator=(const HashTable<K, V>& ht)
	{
		if (&ht != this)
		{
			HashTable<K, V> newTable(ht);
			Swap(newTable);
		}
		return *this;
	}
public:
	bool Insert(const K& key,const V& value)
	{
		//增容
		_CreateCapacity();
		//插入数据
		size_t index = Location(key);
		KVNode* cur = new KVNode(key,value);
		if (_tables[index] == NULL)
		{
			cur->_next = _tables[index];
			_tables[index] = cur;
			++_size;
		}
		else
		{
			KVNode* tmp = _tables[index];
			while (tmp)
			{
				if (tmp->_key == key)
					return false;
				tmp = tmp->_next;
			}
			cur->_next = _tables[index];
			_tables[index] = cur;
		}
		return true;
	}
	size_t Location(const K& key)
	{
		HashFuner<K> hf;
		return hf(key) % _tables.size();
	}
	void Print()
	{
		for (size_t i = 0; i < _tables.size();++i)
		{
			printf("Table[%d]->", i);
			KVNode* cur = _tables[i];
			while (cur)
			{
				cout << "[" << cur->_key << ":" << cur->_value << "]->";
				cur = cur->_next;
			}
			cout << "NULL" << endl;
		}
		cout << "-------------------------------------" << endl;
	}
	bool Remove(const K& key)
	{
		size_t index = Location(key);
		KVNode* cur = _tables[index];
		if (cur == NULL)
		{
			return true;
		}
		if (cur->_next == NULL)
		{
			delete cur;
			_tables[index] = NULL;
			return true;
		}
		while (cur)
		{
			KVNode* prev = cur;
			KVNode* tmp = cur->_next;
			if (tmp->_key == key)
			{
				prev->_next = tmp->_next;
				delete tmp;
				return true;
			}
			cur = cur->_next;
		}
		return false;
	}
	KVNode* Find(const K& key)
	{
		size_t index = Location(key);
		KVNode* cur = _tables[index];
		while (cur)
		{
			if (cur->_key == key)
			{
				return cur;
			}
			cur = cur->_next;
		}
		return NULL;
	}
protected:
	void Swap(HashTable<K,V>& ht)
	{
		_tables.swap(ht._tables);
		swap(_size,ht._size);
	}
	void Destroy()
	{
		for (size_t i = 0; i < _tables.size(); ++i)
		{
			KVNode* cur = _tables[i];
			while (cur)
			{
				KVNode* tmp = cur;
				cur = cur->_next;
				delete tmp;
			}
			_tables[i] = NULL;
		}
	}
	void _CreateCapacity()
	{
		static const int _PrimeSize = 28;
		static const unsigned long _PrimeList[_PrimeSize] =
		{
			53ul, 97ul, 193ul, 389ul, 769ul,
			1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
			49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
			1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
			50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
		};
		if (_size == _tables.size())
		{
			HashTable<K,V> ht;
			for (int i = 0; i < _PrimeSize;++i)
			{
				if (_size < _PrimeList[i])
				{
					ht._tables.resize(_PrimeList[i]);
					break;
				}		
			}
			for (size_t i = 0; i < _size;++i)
			{
				KVNode* cur = _tables[i];
				while (cur)
				{	
					ht.Insert(cur->_key, cur->_value);
					cur = cur->_next;
				}
			}
			_tables.swap(ht._tables);
		}
	}
protected:
	vector<KVNode*> _tables;
	size_t _size;
};

void TestBucket()
{
	HashTable<int,int> ht(2);
	ht.Insert(1,25);
	ht.Insert(11, 35);
	ht.Insert(12, 21);
	ht.Insert(16, 36);
	ht.Insert(19, 81);
	ht.Insert(54, 0);
	//ht.Print();

	//ht.Remove(12);
	//ht.Print();

	//HashTableNode<int, int>* tmp = ht.Find(54);
	//cout << "Find?" << tmp->_key << ":" << tmp->_value << endl;

	HashTable<int, int> ht1(ht);
	ht1.Print();

	HashTable<int, int> ht2;
	ht2 = ht1;
	ht2.Print();

	HashTable<string, string> htstr(10);
	htstr.Insert("字典","dictionary");
	htstr.Insert("清除", "clear,destroy");
	htstr.Insert("手机", "mobilephone");
	htstr.Insert("电脑", "pc");
	htstr.Insert("吸血鬼", "vampire");
	htstr.Print();

	HashTable<string, string> htstr1(htstr);
	htstr1.Print();
}