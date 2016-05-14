#pragma once
#include<assert.h>
//直接插入排序
void InsertSort(int* a,size_t size)
{
	assert(a);
	for (size_t i = 1; i < size;++i)
	{
		int tmp = a[i];
		for (size_t index = i;index >= 0;--index)
		{
			if (tmp < a[index-1])
			{
				a[index] = a[index - 1];
			}
			else
			{
				a[index] = tmp;
				break;
			}
		}
	}
}
//希尔排序
void ShellSort(int* a, size_t size)
{
	assert(a);
	size_t gap = size;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		for (size_t i = gap; i < size; ++i)
		{
			int tmp = a[i];
			for (size_t index = i;index >= 0;)
			{
				if (tmp < a[index - gap])
				{
					a[index] = a[index - gap];
				}
				else
				{
					a[index] = tmp;
					break;
				}
				index -= gap;
			}
		}
	}
}
//堆排序->向下调整
void AdjustDown(int* a, size_t size, size_t root)
{
	assert(a);
	size_t child = root * 2 + 1;
	while (child <size)
	{
		if (a[child] < a[child + 1] && (child + 1)<size)
		{
			++child;
		}
		if (a[child] > a[root])
		{
			swap(a[child], a[root]);
			root = child;
			child = root * 2 + 1;
		}
		else
		{
			break;
		}
	}
}
//堆排序->向上调整
void AdjustUp(int* a, size_t size, size_t parent)
{
	assert(a);
	size_t child = parent * 2 + 1;
	if (a[child] < a[child+1] && (child+1)<size)
	{
		++child;
	}
	if (a[child] > a[parent])
	{
		swap(a[child], a[parent]);
	}
}
//堆排序
void HeapSort(int* a, size_t size)
{
	assert(a);
	for (size_t parent = (size - 2)/2; parent > 0;--parent)
	{
		AdjustUp(a,size,parent);
	}
	for (size_t index = size; index > 0;--index)
	{
		AdjustDown(a,index,0);
		swap(a[0],a[index - 1]);
	}
}
//选择排序优化
void SelectSort(int* a, size_t size)
{
	assert(a);
	size_t left = 0;
	size_t right = size - 1;
	while (left < right)
	{
		for (size_t i = left + 1; i <= right;++i)
		{
			if (a[left] > a[right])
			{
				swap(a[left], a[right]);
			}
			if (a[i] < a[left])
			{
				swap(a[i], a[left]);
			}
			if (a[i] > a[right])
			{
				swap(a[i], a[right]);
			}
		}
		++left;
		--right;
	}
}

//冒泡排序优化
void BubbleSort(int* a,size_t size)
{
	assert(a);
	size_t flag = size - 1;
	while (flag > 0) //flag为0的两种情况:1、一趟不落的排完; 2、中途有一趟没有交换，说明后面的已经有序
	{
		size_t k = flag;
		flag = 0;
		for (size_t j = 0;j < k;++j)
		{
			if (a[j]>a[j+1])
			{
				swap(a[j],a[j+1]);
				flag = j;
			}
		}
	}
}

void _MergeSort(int* a,int* tmp ,size_t begin1, size_t end1, size_t begin2, size_t end2)
{
	size_t mid1 = begin1 + (end1-begin1) / 2;
	size_t mid2 = begin2 + (end2 - begin2) / 2;
	size_t left = begin1;
	size_t right = end2;
	if (begin1 < end1)
	{
		_MergeSort(a, tmp, begin1, mid1, mid1+1, end1);
	}
	if (begin2 < end2)
	{
		_MergeSort(a, tmp, begin2, mid2, mid2 + 1, end2);
	}
	size_t index = begin1;
	while(begin1 <= end1 && begin2 <= end2)
	{
		if (a[begin1] < a[begin2])
		{
			tmp[index++] = a[begin1++];
		}
		else
		{
			tmp[index++] = a[begin2++];
		}
	}
	while (begin1 <= end1)
	{
		tmp[index++] = a[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[index++] = a[begin2++];
	}
	for (size_t i = left; i <= right;++i)
	{
		a[i] = tmp[i];
	}
}
//归并排序
void MergeSort(int* a,size_t size)
{
	assert(a);
	int* tmp = new int[size];
	size_t left = 0;
	size_t right = size - 1;
	size_t mid = left + (right-left) / 2;
	if (left < right)
	{
		_MergeSort(a,tmp,left,mid,mid+1,right);
	}
	memcpy(a, tmp, sizeof(int)*size);
	delete[] tmp;
}

void Print(int* a,size_t size)
{
	assert(a);
	for (size_t i = 0; i < size;++i)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

void InsertTest()
{
	int array[10] = {1,5,4,6,2,7,9,3,8,0};
	InsertSort(array, 10);
	Print(array, 10);
}

void ShellTest()
{
	int array[10] = { 1, 5, 4, 6, 2, 7, 9, 3, 8, 0 };
	ShellSort(array, 10);
	Print(array, 10);
}

void HeapTest()
{
	int array[10] = { 1, 5, 4, 6, 2, 7, 9, 3, 8, 0 };
	HeapSort(array, 10);
	Print(array, 10);
}

void SelectTest()
{
	int array[10] = { 1, 5, 4, 6, 2, 7, 9, 3, 8, 0 };
	SelectSort(array, 10);
	Print(array, 10);
}

void BubbleTest()
{
	int array[10] = { 1, 5, 4, 6, 2, 7, 9, 3, 8, 0 };
	BubbleSort(array, 10);
	Print(array, 10);
}

void MergeTest()
{
	int array[10] = { 5, 1, 4, 6, 2, 7, 9, 3, 8, 0 };
	MergeSort(array, 10);
	Print(array, 10);
}