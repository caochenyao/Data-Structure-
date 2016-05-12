#pragma once
#include<assert.h>
#include<stack>
//��ȡ�ļ��еľ���
void GetMaze(int* a,int row,int col)
{
	FILE* fOut = fopen("MazeMap.txt","r");
	assert(fOut);
	for (int i = 0; i < row;++i)
	{
		for (int j = 0; j < col;)
		{
			char ch = fgetc(fOut);
			if (ch >= '0' && ch <= '9')
			{
				a[i*col + j] = ch - '0';
				++j;
			}
		}
	}
	fclose(fOut);
}
//��ӡ����
void PrintMaze(int* a,int row,int col)
{
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			cout << a[i*col + j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
//����
struct Pos
{
	int row;
	int col;
};
//�жϸ������Ƿ�����ӳ��Թ���·��Ҫ��
bool IsAccess(int* a,int rowsize,int colsize,Pos cur)
{
	if (cur.col >= 0 && cur.row >= 0 &&
		cur.col < colsize && cur.row < rowsize && 
		a[cur.row*colsize + cur.col] == 0)
	{
		return true;
	}
	return false;
}
//ͨ��ѹջ�õ����Թ���·��
stack<Pos> GetPath(int* a,int rowsize,int colsize,Pos enter)
{
	stack<Pos> path;
	Pos cur = enter;
	a[cur.row*colsize + cur.col] = 2;
	path.push(cur);

	while (!path.empty())
	{
		Pos top = path.top();
		Pos next = top;

		if (next.row == rowsize - 1 || next.col == colsize - 1)
		{
			return path;
		}
		//��
		next.row--;
		if (IsAccess(a, rowsize, colsize,next))
		{
			a[next.row*colsize + next.col] = 2;
			path.push(next);
			continue;
		}
        //��
		next = top;
		next.row++;
		if (IsAccess(a, rowsize, colsize, next))
		{
			a[next.row*colsize + next.col] = 2;
			path.push(next);
			continue;
		}
		//��
		next = top;
		next.col--;
		if (IsAccess(a, rowsize, colsize, next))
		{
			a[next.row*colsize + next.col] = 2;
			path.push(next);
			continue;
		}
		//��
		next = top;
		next.col++;
		if (IsAccess(a, rowsize, colsize, next))
		{
			a[next.row*colsize + next.col] = 2;
			path.push(next);
			continue;
		}

		Pos back = top;
		a[back.row*colsize + back.col] = 3;
		path.pop();
	}
	cout << "NOT PATH" << endl;
	return path;
}

void Testmaze()
{
	int a[10][10] = {};
	GetMaze((int*)a,10,10);
	PrintMaze((int*)a, 10, 10);

	Pos cur{2,0};
	GetPath((int*)a,10,10,cur);
	PrintMaze((int*)a, 10, 10);
}