#include"Slist_class.h"
#include<windows.h>

void Test1()
{
	Slist s1;
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.PushBack(4);
	s1.PushBack(5);
	s1.Print();

	s1.PopBack();
	s1.Print();

	Slist s2(s1);
	s2.Print();

	Slist s3;
	s3.PushBack(6);
	s3.PushBack(7);
	s3 = s1;
	s3.Print();
}

int main()
{
	Test1();

	system("pause");
	return 0;
}