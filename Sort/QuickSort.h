#pragma once
#include<assert.h>
#include<stack>

//三数取中法
int SelectKey(int* a, int left, int right)
{
	assert(a);
	int mid = left + (right-left) / 2;
	if (a[left] > a[right])
	{
		if (a[mid] > a[left])
		{
			return left;
		}
		else if (a[mid] < a[right])
		{
			return right;
		}
		else
		{
			return mid;
		}
	}
	else
	{
		if (a[mid] < a[left])
		{
			return left;
		}
		else if (a[mid] > a[right])
		{
			return right;
		}
		else
		{
			return mid;
		}
	}
}
//求边界
int Partition(int* a, int begin, int end)
{
	int right = end + 1;
	int key = a[right];
	while (begin < end)
	{
		while (a[begin] <= key && begin < end)
		{
			++begin;
		}
		while (a[end] >= key && begin < end)
		{
			--end;
		}
		if (begin < end)
			swap(a[begin], a[end]);
	}
	if (a[begin] > key)
	{
		swap(a[begin], a[right]);
	}
	return begin;
}

void _QuickSort(int* a,int left,int right)
{
	assert(a);
	int begin = left;
	int end = right - 1;
	if (begin >= end)
	{
		return;
	}
	int mid = SelectKey(a,left,right);
	//取到中间值后将中间值与最后的值交换
	swap(a[mid],a[right]);  
	int bounary = Partition(a,begin,end);
	_QuickSort(a, left, bounary-1);
	_QuickSort(a, bounary+1, right);
}
//单链表快速排序
void _SeqListQuickSort(int* a, int left, int right)
{
	assert(a);
	int cur = left;
	int prev = left - 1;
	if (left < right)
	{
		while (cur < right)
		{
			if (a[cur] < a[right] && ++prev != cur)
			{
				//++prev;
				swap(a[cur], a[prev]);
			}
			++cur;
		}
		if (a[prev+1] > a[right])
		{
			swap(a[++prev], a[right]);
		}
		else
		{
			++prev;
		}
	}
	else
	{
		return;
	}
	_SeqListQuickSort(a, left, prev - 1);
	_SeqListQuickSort(a, prev + 1, right);
	
}
//快速排序递归算法
void QuickSort(int* a,size_t size)
{
	assert(a);
	size_t left = 0;
	size_t right = size - 1;
	if (left < right)
	{
		//_QuickSort(a, left, right);
		_SeqListQuickSort(a, left, right);
	}	  
}

//快速排序非递归
//int a[10] = { 1, 5, 4, 6, 2, 7, 9, 3, 8, 0 };
void QuickSortNonRecur(int* a, size_t size)
{
	assert(a);
	int _left = 0; 
	int _right = size-1;
	stack<int> s;
	s.push(_left);
	s.push(_right);

	while (!s.empty())
	{
		int right = s.top();
		s.pop();
		int left = s.top();
		s.pop();

		int bounary = Partition(a, left, right-1);
		if (left < bounary-1)
		{
			s.push(left);
			s.push(bounary-1);		
		}
		if (right > bounary+1)
		{
			s.push(bounary+1);
			s.push(right);
		}
	}
}

void Print(int* a, size_t size)
{
	assert(a);
	for (size_t i = 0; i < size; ++i)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

void QuickTest()
{
	int array[] = { 1, 5, 4, 6, 21, 7, 9, 3, 8, 0 ,11,18};
	QuickSort(array, sizeof(array)/sizeof(int));
	//QuickSortNonRecur(array,sizeof(array)/sizeof(int));
	Print(array, sizeof(array)/sizeof(int));
}