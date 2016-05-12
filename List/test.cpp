#include<iostream>
#include<windows.h>
using namespace std;
#include"List_class.h"

void Test()
{
	List t;

	//尾插
	t.PushBack(1);
	t.PushBack(2);
	t.PushBack(3);
	t.PushBack(4);
	t.PushBack(5);
	t.Print();

	//拷贝构造
	List t2(t);
	
	//链表逆置
	//t2.Reserve();

	//查找指定节点
	ListNode* ret = t2.Find(3);

	//删除节点
	t2.Erase(ret);
	ret = t2.Find(2);

	//插入节点
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


