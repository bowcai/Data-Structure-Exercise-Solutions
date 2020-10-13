#include <iostream>
#include <vector>
using namespace std;

void ShowMatrix(const vector<vector<int> >& mat)
{
	for (auto& mati : mat)
	{
		for (auto& matij : mati)
		{
			cout << matij << "\t";
		}
		cout << endl;
	}
}

// Use Siamese method to generate odd-order magic square
void MagicSquare(int m)
{
	if (m % 2 == 0)
	{
		cerr << "The function can only handle"
			<<" odd-order magic square." << endl;
		exit(1);
	}
	
	vector<vector<int> > magic(m, vector<int>(m, 0));

	int i = 0, j = (m - 1) / 2;
	int i_next, j_next;

	for (int k = 1; k <= m*m; k++)
	{
		magic[i][j] = k;

		i_next = i - 1 >= 0 ? i - 1 : m - 1;
		j_next = j + 1 < m ? j + 1 : 0;

		if (magic[i_next][j_next] == 0)
		{
			i = i_next;
			j = j_next;
		}
		else
		{
			i = i + 1 < m ? i + 1 : 0;
		}
	}

	ShowMatrix(magic);
}

int main(void)
{
	int m = 15;
	MagicSquare(m);

	return 0;
}
