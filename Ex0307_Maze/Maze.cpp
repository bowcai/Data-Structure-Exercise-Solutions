#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stack>

using namespace std;

class Maze
{
public:
	const int x_len, y_len;

	// Probability of an open path
	const double open_prob;
	
	// The map of maze
	vector<vector<int> > maze_map;
	
	// Record the points that have walked through
	vector<vector<int> > pass;

	// The routine using coordinate
	stack<vector<int> > routine;
	
	// The direction of last step
	stack<int> step_direct;

	// The allowed directions
	const vector<vector<int> > directions 
		= { {1,0}, {0,1}, {-1,0}, {0,-1} };

	Maze(int, int, double);
	~Maze();
	int randomBlock(void) const;
	void initialBlocks(void);
	void showMaze(void) const;
	bool canStep(int, int) const;
	bool getRoutine(void);
	void showRoutine(void) const;
	void showMapRoutine(void) const;
	
private:

};

Maze::Maze(int m, int n, double prob) 
	:x_len(m), y_len(n), open_prob(prob)
	, maze_map(x_len, vector<int>(y_len))
	, pass(x_len, vector<int>(y_len, 0))
{
	initialBlocks();
	maze_map[0][0] = 0;
	maze_map[x_len - 1][y_len - 1] = 0;
}

Maze::~Maze()
{
}

int Maze::randomBlock(void) const
{
	return (double)rand() / RAND_MAX > open_prob ? 1 : 0;
}

void Maze::initialBlocks(void)
{
	for (auto& i: maze_map)
	{
		for (auto& j: i)
		{
			j = randomBlock();
		}
	}
}

void Maze::showMaze(void) const
{
	cout << "Showing the maze:" << endl;
	for (int i = 0; i < x_len; i++)
	{
		for (int j = 0; j < y_len; j++)
		{
			if (maze_map[i][j] == 1)
			{
				cout << "x ";
			}
			else
			{
				cout << "o ";
			}
		}
		cout << endl;
	}
	cout << endl;
}

// Check the accessibility of next step
bool Maze::canStep(int x, int y) const
{
	if (x < 0 || x >= x_len 
		|| y < 0 || y >= y_len)
	{
		return false;
	}

	return maze_map[x][y] == 0 && pass[x][y] == 0;
}

bool Maze::getRoutine(void)
{
	int x = 0, y = 0;
	unsigned int i = 0;
	routine.push({ x,y });
	pass[x][y] = 1;

	// When routine is empty, there is no solution
	while (!routine.empty())
	{
		// Try all the directions
		while (i < directions.size())
		{
			// If one direction is available, then take a step
			if (canStep(x + directions[i][0], 
				y + directions[i][1]))
			{
				break;
			}
			i++;
		}
		
		// One direction is available
		if (i < directions.size())
		{
			// Take a step
			x += directions[i][0];
			y += directions[i][1];

			// This point has past
			pass[x][y] = 1;

			// Update the routine
			routine.push({ x,y });
			
			// Record last step
			step_direct.push(i);

			// Check if reach the exit
			if (x == x_len - 1 && y == y_len-1)
			{
				return true;
			}

			// Reset the direction and continue
			i = 0;
		}

		// No direction is available, move back a step
		else
		{
			// Move one step behind
			routine.pop();

			// If routine is empty, then there is no solution
			if (routine.empty())
			{
				return false;
			}

			// Retrieve last point
			pass[x][y] = 0;
			x = routine.top()[0];
			y = routine.top()[1];

			// Retrieve last step and continue to try other directions
			i = step_direct.top() + 1;
			step_direct.pop();
		}
		
	}
	return false;
}

// Show the result of routine
void Maze::showRoutine(void) const
{
	stack<vector<int> > routine_copy = routine;
	stack<vector<int> > temp;
	
	// Reverse the routine for print out
	while (!routine_copy.empty())
	{
		temp.push(routine_copy.top());
		routine_copy.pop();
	}

	cout << "Showing the routine:" << endl;
	while (!temp.empty())
	{
		cout << "( " << temp.top()[0]+1 << ", " 
			<< temp.top()[1]+1 << ")" << endl;
		temp.pop();
	}
	cout << endl;
}

// Show routine in map
void Maze::showMapRoutine(void) const
{
	vector<vector<int> > maze_map_copy = maze_map;
	stack<vector<int> > routine_copy = routine;
	vector<int> temp;

	while (!routine_copy.empty())
	{
		temp = routine_copy.top();
		maze_map_copy[temp[0]][temp[1]] = 2;
		routine_copy.pop();
	}

	cout << "Showing the routine in map:" << endl;
	for (int i = 0; i < x_len; i++)
	{
		for (int j = 0; j < y_len; j++)
		{
			switch (maze_map_copy[i][j])
			{
			case 0:
				cout << "o ";
				break;
			case 1:
				cout << "x ";
				break;
			case 2:
				cout << "* ";
			}
		}
		cout << endl;
	}
	cout << endl;
}

int main(void)
{
	srand((unsigned)time(nullptr));
	constexpr int m = 8, n = 7;
	constexpr double prob = 0.70;
	Maze maze1(m, n, prob);
	maze1.showMaze();

	if (maze1.getRoutine())
	{
		cout << "There is a solution :)" << endl;
		maze1.showRoutine();
		maze1.showMapRoutine();
	}
	else
	{
		cout << "There is no solution :(" << endl;
	}
	return 0;
}
