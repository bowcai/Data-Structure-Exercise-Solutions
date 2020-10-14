#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
using namespace std;

typedef char ElementType;

typedef struct TreeNode* PtrToNode;
typedef PtrToNode Tree;

struct TreeNode
{
	ElementType data;
	Tree Left;
	Tree Right;
	int Height;
};

struct dictionary
{
	char key;
	int data;
};

Tree CreateTree(ElementType x);
void DelTree(Tree T);
Tree CombineTree(ElementType x, const Tree L, const Tree R);
string ToPostfix(string S);
int GetValue(const vector<dictionary>& dict, char k);
int ComputePostfix(string postfix, const vector<dictionary>& dict);
Tree PostfixToTree(string postfix);
void PrintTree(const Tree T);

int main(void)
{
	int n_variable;
	vector<dictionary> variables;
	string infix;

	// Get input
	getline(cin, infix);
	cin >> n_variable;
	for (int i = 0; i < n_variable; i++)
	{
		dictionary temp;
		cin >> temp.key;
		cin >> temp.data;
		variables.push_back(temp);
	}

	cout << endl << "Output:" << endl;
	string postfix = ToPostfix(infix);
	cout << postfix << endl;
	Tree T = PostfixToTree(postfix);
	PrintTree(T);
	cout << ComputePostfix(postfix, variables) << endl;

	DelTree(T);

	return 0;
}

Tree CreateTree(ElementType x)
{
	Tree T = new TreeNode;
	T->data = x;
	T->Left = nullptr;
	T->Right = nullptr;
	T->Height = 0;
	return T;
}

void DelTree(Tree T)
{
	if (T == nullptr)
	{
		return;
	}
	DelTree(T->Left);
	DelTree(T->Right);
	delete T;
}

Tree CombineTree(ElementType x, const Tree L, const Tree R)
{
	Tree T = CreateTree(x);
	T->Left = L;
	T->Right = R;
	T->Height = L->Height > R->Height ? L->Height + 1 : R->Height + 1;
	return T;
}

// Convert the infix expression into postfix expression
string ToPostfix(string S)
{
	stack<char> oper;
	string postfix;
	for (char& c : S)
	{
		if ((c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z'))
		{
			postfix += c;
		}
		else if (c == '(')
		{
			oper.push(c);
		}
		else if (c == ')')
		{
			while (oper.size() > 0 && oper.top() != '(')
			{
				// Pop the operators and insert into postfix
				postfix += oper.top();
				oper.pop();
			}
			// Pop the '('
			oper.pop();
		}
		else if (c == '*' || c == '/')
		{
			while (oper.size() > 0 && oper.top() != '('
				&& oper.top() != '+' && oper.top() != '-')
			{
				postfix += oper.top();
				oper.pop();
			}
			// Push c into stack
			oper.push(c);
		}
		else if (c == '+' || c == '-')
		{
			while (oper.size() > 0 && oper.top() != '(')
			{
				postfix += oper.top();
				oper.pop();
			}
			oper.push(c);
		}
	}

	while (oper.size() > 0)
	{
		if (oper.top() != '(')
		{
			postfix += oper.top();
		}
		oper.pop();
	}

	return postfix;
}

int GetValue(const vector<dictionary>& dict, char k)
{
	for (auto& d : dict)
	{
		if (d.key == k)
		{
			return d.data;
		}
	}

	cout << "Cannot find the value." << endl;
	return 0;
}

int ComputePostfix(string postfix, const vector<dictionary>& dict)
{
	stack<int> numbers;
	for (char& c : postfix)
	{
		if ((c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z'))
		{
			numbers.push(GetValue(dict, c));
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/')
		{
			if (numbers.size() < 2)
			{
				cout << "The postfix is illegal." << endl;
				return 0;
			}

			int a = numbers.top();
			numbers.pop();
			int b = numbers.top();
			numbers.pop();

			switch (c)
			{
			case '+':
				numbers.push(a + b);
				break;
			case '-':
				numbers.push(a - b);
				break;
			case '*':
				numbers.push(a * b);
				break;
			case '/':
				numbers.push(a / b);
				break;
			default:
				break;
			}
		}
	}
	
	if (numbers.size() != 1)
	{
		cout << "The postfix is illegal." << endl;
		return 0;
	}

	return numbers.top();
}

Tree PostfixToTree(string postfix)
{
	stack<Tree> nodes;
	for (char& c : postfix)
	{
		if ((c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z'))
		{
			Tree temp = CreateTree(c);
			nodes.push(temp);
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/')
		{
			if (nodes.size() < 2)
			{
				cout << "Postfix is illegal and cannot convert to tree."
					<< endl;
				return nullptr;
			}
			Tree right = nodes.top();
			nodes.pop();
			Tree left = nodes.top();
			nodes.pop();

			nodes.push(CombineTree(c, left, right));
		}
	}

	if (nodes.size() != 1)
	{
		cout << "Postfix is illegal and cannot convert to tree."
			<< endl;
		return nullptr;
	}

	return nodes.top();
}

void PrintTree(const Tree T)
{
	struct NodeDepth
	{
		Tree node;
		int layer;

		// The coordinate of node in output
		int coordinate;
	};
	queue<NodeDepth> nodes;
	vector<string> outs;

	// Get the sequence of nodes
	nodes.push({ T, T->Height, (1 << T->Height) - 1 });

	string s1 = "";
	string s2 = "";
	int coord1 = 0;
	int coord2 = 0;
	int last_layer = T->Height;

	while (nodes.size() > 0)
	{
		struct NodeDepth current = nodes.front();
		nodes.pop();

		// Put last layer into output strings
		if (last_layer != current.layer)
		{
			outs.push_back(s1);
			outs.push_back(s2);
			s1 = "";
			s2 = "";
			coord1 = 0;
			coord2 = 0;
			last_layer = current.layer;
		}

		// Deal with current node
		for (int i = 0; i < current.coordinate - coord1; i++)
		{
			s1 += ' ';
		}
		s1 += current.node->data;
		coord1 = current.coordinate + 1;
		
		if (current.node->Left != nullptr)
		{
			nodes.push({ current.node->Left, current.layer - 1
				, current.coordinate - (1 << (current.layer - 1)) });

			for (int i = 0; i < current.coordinate - 1 - coord2; i++)
			{
				s2 += ' ';
			}
			s2 += '/';
			coord2 = current.coordinate;
		}
		
		if (current.node->Right != nullptr)
		{
			nodes.push({ current.node->Right, current.layer - 1
				, current.coordinate + (1 << (current.layer - 1)) });

			for (int i = 0; i < current.coordinate + 1 - coord2; i++)
			{
				s2 += ' ';
			}
			s2 += '\\';
			coord2 = current.coordinate + 2;
		}
	}

	outs.push_back(s1);

	for (auto& s : outs)
	{
		cout << s << endl;
	}
}
