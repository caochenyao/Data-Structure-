#pragma once

enum Color
{
	RED,
	BLACK
};

template<class K,class V>
struct RBTreeNode
{
	RBTreeNode<K, V>* _left;    //左孩子
	RBTreeNode<K, V>* _right;   //右孩子
	RBTreeNode<K, V>* _parent;  //父亲
    
	K _key;                     //关键字
	V _value;                   //与关键字有关的信息

	Color _col;                 //节点颜色
	//半缺省的构造函数,节点颜色默认为红色,如果出现连续红色节点的话可以调整
	RBTreeNode(const K& key,const V& value,const Color col = RED)
		:_left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _key(key)
		, _value(value)
		, _col(col)
	{}
};

template<class K,class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree()
		:_root(NULL)
	{}
	bool Insert(const K& key,const V& value)
	{
		if (_root == NULL)                       //根节点为空直接插入节点
		{
			_root = new Node(key, value, BLACK); //根节点必须是黑色节点
			return true;
		}
		//找到新插入节点的位置
		Node* parent = NULL;
		Node* cur = _root;
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
				return false;
		}
		//插入新的节点
		cur = new Node(key,value);
		cur->_parent = parent;
		if (parent->_key < key)
			parent->_right = cur;
		else
			parent->_left = cur;

		
		Node* uncle = NULL;
		while (parent)
		{
			//判断是否合法(也就是是否有连续的红节点)
			if (cur->_col == RED && parent->_col == RED)
			{
				//找到叔叔节点
				Node* grandpa = parent->_parent;
				if (grandpa->_key < parent->_key)
					uncle = grandpa->_left;
				else
					uncle = grandpa->_right;

				//分条件判断
				//1.cur为红,parent为红,grandpa为黑,uncle存在且为红
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandpa->_col = RED;
					if (grandpa->_parent && grandpa->_parent->_col == RED)
					{
						cur = grandpa;
						parent = cur->_parent;
					}
					else
					{
						break;
					}
				}
				else  //uncle不存在或者为黑
				{
					if (parent == grandpa->_left)
					{
						if (cur == parent->_left)
						{
							//右单旋
							_RotateR(grandpa);
						}
						else
						{
							//左右双旋
							_RotateLR(grandpa);
						}
						grandpa->_col = BLACK;
						grandpa->_right->_col = RED;
					}
					else
					{
						if (cur == parent->_right)
						{
							//左单旋
							_RotateL(grandpa);
						}
						else
						{
							//右左双旋
							_RotateRL(grandpa);
						}
						grandpa->_col = BLACK;
						grandpa->_left->_col = RED;
					}

					Node* ppNode = grandpa->_parent;
					if (ppNode == NULL)
					{
						_root = grandpa;
						break;
					}
					//使之前的grandpa的父节点指向现在的grandpa
					else
					{
						if (ppNode->_key > grandpa->_key)
							ppNode->_left = grandpa;
						else
							ppNode->_right = grandpa;
						break;
					}	
				}	
			}
			else
			{
				break;
			}
		}
		//调整之后可能会出现根节点变为红色节点的情况,要将根节点重新置为黑色
		_root->_col = BLACK;   
		return true;
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	bool IsBalance()    //判断树是否平衡
	{
		//1.最长路径不超过最短路径的2倍
		//2.对于每个节点，该节点到其所有后代叶节点的简单路径上，均包含相同数目的黑色节点
		//3.没有连续的红色节点
		return BlackCount() && Color();
	}
	bool BlackCount()
	{
		int left = 0;
		int right = 0;
		return _BlackCount(_root,left,right);
	}
	bool Color()
	{
		return _Color(_root);
	}
protected:
	bool _BlackCount(Node* root,int& left,int& right)
	{
		if (root == NULL)
			return true;
		if (root->_col == BLACK)
		{
			left = _BlackCount(root->_left,left,right);
			right = _BlackCount(root->_right, left, right);
		}
		else
		{
			_BlackCount(root->_left, left, right);
			_BlackCount(root->_right, left, right);
		}
		if (left == right)
			return true;
		return false;
	}

	bool _Color(Node* root)
	{
		if (root == NULL)
			return true;
		return _Color(root->_left) && _Color(root->_right) && Red(root);
	}

	bool Red(Node* root)
	{
		if (root->_col == RED && root->_parent && root->_left && root->_right)
			return (root->_col != root->_parent->_col &&
			        root->_col != root->_left->_col &&
			        root->_col != root->_right->_col);
		return true;
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}
	void _RotateR(Node*& grandpa)
	{
		Node* parent = grandpa->_left;       //得到parent节点
		Node* subR = parent->_right;         //得到parent的右孩子

		grandpa->_left = subR;               //将subR作为grandpa的左孩子
		if (subR)
			subR->_parent = grandpa;
		parent->_right = grandpa;            //将grandpa作为parent的右孩子
		parent->_parent = grandpa->_parent;  //parent指向grandpa的父节点
		grandpa->_parent = parent;           //parent变为grandpa的父节点

		grandpa = parent;
	}
	void _RotateL(Node*& grandpa)
	{
		Node* parent = grandpa->_right;      //得到parent节点
		Node* subL = parent->_left;          //得到parent的左孩子

		grandpa->_right = subL;              //将subL作为grandpa的右孩子
		if (subL)
			subL->_parent = grandpa;
		parent->_left = grandpa;             //将grandpa作为parent的左孩子
		parent->_parent = grandpa->_parent;  //parent指向grandpa的父节点
		grandpa->_parent = parent;           //parent变为grandpa的父节点

		grandpa = parent;
	}
	void _RotateRL(Node*& grandpa)
	{
		_RotateR(grandpa->_right);
		_RotateL(grandpa);
	}
	void _RotateLR(Node*& grandpa)
	{
		_RotateL(grandpa->_left);
		_RotateR(grandpa);
	}
protected:
	Node* _root;
};

void Test()
{
	RBTree<int, int> rb;
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	for (int i = 0; i < sizeof(a)/sizeof(int);++i)
	{
		rb.Insert(a[i],i);
	}

	rb.InOrder();
}