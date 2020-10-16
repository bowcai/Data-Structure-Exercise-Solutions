#include <iostream>
#include <cmath>
#include <vector>
#include <cfloat>

using namespace std;

typedef struct coordinate
{
	double x;
	double y;
}ElementType;

typedef double WeightType;

class Graph
{
private:
	const int vexnum;
	int arcnum;
	vector<ElementType> vertexes;
	vector<vector<WeightType> > arcs;

public:
	constexpr static double INF = DBL_MAX;

	Graph(int);
	~Graph();
	
	void AddVertex(int, ElementType);
	void AddArc(int, int);
	void DelArc(int, int);
	void PrintAdjMat(void) const;
	double Euclidean(int, int) const;
	WeightType ShortestRoad(int) const;
};

constexpr double Graph::INF;

Graph::Graph(int m) :vexnum(m), arcnum(0)
			, vertexes(vector<ElementType>(vexnum))
			, arcs(vector<vector<WeightType> >(vexnum
						, vector<WeightType>(vexnum, INF)))
{
	for (int i = 0; i < (int)arcs.size(); i++)
	{
		arcs[i][i] = 0;
	}
}

Graph::~Graph()
{
}

void Graph::AddVertex(int m, ElementType x)
{
	// If input index begin from 1
	m--;
	
	if (m >= vexnum || m < 0)
	{
		throw "Vertex index out of range!";
	}

	vertexes[m] = x;
}

void Graph::AddArc(int m, int n)
{
	// If input index begin from 1
	m--;
	n--;
	
	if (m >= vexnum || n >= vexnum  || m < 0 || n < 0)
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

	arcs[m][n] = Euclidean(m, n);

	// For undirected graph
	// arcs[n][m] = w;
}

void Graph::DelArc(int m, int n)
{
	// If input index begin from 1
	m--;
	n--;
	
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

	// For undirected graph
	// arcs[n][m] = INF;
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

double Graph::Euclidean(int m, int n) const
{
	if (m >= vexnum || n >= vexnum || m < 0 || n < 0)
	{
		throw "Vertex index out of range!";
	}

	if (m == n)
	{
		throw "Cannot delete the arc between the same vertex.";
	}
	
	return sqrt((vertexes[m].x - vertexes[n].x) 
		* (vertexes[m].x - vertexes[n].x)
		+ (vertexes[m].y - vertexes[n].y)
		* (vertexes[m].y - vertexes[n].y));
}

// Given one start point, return the shortest road built
// from this point
WeightType Graph::ShortestRoad(int m_start) const
{
	// If input index start from 1
	m_start--;

	if (m_start >= vexnum || m_start < 0)
	{
		throw "Vertex index out of range!";
	}

	WeightType RoadLength = 0;

	vector<bool> known(vexnum, false);

	known[m_start] = true;

	// Minimun distance to start point
	vector<WeightType> MinDist(vexnum);
	// Length of last step to this point
	// (Length of new road needed to be built)
	vector<WeightType> LastDist(vexnum);

	for (int i = 0; i < vexnum; i++)
	{
		LastDist[i] = MinDist[i] = arcs[m_start][i];
	}

	while (true)
	{
		int v_shortest = -1;
		WeightType w_shortest = INF;

		// Get the shortest unknown vertex
		for (int i = 0; i < vexnum; i++)
		{
			if (known[i])
			{
				continue;
			}
			
			if (MinDist[i] < w_shortest)
			{
				v_shortest = i;
				w_shortest = MinDist[i];
			}
		}

		// No unknown accessible vertex
		if (v_shortest == -1)
		{
			for (bool k : known)
			{
				// Found vertex unaccessible
				if (!k)
				{
					return -1;
				}
			}

			return RoadLength;
		}

		known[v_shortest] = true;
		RoadLength += LastDist[v_shortest];

		// Update MinDist and LastDist
		for (int j = 0; j < vexnum; j++)
		{
			if (known[j])
			{
				continue;
			}
			
			if (arcs[v_shortest][j] == INF)
			{
				continue;
			}

			if (w_shortest + arcs[v_shortest][j] < MinDist[j])
			{
				MinDist[j] = w_shortest + arcs[v_shortest][j];
				LastDist[j] = arcs[v_shortest][j];
			}
		}
	}
}

int main(void)
{
	int n_vex = 0;

	vector<Graph> graphs;

	cin >> n_vex;
	
	while (n_vex)
	{
		int n_arc;
		cin >> n_arc;

		Graph G(n_vex);
		
		for (int i = 1; i <= n_vex; i++)
		{
			ElementType a;
			cin >> a.x >> a.y;

			G.AddVertex(i, a);
		}

		for (int i = 1; i <= n_arc; i++)
		{
			int m, n;
			cin >> m >> n;
			G.AddArc(m, n);
		}
		
		graphs.push_back(G);

		n_vex = 0;
		cin >> n_vex;
	}

	cout << endl;
	cout << "Output:" << endl;

	cout.setf(ios_base::fixed);
	cout.precision(2);

	for (auto& G : graphs)
	{
		WeightType RoadLength = G.ShortestRoad(1);
		if (RoadLength < 0)
		{
			cout << "NO" << endl;
		}
		else
		{
			cout << RoadLength << endl;
		}
	}

	return 0;
}
