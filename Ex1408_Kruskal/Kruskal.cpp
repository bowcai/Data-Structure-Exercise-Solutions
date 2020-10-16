#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

#define INF INT_MAX

using namespace std;

typedef int ElementType;
typedef int WeightType;

class Graph
{
public:
	int vexnum;
	int arcnum;
	vector<ElementType> vertexes;
	vector<vector<WeightType> > arcs;

	Graph(int);
	~Graph();
	void AddArc(int, int, WeightType);
	void DelArc(int, int);
	void PrintAdjMat(void) const;
	Graph Kruskal(void) const;

private:

};

Graph::Graph(int m) :vexnum(m), arcnum(0)
			, vertexes(vector<ElementType>(vexnum))
			, arcs(vector<vector<ElementType> >(vexnum
						, vector<ElementType>(vexnum, INF)))
{
	for (int i = 0; i < (int)vertexes.size(); i++)
	{
		vertexes[i] = i;
	}

	for (int i = 0; i < (int)arcs.size(); i++)
	{
		arcs[i][i] = 0;
	}
}

Graph::~Graph()
{
}

void Graph::AddArc(int m, int n, WeightType w)
{
	if (m >= vexnum || n >= vexnum || m < 0 || n < 0)
	{
		throw "Vertex index out of range!";
	}

	if (m == n)
	{
		throw "The arc cannot connect between the same vertex.";
	}

	if (arcs[m][n] == INF)
	{
		arcnum++;
	}
	arcs[m][n] = w;
	arcs[n][m] = w;
}

void Graph::DelArc(int m, int n)
{
	if (m >= vexnum || n >= vexnum || m < 0 || n < 0)
	{
		throw "Vertex index out of range!";
	}

	if (m == n)
	{
		throw "Cannot delete the arc between the same vertex.";
	}

	if (arcs[m][n] != INF)
	{
		arcnum--;
	}
	arcs[m][n] = INF;
	arcs[n][m] = INF;
}

// Print out the adjacent matrix
void Graph::PrintAdjMat(void) const
{
	for (auto& i : arcs)
	{
		for (auto& j : i)
		{
			if (j == INF)
			{
				cout << "INF";
			}
			else
			{
				cout << j;
			}
			cout << "\t";
		}
		cout << endl;
	}
}

struct arc
{
	int m;
	int n;
	WeightType w;
};

bool CompareArc(const arc& i, const arc& j)
{
	return i.w < j.w;
}

Graph Graph::Kruskal(void) const
{
	Graph MinSpan(vexnum);
	int EdgesAccepted = 0;

	vector<arc> AllEdges;

	vector<int> ConComponent(vexnum);
	for (int i = 0; i < vexnum; i++)
	{
		ConComponent[i] = i;
	}

	for (int i = 0; i < vexnum; i++)
	{
		for (int j = i + 1; j < vexnum; j++)
		{
			if (arcs[i][j] != INF)
			{
				arc Edge;
				Edge.m = i;
				Edge.n = j;
				Edge.w = arcs[i][j];
				AllEdges.push_back(Edge);
			}
		}
	}

	sort(AllEdges.rbegin(), AllEdges.rend(), CompareArc);
	
	while (EdgesAccepted < vexnum - 1)
	{
		if (AllEdges.empty())
		{
			throw "Number of edges not enough.";
		}

		arc E = AllEdges.back();
		AllEdges.pop_back();

		// Accept the edge
		if (ConComponent[E.m] != ConComponent[E.n])
		{
			MinSpan.AddArc(E.m, E.n, E.w);
			EdgesAccepted++;

			for (int i = 0; i < vexnum; i++)
			{
				if (i == E.n)
				{
					continue;
				}
				if (ConComponent[i] == ConComponent[E.n])
				{
					ConComponent[i] = ConComponent[E.m];
				}
			}

			ConComponent[E.n] = ConComponent[E.m];
		}
	}

	return MinSpan;
}

int main(void)
{
	Graph G(5);
	G.AddArc(0, 1, 1);
	G.AddArc(0, 2, 2);
	G.AddArc(0, 3, 3);
	G.AddArc(1, 2, 3);
	G.AddArc(1, 4, 1);
	G.AddArc(2, 3, 2);
	G.AddArc(2, 4, 2);
	G.AddArc(3, 4, 1);

	cout << "Origin:" << endl;
	G.PrintAdjMat();

	cout << endl << "Minimum Spanning Tree:" << endl;
	Graph Minspan = G.Kruskal();
	Minspan.PrintAdjMat();

	return 0;
}
