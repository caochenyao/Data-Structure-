#pragma once
#include"Tree.h"
#include<stack>

#pragma warning(disable:4715)

//找路径，将路径压入栈中
bool Find(BinaryTreeNode* root, BinaryTreeNode* x, stack<BinaryTreeNode*>& s)
{
	if (root == NULL)
		return false;
	
	s.push(root);

	bool left = Find(root->_left, x, s);
	bool right = Find(root->_right, x, s);

	if (root == x)
		return true;

	if (left || right)
		return true;
	
	s.pop();
	return false;
}
//使用状态机(较麻烦)
//void Find(BinaryTreeNode* x, stack<BinaryTreeNode*>& s)
//{
//	BinaryTreeNode* cur = s.top();
//	s.pop();
//
//	while (cur || !s.empty())
//	{
//		while (cur)
//		{
//			if (cur->_status == UNACCESS)  //没有遍历过的再入栈
//			{
//				s.push(cur);
//				cur->_status = ACCESS;
//			}
//			
//			if (cur == x)
//				return;
//			else
//				cur = cur->_left;  
//		}
//		if (!s.empty())
//		{
//			BinaryTreeNode* top = s.top();
//			s.pop();
//
//			cur = top->_right;
// 
//			if (cur && top->_status != TWINCE) //如果某节点的右孩子不为空且不是已入栈两次，则将该节点再次入栈
//			{
//				s.push(top);
//				top->_status = TWINCE;
//			}	
//		}
//	}
//}

//找祖先节点
BinaryTreeNode* AncestorNode(BinaryTree& bt, BinaryTreeNode* x1, BinaryTreeNode* x2)
{
	stack<BinaryTreeNode*> s1;
	stack<BinaryTreeNode*> s2;
	BinaryTreeNode* root = bt.GetRoot();

	bool b1 = Find(root, x1, s1);
	bool b2 = Find(root, x2, s2);

	if (b1 && b2)
	{
		int size = abs((int)(s1.size() - s2.size()));
		if (s1.size() > s2.size())
		{
			while (size-- > 0)
			{
				s1.pop();
			}
		}
		else
		{
			s2.pop();
		}

		int Size = s1.size();
		while (Size-- > 0)
		{
			BinaryTreeNode* top1 = s1.top();
			BinaryTreeNode* top2 = s2.top();

			if (top1 == top2)
				return top1;
			else
			{
				s1.pop();
				s2.pop();
			}
		}
	}
	
	return NULL;
}

BinaryTreeNode* _FindNode(BinaryTreeNode* root,int data)
{
	if (root == NULL)
		return NULL;
	else if (root->_data == data)
		return root;
	else
	{
		BinaryTreeNode* ret = _FindNode(root->_left,data);
		if (ret)
			return ret;
		else
			return _FindNode(root->_right,data);
	}
}

BinaryTreeNode* FindNode(BinaryTree& bt,int data)
{
	BinaryTreeNode* root = bt.GetRoot();

	BinaryTreeNode* ret = _FindNode(root,data);

	if (ret)
		return ret;
	else
		return NULL;
}

//找最近的公共祖先
void FindAncestor(const int* a, const int n)
{
	assert(a);
	BinaryTree bt(a, n);
	BinaryTreeNode* node1 = FindNode(bt, 4);
	BinaryTreeNode* node2 = FindNode(bt, 1);

	BinaryTreeNode* ancestor = AncestorNode(bt,node1,node2);

	cout << "Ancestor?:" << " ";
	if (ancestor)
		cout << ancestor->_data << endl;
	else
		cout << "NULL" << endl;
}

int _IsBalance(BinaryTreeNode* root)
{
	if (root == NULL)
		return 0;
	int left = _IsBalance(root->_left);
	int right = _IsBalance(root->_right);

	if (abs(left - right) > 1)
		return -1;
	else
		return left > right ? (left+1) : (right+1);
}
//判断是否是平衡二叉树
bool IsBalance(const int* a, const int n)
{
	assert(a);
	BinaryTree bt(a, n);
	BinaryTreeNode* root = bt.GetRoot();

	int isbalance = _IsBalance(root);
	if (isbalance > 0)
		return true;
	else
		return false;
}

int _LongDistance(BinaryTreeNode* root,int& len)
{
	if (root == NULL)
		return 0;
	int left = _LongDistance(root->_left,len);
	int right = _LongDistance(root->_right, len);

	if (left + right > len)
		len = left + right;

	return left > right ? left+1 : right+1;
}
//二叉树中节点的最大距离
int LongDistance(const int* a,const int n)
{
	assert(a);
	
	BinaryTree bt(a,n);
	BinaryTreeNode* root = bt.GetRoot();

	int len = 0;

	int high = _LongDistance(root,len);

	return len;
}
//找到根节点在中序遍历中的下标
int FindIndex(int* a, int x, int left,int right)
{
	for (int i = left; i <= right; ++i)
	{
		if (a[i] == x)
			return i;
	}
	return -1;
}

void _GreateTree(BinaryTreeNode*& root, int* prev, int* in, 
	                         int left, int right, int& pre)
{
	int begin = left;
	int end = right;

	if (left <= right)
		root = new BinaryTreeNode(prev[pre]);

	int index = FindIndex(in, prev[pre], left, right);

	if (left <= index - 1)
		_GreateTree(root->_left, prev, in, left, index-1, ++pre);
	else
		root->_left = NULL;

	if (index + 1 <= right)
		_GreateTree(root->_right, prev, in, index+1, right, ++pre);
	else
	{
		root->_right = NULL;
		return;
	}
}
//根据前序遍历和中序遍历重建二叉树
void GreateTreeByPrevAndIn(int* prev,int* in,int psize,int isize)
{
	assert(prev);
	assert(in);

	int pre = 0;
	BinaryTreeNode* _root = new BinaryTreeNode(prev[pre]);

	int index = FindIndex(in, prev[pre], 0, isize);

	_GreateTree(_root->_left, prev, in, 0, index-1, ++pre);
	_GreateTree(_root->_right, prev, in, index+1, isize-1, ++pre);

}

void FindAncestorNodeTest()
{
	int a[] = {5,3,2,1,'#','#','#',4,'#','#',7,6,'#','#',8,'#',9,'#','#'};
	FindAncestor(a,sizeof(a)/sizeof(int));
}

void IsBalanceTest()
{
	int a[] = {5,3,2,1,'#','#','#',4,'#','#',7,6,'#','#',8,'#',9,'#','#'};
	cout << "IsBalance ? " << IsBalance(a, sizeof(a)/sizeof(int)) << endl;
}

void LongDistanceTest()
{
	int a[] = {5,3,2,1,'#','#','#',4,'#','#',7,6,'#','#',8,'#',9,'#','#'};
	cout<<"LongDiastance?:"<<LongDistance(a, sizeof(a)/sizeof(int))<<endl;
}

void GreateTreeTest()
{
	int prev[] = {5,3,2,1,4,7,6,8,9};
	int in[] = {1,2,3,4,5,6,7,8,9};

	GreateTreeByPrevAndIn(prev, in, sizeof(prev)/sizeof(int), sizeof(in)/sizeof(int));
}