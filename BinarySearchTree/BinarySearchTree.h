#pragma once

template<class K, class V>
//定义结构体，包含有左右孩子节点，关键字和与关键字有关的信息
//例如学生学号(关键字)和学生成绩(与关键字有关的信息)
struct BSTreeNode
{
	BSTreeNode<K, V>* _left;
	BSTreeNode<K, V>* _right;
	K _key;
	V _value;
	BSTreeNode(const K& key, const V& value)  //有参的构造函数
		:_left(NULL)
		, _right(NULL)
		, _key(key)
		, _value(value)
	{}
};

template<class K, class V>
class BSTree
{
	typedef BSTreeNode<K, V> Node;
public:
	BSTree()
		:_root(NULL)
	{}
public:
	bool InSert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);      //刚插入是没有数据的情况，直接构造一个节点赋给根节点
		}
		else
		{
			Node* cur = _root;                //cur指向根节点
			Node* prev = NULL;                //prev指向cur的父节点，初始化为空
			while (cur)                       //找要插入节点的位置
			{
				if (cur->_key < key)          //比该节点大在该节点的右子树上找
				{
					prev = cur;
					cur = cur->_right;
				}
				else if (cur->_key > key)     //比该节点小在该节点的左子树上找
				{
					prev = cur;
					cur = cur->_left;
				}
				else                          //与该节点相等时插入失败
				{
					return false;
				}
			}
			Node* newnode = new Node(key, value); //构造新节点并插入相应的位置
			if (prev->_key < key)
				prev->_right = newnode;
			else
				prev->_left = newnode;
		}
		return true;
	}
	bool InSert_R(const K& key, const V& value)   //使用递归插入节点
	{
		return _InSert_R(_root, key, value);
	}
	bool Remove(const K& key, const V& value)
	{
		if (_root == NULL)
			return false;
		Node* cur = _root;
		Node* prev = NULL;
		while (cur)
		{
			if (cur->_key < key)                //先找到要删除的节点
			{
				prev = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				prev = cur;
				cur = cur->_left;
			}
			else
			{
				if (cur->_left == NULL)        //如果要删除节点cur的左孩子为空
				{                              //该节点cur的父节点prev指向cur的右孩子
					if (prev->_left == cur)
						prev->_left = cur->_right;
					else
						prev->_right = cur->_right;
					delete cur;                //删除节点
				}
				else if (cur->_right == NULL)  //如果要删除节点cur的右孩子为空
				{                              //该节点cur的父节点prev指向cur的左孩子
					if (prev->_left == cur)
						prev->_left = cur->_right;
					else
						prev->_right = cur->_right;
					delete cur;                //删除节点
				}
				else                           //如果该节点cur的左右孩子都不为空
				{                              //找到cur中序遍历的下一个节点(分两种情况)
					Node* next = cur->_right;
					prev = next;
					if (next->_left == NULL)   //case1:cur右孩子的左孩子为空
					{                          //将cur与cur的右孩子交换
						swap(cur->_key, next->_key);
						swap(cur->_value, next->_value);
						cur->_right = next->_right; //将cur的右孩子指向cur右孩子的右孩子
						delete next;           //删除cur的右孩子
					}
					else                       //case2:cur右孩子的左孩子不为空
					{                          //循环找到cur中序遍历的下一个节点next
						while (next->_left)
						{
							prev = next;
							next = next->_left;
						}
						swap(cur->_key, next->_key); //交换cur与next
						swap(cur->_value, next->_value);
						prev->_left = next->_right;  //将next的右孩子作为next父节点的左孩子
						delete next;                 //删除next
					}
				}
			}
		}
		return false;
	}
	bool Remove_R(const K& key, const V& value)      //递归实现删除节点
	{
		if (_root == NULL)
			return false;
		return _Remove_R(_root, key, value);
	}
	Node* Find(const K& key, const V& value)        //寻找指定的节点
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
				cur = cur->_right;
			else if (cur->_key > key)
				cur = cur->_left;
			else
				return cur;
		}
		return NULL;
	}
	Node* Find_R(const K& key, const V& value)      //递归寻找指定的节点
	{
		return _Find_R(_root, key);
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
protected:
	void _InOrder(Node* root)
	{
		Node* node = root;
		if (node == NULL)
			return;
		_InOrder(node->_left);
		cout << node->_key << "->" << node->_value << " ";
		_InOrder(node->_right);
	}
	Node* _Find_R(Node* root, const K& key)
	{
		if (root == NULL)
			return NULL;
		if (root->_key < key)
			return _Find_R(root->_right, key);
		else if (root->_key > key)
			return _Find_R(root->_left, key);
		else
			return root;
	}
	bool _Remove_R(Node*& root, const K& key, const V& value)
	{
		if (root->_key < key)
			return _Remove_R(root->_right, key, value);
		else if (root->_key > key)
			return _Remove_R(root->_left, key, value);
		else
		{
			Node* cur = root;
			if (cur->_left == NULL)
			{
				root = cur->_right;
				delete cur;
			}
			else if (cur->_right == NULL)
			{
				root = cur->_left;
				delete cur;
			}
			else
			{
				Node* next = cur->_right;
				if (next->_left == NULL)
				{
					cur->_key = next->_key;
					cur->_value = next->_value;
					cur->_right = next->_right;
					delete next;
				}
				else
				{
					Node* prev = NULL;
					while (next->_left)
					{
						prev = next;
						next = next->_left;
					}
					cur->_key = next->_key;
					cur->_value = next->_value;
					prev->_left = next->_right;
					delete next;
				}
			}
			return true;
		}
		return false;
	}
	bool _InSert_R(Node*& root, const K& key, const V& value)
	{
		if (root == NULL)
		{
			Node* newnode = new Node(key, value);
			root = newnode;              //这里使用的是引用，root改变
			return true;                 //则上一层的root->_left或root->_right也改变
		}
		if (root->_key < key)
			return _InSert_R(root->_right, key, value);
		else if (root->_key > key)
			return _InSert_R(root->_left, key, value);
		else
			return false;
	}
protected:
	Node* _root;
};
void Test()
{
	BSTree<int, int> t;
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	for (int i = 0; i < sizeof(a) / sizeof(int); ++i)
	{
		//t.InSert(a[i], a[i]);
		t.InSert_R(a[i], a[i]);
	}

	t.Remove(5, 5);
	t.InOrder();
	t.Remove_R(7, 7);
	t.InOrder();

	BSTreeNode<int, int>* node = t.Find(6, 6);
	cout << node->_key << "->" << node->_value << endl;
	node = t.Find_R(10, 10);
	t.InOrder();
}