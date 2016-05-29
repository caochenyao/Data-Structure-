#pragma once
#include"Tree.h"
#include<queue>
//判断一个二叉树是否是完全二叉树
bool IsComplete(const int* a,const int n)
{
	assert(a);
	BinaryTree bt(a,n);
	BinaryTreeNode* root = bt.GetRoot();

	queue<BinaryTreeNode*> q;
	q.push(root);

	while (!q.empty())
	{
		BinaryTreeNode* cur = q.front();
		q.pop();

		if (cur->_left)
			q.push(cur->_left);
		if (cur->_right)
			q.push(cur->_right);

		if ((cur->_left == NULL && cur->_right == NULL) || (cur->_left && cur->_right == NULL))
		{
			while (!q.empty())
			{
				cur = q.front();
				q.pop();
				if (cur->_left == NULL && cur->_right == NULL)
					continue;
				else
					return false;
			}
		}
		else if (cur->_left && cur->_right)
			continue;
		else
			return false;
	}
	return true;
}

void _MirrorBinaryTree(BinaryTreeNode* root)
{
	if (root == NULL)
		return;
	swap(root->_left, root->_right);
	_MirrorBinaryTree(root->_left);
	_MirrorBinaryTree(root->_right);
}
//二叉树的镜像
void MirrorBinaryTree(const int* a,const int n)
{
	assert(a);
	BinaryTree bt(a, n);
	BinaryTreeNode* root = bt.GetRoot();

	_MirrorBinaryTree(root);
}

void _ChangeBinaryTree(BinaryTreeNode* root,BinaryTreeNode*& prev)
{
	if (root == NULL)
		return;
	_ChangeBinaryTree(root->_left, prev);

	root->_left = prev;
	if (prev)
		prev->_right = root;
	prev = root;

	_ChangeBinaryTree(root->_right, prev);
}
//将二叉搜索树变为双向链表
void ChangeBinaryTree(const int* a,const int n)
{
	assert(a);
	BinaryTree bt(a, n);
	BinaryTreeNode* root = bt.GetRoot();

	BinaryTreeNode* prev = NULL;
	_ChangeBinaryTree(root, prev);

	while (root)
	{
		prev = root;
		root = root->_left;
	}

	while (prev)
	{
		cout << prev->_data << "->";
		prev = prev->_right;
	}
	cout << "NULL" << endl;
}

void IsCompleteTest()
{
	int a1[] = {5,2,4,8,'#','#',9,'#','#',5,'#','#',3,6,'#','#',7,'#','#'};
	bool Is = IsComplete(a1, sizeof(a1)/sizeof(int));
	cout << "IsCompete?:" << Is << endl;

	int a2[] = {1,2,4,8,'#','#',9,'#','#',5,'#','#',3,'#',7,'#','#'};
	Is = IsComplete(a2, sizeof(a2) / sizeof(int));
	cout << "IsCompete?:" << Is << endl;
}

void MirrorTest()
{
	int a[] = {1,2,4,8,'#','#',9,'#','#',5,'#','#',3,6,'#','#',7,'#','#'};
	MirrorBinaryTree(a, sizeof(a)/sizeof(int));
}

void ChangeTest()
{
	//int a[] = {5,3,2,1,'#','#','#',4,'#','#',7,6,'#','#',8,'#',9,'#','#'};
	int a[] = { 4, 2, 1, '#', '#', 3, '#', '#', 6, 5, '#', '#','#' };

	ChangeBinaryTree(a, sizeof(a)/sizeof(int));
}