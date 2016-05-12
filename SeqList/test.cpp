#include<iostream>
using namespace std;
#include<windows.h>
#include"SeqList_class.h"

//SeqList() & SeqList(SeqList &s) & operator=()
void Test1()
{
	int array1[5] = { 1, 2, 3, 4, 5 };
	SeqList s1(array1,5);
	s1.Print();
	SeqList s2(s1);
	s2.Print();
	cout << s2[3] << endl;

	int array2[3] = { 1, 2, 3 };
	SeqList s3(array2,3);
	s3.Print();
	s1 = s3;
	s1.Print();
}

//PushBack()&PopBack()
void Test2()
{
	int array[5] = { 1, 2, 3, 4, 5 };
	SeqList s1(array, 5);
	s1.Print();
	s1.PushBack(6);
	s1.Print();
	s1.PopBack();
	s1.PopBack();
	s1.Print();
}

//Find()&Earse()&Insert()
void Test3()
{
	int array[5] = { 1, 2, 3, 4, 5 };
	SeqList s1(array, 5);
	s1.Print();
	int pos = s1.Find(3);
	cout << "The location is:" << pos << endl;
	pos = s1.Find(9);
	cout << "The location is:" << pos << endl;
	s1.Insert(2,6);
	s1.Print();
	s1.Earse(3);
	s1.Print();
}

//Size()&Capacity()
void Test4()
{   
	int array[5] = { 1, 2, 4, 5, 6 };
	SeqList s1(array, 5);
	s1.Print();
	size_t size = s1.Size();
	cout << "The size is:" << size << endl;
	size_t capacity = s1.Capacity();
	cout << "The capacity is:" << capacity << endl;
	s1.Insert(2, 3);
	s1.Print();
	size = s1.Size();
	cout << "The size is:" << size << endl;
	capacity = s1.Capacity();
	cout << "The capacity is:" << capacity << endl;
}

//Reserve()&Clear()
void Test5()
{
	int array[5] = { 1, 2, 3, 4, 5 };
	SeqList s1(array, 5);
	s1.Print();
	size_t size = s1.Size();
	cout << "The size is:" << size << endl;
	size_t capacity = s1.Capacity();
	cout << "The capacity is:" << capacity << endl;
	s1.Reserve(20);
	size = s1.Size();
	cout << "The size is:" << size << endl;
	capacity = s1.Capacity();
	cout << "The capacity is:" << capacity << endl;
	s1.Clear();
	size = s1.Size();
	cout << "The size is:" << size << endl;
	capacity = s1.Capacity();
	cout << "The capacity is:" << capacity << endl;
}

int main()
{
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	Test5();

	system("pause");
	return 0;
}