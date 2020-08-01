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

	AdjList();
	~AdjList();
	void AddVertex(ElementType);
	void MakeEmpty(void);
	void AddArc(int, int);

	void BFSprint(int);
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
}

void AdjList::AddVertex(ElementType x)
{
	struct Vertex NewVertex;
	NewVertex.data = x;
	NewVertex.firstarc = NULL;

	vertexes.push_back(NewVertex);
	vexnum += 1;
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

	PtrToArc newarc_j = new Arc;
	newarc_j->adjvex = i;
	newarc_j->next = vertexes[j].firstarc;
	vertexes[j].firstarc = newarc_j;
	
	arcnum += 1;
}

// k is the begin vertex
void AdjList::BFSprint(int k)
{
	if (k >= vexnum)
	{
		cerr << "Vertex number out of range!" << endl;
		cerr << "Cannot find the vertex." << endl;
		return;
	}
		
	vector<int> visited;

	visited.resize(vertexes.size());
	for (int& i : visited)
	{
		i = 0;
	}

	queue<int> Q;
	Q.push(k);
	visited[k] = 1;

	while (Q.size() != 0)
	{
		int current = Q.front();
		Q.pop();

		cout << vertexes[current].data << " ";
		
		PtrToArc temp = vertexes[current].firstarc;
		while (temp != NULL)
		{
			if (visited[temp->adjvex] == 0)
			{
				Q.push(temp->adjvex);
				visited[temp->adjvex] = 1;
			}
			temp = temp->next;
		}
	}
	cout << endl;
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
	
	G.AddArc(0, 4);
	G.AddArc(0, 3);
	G.AddArc(0, 1);
	G.AddArc(1, 5);
	G.AddArc(1, 4);
	G.AddArc(1, 2);
	G.AddArc(2, 5);
	G.AddArc(2, 4);
	G.AddArc(2, 3);
	G.AddArc(3, 4);
	G.AddArc(4, 5);

	G.BFSprint(5);
	return 0;
}
