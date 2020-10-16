#include <iostream>
#include <vector>
#include <stack>
#include <climits>

using namespace std;

template <typename T>
class Graph
{
public:
	typedef int WeightType;

private:
	int vexnum;
	int arcnum;
	vector<T> vertexes;
	vector<vector<WeightType> > arcs;

public:
	constexpr static WeightType INF = INT_MAX;
	Graph(int);
	~Graph();
	void AddArc(int, int, WeightType);
	void DelArc(int, int);
	void PrintAdjMat(void) const;
	int BreakCycle(void);
	int BreakDFS(int, int, vector<bool>&, stack<int>&);
	void BuildMinSpan(void);
};

template <typename T>
constexpr typename Graph<T>::WeightType Graph<T>::INF;

// Use adjacent matrix to store the graph
template <typename T>
Graph<T>::Graph(int m) :vexnum(m), arcnum(0)
			, vertexes(vector<T>(vexnum))
			, arcs(vector<vector<WeightType> >(vexnum
						, vector<WeightType>(vexnum, INF)))
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

template <typename T>
Graph<T>::~Graph()
{
}

template <typename T>
void Graph<T>::AddArc(int m, int n, WeightType w)
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

template <typename T>
void Graph<T>::DelArc(int m, int n)
{
	if (m >= vexnum || n >= vexnum)
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
template <typename T>
void Graph<T>::PrintAdjMat(void) const
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

// DFS for breaking the cycle
template <typename T>
int Graph<T>::BreakDFS(int k, int former, vector<bool>& visited
	, stack<int>& path)
{
	// Set the current point as visited and record it into path
	visited[k] = true;
	path.push(k);

	for (int i = 0; i < vexnum; i++)
	{
		// The arc between current vertex and former vertex 
		// cannot form a circle
		if (i == k || i == former)
		{
			continue;
		}

		// Check all the connected vertex
		if (arcs[k][i] != INF)
		{
			// If one of the connected vertex has been visited, 
			// then there is a cycle
			// return the start vertex of the cycle
			if (visited[i] == 1)
			{
				path.push(i);
				return i;
			}

			// If the connected vertex has not been visited,
			// then continue the DFS
			else
			{
				int rslt = BreakDFS(i, k, visited, path);

				// If the deeper DFS finds a cycle,
				// then continue to return the result
				if (rslt != -1)
				{
					return rslt;
				}
			}
		}
	}

	// When all the connected vertex cannot find a cycle, 
	// return -1 as fail to find a cycle
	return -1;
}

template <typename T>
int Graph<T>::BreakCycle(void)
{
	// There will not be cycles if vexnum<=2
	if (vexnum <= 2)
	{
		return 0;
	}

	// Record the visited vertexes and the path of cycle
	vector<bool> visited(vexnum, false);
	stack<int> path;

	// Try all the start vertex
	for (int i = 0; i < vexnum; i++)
	{
		// Skip the visited vertex which cannot find a cycle
		if (!visited[i])
		{
			// Start the DFS (-1 means no former vertex)
			int rslt = BreakDFS(i, -1, visited, path);

			// If a cycle is found, then process the cycle
			if (rslt != -1)
			{
				// Check the path and find the maximum weight
				int former = path.top();
				path.pop();
				int current, m = -1, n = -1;
				WeightType maxweight = 0;
				while (!path.empty())
				{
					current = path.top();
					path.pop();
					if (arcs[current][former] > maxweight)
					{
						maxweight = arcs[current][former];

						// Record the vertexes of maximum weight arc
						m = current;
						n = former;
					}

					// Reach the start point of the cycle
					if (current == rslt)
					{
						break;
					}

					former = current;
				}

				// Delete the arc with maximum weight
				DelArc(m, n);

				// Find a cycle
				return 1;
			}
		}
	}

	// No cycle found
	return 0;
}

template <typename T>
void Graph<T>::BuildMinSpan(void)
{
	while (BreakCycle())
	{
		continue;
	}
}

int main(void)
{
	Graph<int> G(5);
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

	G.BuildMinSpan();

	cout << endl << "Minimum Spanning Tree:" << endl;
	G.PrintAdjMat();

	return 0;
}
