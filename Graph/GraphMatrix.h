#pragma once
#include<assert.h>
#include<string>

template<class V,class W>
class GraphMatrix
{
public:
	GraphMatrix(V* v,size_t size)
		:_vertex(new V[size])
		, _size(size)
	{
		for (size_t  i = 0; i < size;++i)
		{
			_vertex[i] = v[i];
		}
		_edge = new W*[size];
		for (size_t i = 0; i < size; ++i)
		{
			_edge[i] = new W[size];
			memset(_edge[i],W(),sizeof(W)*size); 
		}
		//memset(_edge, W(), sizeof(W)*size*size);

	}
	~GraphMatrix()
	{
		if (_vertex)
		{
			delete[] _vertex;
			_vertex = NULL;
		}
			
		for (size_t i = 0; i < _size; ++i)
		{
			if (_edge[i])
			{
				delete[] _edge[i];
				_edge[i] = NULL;
			}
		}
		delete[] _edge;
		_edge = NULL;
	}
public:
	//默认为无向图
	void AddEdge(const V& src, const V& dst, const W& w, bool directon = false)
	{
		assert(src != dst);
		int srcindex = FindIndex(src);
		int dstindex = FindIndex(dst);
		if (srcindex >= 0 && dstindex >= 0)
		{
			_edge[srcindex][dstindex] = w;
			if (directon == false)
			    _edge[dstindex][srcindex] = w;
		}
	}
	void Display()
	{
		cout<<'\t';
		for (size_t i = 0; i < _size; ++i)
		{
			cout << _vertex[i] << '\t';
		}
		cout << endl;
		for (size_t i = 0; i < _size; ++i)
		{
			cout << _vertex[i] << '\t';
			for (size_t j = 0; j < _size; ++j)
			{
				cout << _edge[i][j] << '\t';
			}
			cout << endl;
		}
	}
protected:
	int FindIndex(const V& vertex)
	{
		for (size_t i = 0; i < _size; ++i)
		{
			if (_vertex[i] == vertex)
				return i;
		}
		return -1;
	}
protected:
	V* _vertex;
	size_t _size;
	W** _edge;
};

void GraphMatrixTest()
{
	string vertex[] = { "卡塞尔", "高天原", "三峡", "北京", "尼伯龙根" };
	GraphMatrix<string, int> graph(vertex,sizeof(vertex)/sizeof(string));

	graph.AddEdge("卡塞尔", "高天原", 1000);
	graph.AddEdge("尼伯龙根", "高天原", 3000);
	graph.AddEdge("卡塞尔", "三峡", 2000);

	graph.Display();


	//int a[5][5] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

}