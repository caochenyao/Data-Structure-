#pragma once
#pragma warning(disable:4018)

template<class K,int M = 3>
struct BTreeNode
{
	K _key[M];                    //关键字数组
	BTreeNode<K, M>* _sub[M+1];   //孩子数组
	size_t _size;                 //孩子个数

	BTreeNode<K, M>* _parent;     //父亲

	BTreeNode()
		:_size(0)
		, _parent(NULL)
	{
		for (int i = 0; i < M + 1;++i)
		{
			_sub[i] = NULL;
		}
	}
};

template<class K,class V>
struct Pair
{
	K _first;
	V _second;
	Pair(const K& k = K(),const V& v = V())
		:_first(k)
		, _second(v)
	{}
};

template<class K,int M = 3>
class BTree
{
	typedef BTreeNode<K, M> Node;
public:
	BTree()
		:_root(NULL)
	{}
	bool Insert(const K& key)
	{
		//当根节点为NULL
		if (_root == NULL)
		{
			_root = new Node;
			_root->_key[0] = key;
			_root->_size++;
			return true;
		}

		//当根节点不为NULL,找到要插入的节点
		Pair<Node*, int> pair = Find(key);

		//pair->_second为-1时说明没有找到这个值，可以插入
		if (pair._second != -1)
		{
			return false;
		}
		
		Node* cur = pair._first;
		Node* right = NULL;
		K k = key;
		while (cur)
		{
			int index = cur->_size - 1;
			while (index > -1)
			{
				if (cur->_key[index] > k)
				{
					cur->_key[index + 1] = cur->_key[index];
					cur->_sub[index + 2] = cur->_sub[index + 1];
					index--;
				}
				else
				{
					break;
				}
			}
			cur->_sub[index+2] = right;
			cur->_key[index+1] = k;
			cur->_size++;

			//判断是否需要分解
			if (cur->_size < M)
			{
				return true;
			}
			else
			{
				int boundary = cur->_size/2;	
				k = cur->_key[boundary];
				right = new Node;
				int i = 0;
				size_t size = cur->_size;
				cur->_size--;
				for (int j = boundary + 1; j < size; ++j)
				{
					right->_key[i] = cur->_key[j];
					right->_sub[i] = cur->_sub[j];
					if (right->_sub[i])
					    right->_sub[i]->_parent = right;
					++i;
					cur->_size--;
					right->_size++;
				}
				right->_sub[i] = cur->_sub[size];
				if (right->_sub[i])
				    right->_sub[i]->_parent = right;
				if (cur == _root)
				{
					_root = new Node;
					_root->_key[0] = k;
					_root->_size++;
					_root->_sub[0] = cur;
					_root->_sub[1] = right;
					cur->_parent = _root;
					right->_parent = _root;
					return true;
				}
				
				cur = cur->_parent;
			}
		}
		return true;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
protected:
	Pair<Node*, int> Find(const K& key)
	{
		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			int i = 0;
			while(i < cur->_size && cur->_key[i] < key)
			{
				++i;
			}
			if (key == cur->_key[i])
			{
				return Pair<Node*, int>(cur, i);
			}
			parent = cur;
			cur = cur->_sub[i];
		}
		return Pair<Node*, int>(parent,-1);
	}
	
	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;
		for (int i = 0; i < root->_size;++i)
		{
			_InOrder(root->_sub[i]);
			cout << root->_key[i] << endl;
		}
	}
protected:
	Node* _root;
};

void Test()
{
	BTree<int, 3> bt;
	int a[] = { 53, 75, 139, 49, 145, 36, 101 };
	for (int i = 0; i < sizeof(a)/sizeof(int);++i)
	{
		bt.Insert(a[i]);
	}

	bt.InOrder();
}