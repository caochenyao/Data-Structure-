#pragma once

template<class K,class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	K _key;
	V _value;
	int _bf;

	AVLTreeNode(const K& key,const V& value)
		:_left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _key(key)
		, _value(value)
		, _bf(0)
	{}
};

template<class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}
public:
	bool Insert(const K& key,const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}
			
		Node* parent = NULL;
		Node* cur = _root;
		bool Isadjust = false;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}	
		}

		cur = new Node(key,value);
		cur->_parent = parent;
		if (cur->_key < parent->_key)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}

		while (parent)
		{
			
			if (cur == parent->_left)
			{
				parent->_bf--;
				if (parent->_bf == 0)
					break;
			}
			else if (cur == parent->_right)
			{
				parent->_bf++;
				if (parent->_bf == 0)
					break;
			}

			if (parent->_bf > 1 || parent->_bf < -1)
			{
				Isadjust = true;
				if (parent->_bf > 1)
				{
					if (parent->_right->_bf == 1)
					{
						//情况为2,1,0;为左单旋
						_RotateL(parent);
					}
					else if (parent->_right->_bf == -1)
					{
						//情况为2,-1,0;为右左双旋
						_RotateRL(parent);
					}
				}
				else
				{
					if (parent->_left->_bf == -1)
					{
						//情况为-2,-1,0;为右单旋
						_RotateR(parent);
					}
					else if (parent->_left->_bf == 1)
					{
						//情况为-2,1,0;为为左右双旋
						_RotateLR(parent);
					}
				}
				if (parent->_parent == NULL)
				{
					_root = parent;
					return true;
				}
			}

			Node* ppNode = parent->_parent;
			if (Isadjust && ppNode)
			{
				if (parent->_key < ppNode->_key)
				{
					ppNode->_left = parent;
				}
				else
				{
					ppNode->_right = parent;
				}
				return true;
			}
			cur = parent;
			parent = cur->_parent;
		}
		return true;
	}
public:
	void _RotateL(Node*& parent)
	{
		Node* subR = parent->_right; //parent为_bf为2的节点,subR为_bf为1的节点
		Node* subRL = subR->_left;   //subRL为subR的左孩子

		parent->_right = subRL;      //将subRL链为parent的右孩子
		if (subRL)
			subRL->_parent = parent;

		subR->_parent = parent->_parent;//先将parent的父节点链为subR的父节点
		parent->_parent = subR;  //再将subR作为parent的父节点
		subR->_left = parent;

		parent->_bf = subR->_bf = 0;
		parent = subR;                //将subR赋为parent(此处用的是引用,此处变,上面的cur也会变)
	    
	}
	void _RotateR(Node*& parent)
	{
		//右单旋与左单旋相似
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		subL->_parent = parent->_parent;
		parent->_parent = subL;
		subL->_right = parent;

		parent->_bf = subL->_bf = 0;
		parent = subL;
	}
	void _RotateRL(Node*& parent)
	{
		/*_RotateR(parent->_right);
		_RotateL(parent);*/
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		//右旋
		subR->_left = subRL->_right;
		if (subRL->_right)
			subRL->_right->_parent = subR;
		parent->_right = subRL;
		subRL->_right = subR;
		//改变平衡因子
		if (subRL->_bf == 0 || subRL->_bf == 1)
		{
			subR->_bf = 0;
		}
		else
		{
			subR->_bf = 1;
		}
		//左旋
		parent->_right = subRL->_left;
		if (subRL->_left)
			subRL->_left->_parent = parent;
		subRL->_parent = parent->_parent;
		subRL->_left = parent;
		parent->_parent = subRL;
		//改变平衡因子
		if (subRL->_bf == 0 || subRL->_bf == -1)
		{
			parent->_bf = 0;
		}
		else
		{
			parent->_bf = -1;
		}

		subRL->_bf = 0;
		parent = subRL;

	}
	void _RotateLR(Node*& parent)
	{
		/*_RotateL(parent->_left);
		_RotateR(parent);*/
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		//左旋
		subL->_right = subLR->_left;
		if (subLR->_left)
			subLR->_left->_parent = subL;
		parent->_left = subLR;
		subLR->_left = subL;
		//改变平衡因子
		if (subLR->_bf == 0 || subLR->_bf == -1)
		{
			subL->_bf = 0;
		}
		else
		{
			subL->_bf = -1;
		}
		//右旋
		parent->_left = subLR->_right;
		if (subLR->_right)
			subLR->_right->_parent = parent;
		subLR->_parent = parent->_parent;
		subLR->_right = parent;
		parent->_parent = subLR;
		//改变平衡因子
		if (subLR->_bf == 0 || subLR->_bf == 1)
		{
			parent->_bf = 0;
		}
		else
		{
			parent->_bf = 1;
		}

		subLR->_bf = 0;
		parent = subLR;
	}
	int Hight()
	{
		return _Hight(_root);
	}
	bool IsBalance()
	{
		return _IsBalance(_root);
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
protected:
	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;

		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}
	bool _IsBalance(Node* root)
	{
		if (root == NULL)
			return true;

		int left = _Hight(root->_left);
		int right = _Hight(root->_right);
		int poor = right-left;
		bool IsBalance = abs(poor) < 2 && root->_bf == poor;

		return _IsBalance(root->_left) && _IsBalance(root->_right) && IsBalance;
	}
	int _Hight(Node* root)
	{
		if (root == NULL)
			return 0;

		int left = _Hight(root->_left)+1;
		int right = _Hight(root->_right)+1;

		return left > right ? left : right;
	}
protected:
	Node* _root;
};

void Test1()
{
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };

	AVLTree<int, int> t;
	for (int i = 0; i < sizeof(a) / sizeof(int);++i)
	{
		t.Insert(a[i],i);
	}

	t.InOrder();
	cout<<"IsBalance:"<<t.IsBalance()<<endl;
}

void Test2()
{
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };

	AVLTree<int, int> t;
	for (int i = 0; i < sizeof(a) / sizeof(int); ++i)
	{
		t.Insert(a[i], i);
	}

	t.InOrder();
	cout << "IsBalance:" << t.IsBalance() << endl;
}