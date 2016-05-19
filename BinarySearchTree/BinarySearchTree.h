#pragma once

template<class K, class V>
//����ṹ�壬���������Һ��ӽڵ㣬�ؼ��ֺ���ؼ����йص���Ϣ
//����ѧ��ѧ��(�ؼ���)��ѧ���ɼ�(��ؼ����йص���Ϣ)
struct BSTreeNode
{
	BSTreeNode<K, V>* _left;
	BSTreeNode<K, V>* _right;
	K _key;
	V _value;
	BSTreeNode(const K& key, const V& value)  //�вεĹ��캯��
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
			_root = new Node(key, value);      //�ղ�����û�����ݵ������ֱ�ӹ���һ���ڵ㸳�����ڵ�
		}
		else
		{
			Node* cur = _root;                //curָ����ڵ�
			Node* prev = NULL;                //prevָ��cur�ĸ��ڵ㣬��ʼ��Ϊ��
			while (cur)                       //��Ҫ����ڵ��λ��
			{
				if (cur->_key < key)          //�ȸýڵ���ڸýڵ������������
				{
					prev = cur;
					cur = cur->_right;
				}
				else if (cur->_key > key)     //�ȸýڵ�С�ڸýڵ������������
				{
					prev = cur;
					cur = cur->_left;
				}
				else                          //��ýڵ����ʱ����ʧ��
				{
					return false;
				}
			}
			Node* newnode = new Node(key, value); //�����½ڵ㲢������Ӧ��λ��
			if (prev->_key < key)
				prev->_right = newnode;
			else
				prev->_left = newnode;
		}
		return true;
	}
	bool InSert_R(const K& key, const V& value)   //ʹ�õݹ����ڵ�
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
			if (cur->_key < key)                //���ҵ�Ҫɾ���Ľڵ�
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
				if (cur->_left == NULL)        //���Ҫɾ���ڵ�cur������Ϊ��
				{                              //�ýڵ�cur�ĸ��ڵ�prevָ��cur���Һ���
					if (prev->_left == cur)
						prev->_left = cur->_right;
					else
						prev->_right = cur->_right;
					delete cur;                //ɾ���ڵ�
				}
				else if (cur->_right == NULL)  //���Ҫɾ���ڵ�cur���Һ���Ϊ��
				{                              //�ýڵ�cur�ĸ��ڵ�prevָ��cur������
					if (prev->_left == cur)
						prev->_left = cur->_right;
					else
						prev->_right = cur->_right;
					delete cur;                //ɾ���ڵ�
				}
				else                           //����ýڵ�cur�����Һ��Ӷ���Ϊ��
				{                              //�ҵ�cur�����������һ���ڵ�(���������)
					Node* next = cur->_right;
					prev = next;
					if (next->_left == NULL)   //case1:cur�Һ��ӵ�����Ϊ��
					{                          //��cur��cur���Һ��ӽ���
						swap(cur->_key, next->_key);
						swap(cur->_value, next->_value);
						cur->_right = next->_right; //��cur���Һ���ָ��cur�Һ��ӵ��Һ���
						delete next;           //ɾ��cur���Һ���
					}
					else                       //case2:cur�Һ��ӵ����Ӳ�Ϊ��
					{                          //ѭ���ҵ�cur�����������һ���ڵ�next
						while (next->_left)
						{
							prev = next;
							next = next->_left;
						}
						swap(cur->_key, next->_key); //����cur��next
						swap(cur->_value, next->_value);
						prev->_left = next->_right;  //��next���Һ�����Ϊnext���ڵ������
						delete next;                 //ɾ��next
					}
				}
			}
		}
		return false;
	}
	bool Remove_R(const K& key, const V& value)      //�ݹ�ʵ��ɾ���ڵ�
	{
		if (_root == NULL)
			return false;
		return _Remove_R(_root, key, value);
	}
	Node* Find(const K& key, const V& value)        //Ѱ��ָ���Ľڵ�
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
	Node* Find_R(const K& key, const V& value)      //�ݹ�Ѱ��ָ���Ľڵ�
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
			root = newnode;              //����ʹ�õ������ã�root�ı�
			return true;                 //����һ���root->_left��root->_rightҲ�ı�
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