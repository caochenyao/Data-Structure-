#pragma once
#include<assert.h>
#include<queue>

template<class T>
struct BinaryTreeNode                   //�������ṹ
{
	T _data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;
	BinaryTreeNode(const T& x)         //�ڵ�Ĺ��캯��
		:_data(x)
		, _left(NULL)
		, _right(NULL)
	{
	}
};

template<class T>
class BinaryTree
{
public:
	BinaryTree()                       //�޲εĹ��캯��
		:_root(NULL)
	{
	}
	BinaryTree(const T* a,size_t size) //�вεĹ��캯��
	{
		size_t index = 0;
		_root = CreateTree(a,size,index);
	}
	void PrevOrder()                  //�������
	{
		_PrevOrder(_root);
		cout << endl;
	}
	void InOrder()                    //�������
	{
		_InOrder(_root);
		cout << endl;
	}
	void PostOrder()                  //�������
	{
		_PostOrder(_root);
		cout << endl;
	}
	void LevelOrder()                 //��α���(ͨ��������ʵ��)
	{
		queue<BinaryTreeNode<T>*> q;
		if (_root == NULL)
		{
			return;
		}
		q.push(_root);
		while (!q.empty())
		{
			BinaryTreeNode<T>* root = q.front();
			q.pop();
			if (root->_left)          //������ӵĽڵ�����ӻ��Һ��Ӳ�Ϊ��,�䲻Ϊ�յĺ�������� 
			{
				q.push(root->_left);
			}
			if (root->_right)
			{
				q.push(root->_right);
			}
			cout << root->_data << " ";//��ӡ���ӵĽڵ�->�൱�ڱ������ӵĽڵ�
		}
		cout << endl;
	}
	size_t Size()
	{ 
		return _Size(_root);
	}
	size_t Depth()                    //��������������
	{
		return _Depth(_root);
	}
	BinaryTreeNode<T>* Find(const T& x)//�ò�α���Ѱ�ҷ��������Ľڵ�
	{
		queue<BinaryTreeNode<T>*> q;
		if (_root == NULL)
		{
			return NULL;
		}
		q.push(_root);
		while (!q.empty())
		{
			BinaryTreeNode<T>* root = q.front();
			q.pop();
			if (root->_left)
			{
				q.push(root->_left);
			}
			if (root->_right)
			{
				q.push(root->_right);
			}
			if (root->_data == x)
			{
				return root;
			}
		}
		return NULL;
		cout << endl;
	}
protected:
	size_t _Depth(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
		{
			return 0;
		}
		size_t leftdepth = 1;
		size_t rightdepth = 1;
		leftdepth += _Depth(root->_left);
		rightdepth += _Depth(root->_right);
		return (leftdepth > rightdepth) ? leftdepth : rightdepth;
	}
	size_t _Size(BinaryTreeNode<T>* root)
	{
		if (root == NULL)
			return 0;
		return (_Size(root->_left) + _Size(root->_right) + 1);
	}
	void _PostOrder(BinaryTreeNode<T>* root)
	{
		BinaryTreeNode<T>* curroot = root;
		if (curroot == NULL)
		{
			return;
		}
		_PostOrder(curroot->_left);	
		_PostOrder(curroot->_right);
		cout << curroot->_data << " ";
	}
	void _InOrder(BinaryTreeNode<T>* root)
	{
		BinaryTreeNode<T>* curroot = root;
		if (curroot == NULL)
		{
			return;
		}
		_InOrder(curroot->_left);
		cout << curroot->_data << " ";
		_InOrder(curroot->_right);
	}
	void _PrevOrder(BinaryTreeNode<T>* root)
	{
		BinaryTreeNode<T>* curroot = root;
		if (curroot == NULL)
		{
			return;
		}
		cout << curroot->_data << " ";
		_PrevOrder(curroot->_left);
		_PrevOrder(curroot->_right);
	}
	//����������(indexΪ�����±�)
	BinaryTreeNode<T>* CreateTree(const T*a,size_t size,size_t& index)
	{
		assert(a);
		BinaryTreeNode<T>* newroot = NULL;
		if (index < size && a[index] != '#')
		{
			newroot = new BinaryTreeNode<T>(a[index]);
			newroot->_left = CreateTree(a, size, ++index);
			newroot->_right = CreateTree(a, size, ++index);
		}
		return newroot;
	}
protected:
	BinaryTreeNode<T>* _root;
};

void Test()
{
	int a[10] = {1,2,3,'#','#',4,'#','#',5,6};
	BinaryTree<int> t1(a,10);
	t1.PrevOrder();
	t1.InOrder();
	t1.PostOrder();
	t1.LevelOrder();
	cout << t1.Size() << endl;
	cout << t1.Depth() << endl;
	cout << t1.Find(3)->_data << endl;
}