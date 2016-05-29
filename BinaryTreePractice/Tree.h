#pragma once

enum status
{
	UNACCESS,
	ACCESS,
	TWINCE,
};

struct BinaryTreeNode
{
	int _data;
	BinaryTreeNode* _left;
	BinaryTreeNode* _right;

	status _status;

	BinaryTreeNode(const int& x)
		:_data(x)
		, _left(NULL)
		, _right(NULL)
		, _status(UNACCESS)
	{}
};

class BinaryTree
{
public:
	BinaryTree()
		:_root(NULL)
	{}
	BinaryTree(const int* a, size_t size)
	{
		size_t index = 0;
		_root = _CreatTree(a, size, index);
	}
	BinaryTreeNode* GetRoot()
	{
		return _root;
	}
protected:
	BinaryTreeNode* _CreatTree(const int* a, size_t size, size_t& index)
	{
		BinaryTreeNode* root = NULL;
		if (index <= size && a[index] != '#')
		{
			root = new BinaryTreeNode(a[index]);
			root->_left = _CreatTree(a, size, ++index);
			root->_right = _CreatTree(a, size, ++index);
		}
		return root;
	}
protected:
	BinaryTreeNode* _root;
};