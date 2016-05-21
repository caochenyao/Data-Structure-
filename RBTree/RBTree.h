#pragma once

enum Color
{
	RED,
	BLACK
};

template<class K,class V>
struct RBTreeNode
{
	RBTreeNode<K, V>* _left;    //����
	RBTreeNode<K, V>* _right;   //�Һ���
	RBTreeNode<K, V>* _parent;  //����
    
	K _key;                     //�ؼ���
	V _value;                   //��ؼ����йص���Ϣ

	Color _col;                 //�ڵ���ɫ
	//��ȱʡ�Ĺ��캯��,�ڵ���ɫĬ��Ϊ��ɫ,�������������ɫ�ڵ�Ļ����Ե���
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
		if (_root == NULL)                       //���ڵ�Ϊ��ֱ�Ӳ���ڵ�
		{
			_root = new Node(key, value, BLACK); //���ڵ�����Ǻ�ɫ�ڵ�
			return true;
		}
		//�ҵ��²���ڵ��λ��
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
		//�����µĽڵ�
		cur = new Node(key,value);
		cur->_parent = parent;
		if (parent->_key < key)
			parent->_right = cur;
		else
			parent->_left = cur;

		
		Node* uncle = NULL;
		while (parent)
		{
			//�ж��Ƿ�Ϸ�(Ҳ�����Ƿ��������ĺ�ڵ�)
			if (cur->_col == RED && parent->_col == RED)
			{
				//�ҵ�����ڵ�
				Node* grandpa = parent->_parent;
				if (grandpa->_key < parent->_key)
					uncle = grandpa->_left;
				else
					uncle = grandpa->_right;

				//�������ж�
				//1.curΪ��,parentΪ��,grandpaΪ��,uncle������Ϊ��
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
				else  //uncle�����ڻ���Ϊ��
				{
					if (parent == grandpa->_left)
					{
						if (cur == parent->_left)
						{
							//�ҵ���
							_RotateR(grandpa);
						}
						else
						{
							//����˫��
							_RotateLR(grandpa);
						}
						grandpa->_col = BLACK;
						grandpa->_right->_col = RED;
					}
					else
					{
						if (cur == parent->_right)
						{
							//����
							_RotateL(grandpa);
						}
						else
						{
							//����˫��
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
					//ʹ֮ǰ��grandpa�ĸ��ڵ�ָ�����ڵ�grandpa
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
		//����֮����ܻ���ָ��ڵ��Ϊ��ɫ�ڵ�����,Ҫ�����ڵ�������Ϊ��ɫ
		_root->_col = BLACK;   
		return true;
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	bool IsBalance()    //�ж����Ƿ�ƽ��
	{
		//1.�·�����������·����2��
		//2.����ÿ���ڵ㣬�ýڵ㵽�����к��Ҷ�ڵ�ļ�·���ϣ���������ͬ��Ŀ�ĺ�ɫ�ڵ�
		//3.û�������ĺ�ɫ�ڵ�
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
		Node* parent = grandpa->_left;       //�õ�parent�ڵ�
		Node* subR = parent->_right;         //�õ�parent���Һ���

		grandpa->_left = subR;               //��subR��Ϊgrandpa������
		if (subR)
			subR->_parent = grandpa;
		parent->_right = grandpa;            //��grandpa��Ϊparent���Һ���
		parent->_parent = grandpa->_parent;  //parentָ��grandpa�ĸ��ڵ�
		grandpa->_parent = parent;           //parent��Ϊgrandpa�ĸ��ڵ�

		grandpa = parent;
	}
	void _RotateL(Node*& grandpa)
	{
		Node* parent = grandpa->_right;      //�õ�parent�ڵ�
		Node* subL = parent->_left;          //�õ�parent������

		grandpa->_right = subL;              //��subL��Ϊgrandpa���Һ���
		if (subL)
			subL->_parent = grandpa;
		parent->_left = grandpa;             //��grandpa��Ϊparent������
		parent->_parent = grandpa->_parent;  //parentָ��grandpa�ĸ��ڵ�
		grandpa->_parent = parent;           //parent��Ϊgrandpa�ĸ��ڵ�

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