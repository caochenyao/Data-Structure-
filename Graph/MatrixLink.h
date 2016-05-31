#pragma once
#include<vector>
#include<assert.h>
#include<string>

#pragma warning(disable:4018)

template<class V, class W>
struct LinkNode
{
	size_t _srcindex;
	size_t _dstindex;
	W _edge;
	LinkNode<V, W>* _next;
	LinkNode(const size_t src,const size_t dst = 0, const W& w = 0)
		:_srcindex(src)
		, _dstindex(dst)
		, _edge(w)
		, _next(NULL)
	{}
};

template<class V,class W>
class MatrixLink
{
	typedef LinkNode<V, W> Node;
public:
	MatrixLink(const V* v,size_t size,bool dir = false)
		:_vertexs(new V[size])
		, _size(size)
		, _direction(dir)
	{
		_array.resize(size);
		for (int i = 0; i < size;++i)
		{
			_vertexs[i] = v[i];
			Node* cur = new Node(i);
			cur->_next = _array[i];
			_array[i] = cur;
		}
	}
	~MatrixLink()
	{
		if (_vertexs)
		{
			delete[] _vertexs;
			_vertexs = NULL;
		}
		for (int i = 0; i < _size; ++i)
		{
			Node* cur = _array[i];	
			while (cur)
			{
				Node* prev = cur;
				cur = cur->_next;
				delete prev;
				prev = NULL;
			}
		}
	}
public:
	//Ĭ��Ϊ����ͼ
	void AddEdge(const V& src,const V& dst,const W& w)
	{
		assert(src != dst);

		int srcindex = FindIndex(src);
		int dstindex = FindIndex(dst);

		if (srcindex != -1 && dstindex != -1)
		{
			Node* prev1 = _array[srcindex];
			Node* next1 = prev1->_next;
			Node* cur1 = new Node(srcindex, dstindex, w);
			prev1->_next = cur1;
			cur1->_next = next1;

			if (_direction == false)
			{
				Node* prev2 = _array[dstindex];
				Node* next2 = prev2->_next;
				Node* cur2 = new Node(dstindex, srcindex, w);
				prev2->_next = cur2;
				cur2->_next = next2;
			}
		}
	}
	void Display()
	{
		for (int i = 0; i < _size; ++i)
		{
			Node* cur = _array[i];
			while (cur)
			{
				cout << cur->_edge << "[" << cur->_srcindex << "]" << "[" << cur->_dstindex << "]->";
				cur = cur->_next;
			}
			cout << "NULL" << endl;
		}
	}
protected:
	int FindIndex(const V& vertex)
	{
		for (size_t i = 0; i < _size; ++i)
		{
			if (_vertexs[i] == vertex)
				return i;
		}
		return -1;
	}
protected:
	V* _vertexs;
	size_t _size;
	vector<Node*> _array;
	bool _direction;
};

void MatrixLinkTest()
{
	string vertex[] = { "������", "����ԭ", "��Ͽ", "����", "�Ხ����" };

	MatrixLink<string, int> link(vertex,sizeof(vertex)/sizeof(string));

	link.AddEdge("����", "����ԭ", 100);
	link.AddEdge("������", "�Ხ����", 200);
	link.AddEdge("�Ხ����", "����ԭ", 300);
	link.AddEdge("��Ͽ", "����ԭ", 400);
	link.AddEdge("������", "��Ͽ", 500);

	link.Display();
}