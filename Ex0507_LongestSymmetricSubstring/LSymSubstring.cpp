#include <iostream>
#include <string>
using namespace std;

int longest_symmetric(string S)
{
	int MaxSymLen = 0;
	int fore, back, SymLen;
	for (int i = 0; i < (int)S.length(); i++)
	{
		// If the symmetry substring length is odd
		SymLen = 1;
		fore = i - 1;
		back = i + 1;
		while (fore >= 0 && back < (int)S.length())
		{
			if (S[fore] == S[back])
			{
				SymLen += 2;
				fore--;
				back++;
			}
			else
			{
				break;
			}
		}
		if (SymLen > MaxSymLen)
		{
			MaxSymLen = SymLen;
		}

		// If the symmetry substring length is even
		SymLen = 0;
		fore = i;
		back = i + 1;
		while (fore >= 0 && back < (int)S.length())
		{
			if (S[fore] == S[back])
			{
				SymLen += 2;
				fore--;
				back++;
			}
			else
			{
				break;
			}
		}
		if (SymLen > MaxSymLen)
		{
			MaxSymLen = SymLen;
		}
	}

	return MaxSymLen;
}

int main(void)
{
	string S;
	cout << "Enter a string:" << endl;
	getline(cin, S);
	int MaxSymLen = longest_symmetric(S);
	cout << "The longest symmetry substring's length is" << endl;
	cout << MaxSymLen << endl;

	return 0;
}
