#pragma once
#include<assert.h>

//��������
void CountSort(int* a,size_t size)
{
	assert(a);
	int min = a[0];
	int max = a[0];
	//�ҳ����ֵ����Сֵ
	for (size_t i = 1;i<size;++i)
	{
		if (a[i]<min)
		{
			min = a[i];
		}
		else if (a[i]>max)
		{
			max = a[i];
		}
	}
	//����������ķ�Χ
	int range = max-min+1;
	int* count = new int[range];
	memset(count,0,sizeof(int)*range);

	for (size_t i = 0; i < size;++i)
	{
		count[a[i] - min]++;    //a[i]-minΪa[i]��count�������������λ��
		                        //count����洢����ÿ��λ�����ݵĸ���
	}

	int index = 0;
	for (int i = 0; i < range;++i)
	{
		int tmp = count[i];    //tmp>0��ʾ��һ����������,iΪ�����ݵ����λ��
		while (tmp)            //��һ��������ͬ����
		{
			a[index++] = i + min;
			--tmp;
		}
	}
	delete[] count;
}
//�����������λ��:
int BitNum(int* a, size_t size)
{
	assert(a);
	int bit = 1;
	int flag = 10;
	for (size_t i = 0; i < size;++i)
	{
		if (a[i] >= flag)
		{
			++bit;
			flag *= 10;
		}
	}
	return bit;
}
//��������
void RadixSort(int* a,size_t size)
{
	int bit = BitNum(a,size);
	int flag = 1;
	int* count = new int[10];
	int* start = new int[10];
	int* tmp = new int[size];

	while (bit > 0)
	{
		memset(count, 0, sizeof(int)*10);
		memset(start, 0, sizeof(int)*10);
		for (size_t i = 0; i < size;++i)
		{
			count[(a[i]/flag)%10]++;
		}
		//ȷ����ʼλ��
		start[0] = 0;
		for (size_t i = 1; i < 10;++i)
		{
			start[i] = count[i-1] + start[i-1];
		}
		for (size_t i = 0; i < size;++i)
		{
			int index = (a[i] / flag) % 10;
			tmp[start[index]++] = a[i];
		}
		memcpy(a, tmp, sizeof(int)*size);
		flag *= 10;
		--bit;	
	}
	
	delete[] tmp;
	delete[] count;
	delete[] start;
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

void CountTest()
{
	int array[] = { 19, 22, 34, 65, 22, 7, 98, 345, 81, 1 };
	CountSort(array, sizeof(array)/sizeof(int));
	Print(array, sizeof(array)/sizeof(int));
}

void RadixTest()
{
	int array[] = { 19, 22, 34, 65, 22, 7, 98, 345, 81, 1 ,55};
	RadixSort(array, sizeof(array)/sizeof(int));
	Print(array, sizeof(array)/sizeof(int));
}