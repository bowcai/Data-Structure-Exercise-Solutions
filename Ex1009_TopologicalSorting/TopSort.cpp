#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef int ElementType;

typedef struct Arc
{
	int adjvex;
	struct Arc* next;
}*PtrToArc;

struct Vertex
{
	ElementType data;
	struct Arc* firstarc;
};

class AdjList
{
public:
	vector<Vertex> vertexes;
	int vexnum;
	int arcnum;

	// For directed graph
	vector<int> Indegree;

	AdjList();
	~AdjList();
	void AddVertex(ElementType);
	void MakeEmpty(void);
	void AddArc(int, int);

	vector<int> Topsort(void) const;
};

AdjList::AdjList()
{
	vexnum = 0;
	arcnum = 0;
}

AdjList::~AdjList()
{
	MakeEmpty();
}

void AdjList::MakeEmpty(void)
{
	for (auto& i : vertexes)
	{
		PtrToArc temp;
		PtrToArc tempnext;

		temp = i.firstarc;

		while (temp != NULL)
		{
			tempnext = temp->next;
			delete temp;
			temp = tempnext;
		}
	}

	vertexes.resize(0);
	vexnum = 0;
	arcnum = 0;

	// For directed graph
	Indegree.resize(0);
}

void AdjList::AddVertex(ElementType x)
{
	struct Vertex NewVertex;
	NewVertex.data = x;
	NewVertex.firstarc = NULL;

	vertexes.push_back(NewVertex);
	vexnum += 1;

	// For directed graph
	Indegree.push_back(0);
}

void AdjList::AddArc(int i, int j)
{
	if (i >= vexnum || j >= vexnum)
	{
		cerr << "Vertex number out of range!" << endl;
		cerr << "Cannot add the arc." << endl;
		return;
	}

	PtrToArc temp = vertexes[i].firstarc;
	while (temp != NULL)
	{
		if (temp->adjvex == j)
		{
			cerr << "The arc has already been added." << endl;
			return;
		}
		temp = temp->next;
	}

	PtrToArc newarc_i = new Arc;
	newarc_i->adjvex = j;
	newarc_i->next = vertexes[i].firstarc;
	vertexes[i].firstarc = newarc_i;

	// For undirected graph
	// PtrToArc newarc_j = new Arc;
	// newarc_j->adjvex = i;
	// newarc_j->next = vertexes[j].firstarc;
	// vertexes[j].firstarc = newarc_j;

	// For directed graph
	Indegree[j]++;

	arcnum += 1;
}

vector<int> AdjList::Topsort(void) const
{
	vector<int> Indegree_copy = Indegree;
	queue<int> Q;
	int Counter = 0;
	vector<int> TopVex;

	for (int i = 0; i < vexnum; i++)
	{
		if (Indegree_copy[i] == 0)
		{
			Q.push(i);
		}
	}

	while (!Q.empty())
	{
		int v = Q.front();
		Q.pop();

		TopVex.push_back(v);

		PtrToArc w = vertexes[v].firstarc;
		while (w != NULL)
		{
			Indegree_copy[w->adjvex]--;
			if (Indegree_copy[w->adjvex] == 0)
			{
				Q.push(w->adjvex);
			}
			
			w = w->next;
		}

		Counter++;
	}

	if (Counter != vexnum)
	{
		cerr << "Graph has a cycle." << endl;
	}

	return TopVex;
}

int main(void)
{
	AdjList G;

	G.AddVertex(0);
	G.AddVertex(1);
	G.AddVertex(2);
	G.AddVertex(3);
	G.AddVertex(4);
	G.AddVertex(5);
	G.AddVertex(6);

	G.AddArc(0, 1);
	G.AddArc(0, 2);
	G.AddArc(0, 3);
	G.AddArc(1, 3);
	G.AddArc(1, 4);
	G.AddArc(2, 5);
	G.AddArc(3, 2);
	G.AddArc(3, 5);
	G.AddArc(3, 6);
	G.AddArc(4, 3);
	G.AddArc(4, 6);
	G.AddArc(6, 5);

	vector<int> Topvex = G.Topsort();

	for (auto& v : Topvex)
	{
		cout << v << " ";
	}
	cout << endl;

	return 0;
}
