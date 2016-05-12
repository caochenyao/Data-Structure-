#include<iostream>
#include<windows.h>
using namespace std;
#include"List_class.h"

void Test()
{
	List t;
	t.PushBack(1);
	t.PushBack(2);
	t.PushBack(3);
	t.PushBack(4);
	t.PushBack(5);
	t.Print();

	List t2(t);
	//t2.Reserve();
	ListNode* ret = t2.Find(3);
	t2.Erase(ret);
	ret = t2.Find(2);
	t2.Insert(ret,6);
	t2.Print();

	List t3;
	t3=t;
	t3.Print();
}

int main()
{
	Test();

	system("pause");
	return 0;
}


