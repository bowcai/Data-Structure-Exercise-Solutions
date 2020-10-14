#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <unordered_map>
#include <memory>
using namespace std;

template <typename T>
class TreeNode;

template <typename T>
using Tree = shared_ptr<TreeNode<T> >;

template <typename T>
class TreeNode
{
public:
	T data;
	Tree<T> Left;
	Tree<T> Right;
	int Height;

	// Create a new tree
	TreeNode(T);

	// Combine two trees with a new root node
	TreeNode(T, const Tree<T>&
		, const Tree<T>&);

	void show(void);
};

string ToPostfix(string S);
int ComputePostfix(string postfix
	, const unordered_map<char, int>& dict);
Tree<char> PostfixToTree(string postfix);

int main(void)
{
	int n_variable;
	unordered_map<char, int> variables;
	string infix;

	// Get input
	getline(cin, infix);
	cin >> n_variable;
	for (int i = 0; i < n_variable; i++)
	{
		char key;
		int value;
		cin >> key;
		cin >> value;
		variables[key] = value;
	}

	cout << endl << "Output:" << endl;
	string postfix = ToPostfix(infix);
	cout << postfix << endl;
	Tree<char> T = PostfixToTree(postfix);
	T->show();
	cout << ComputePostfix(postfix, variables) << endl;

	return 0;
}

template <typename T>
TreeNode<T>::TreeNode(T data) : data(data), Left(nullptr)
, Right(nullptr), Height(0)
{
}

template <typename T>
TreeNode<T>::TreeNode(T data, const Tree<T>& Left
	, const Tree<T>& Right)
	: data(data), Left(Left), Right(Right)
{
	int leftHeight = Left ? Left->Height : -1;
	int rightHeight = Right ? Right->Height : -1;
	Height = leftHeight > rightHeight
		? leftHeight + 1 : rightHeight + 1;
}

template <typename T>
void TreeNode<T>::show(void)
{
	struct NodeDepth
	{
		Tree<T> node;
		int layer;

		// The coordinate of node in output
		int coordinate;
	};
	queue<NodeDepth> nodes;
	vector<string> outs;

	// Get the sequence of nodes
	nodes.push({ Tree<T>(this), Height, (1 << Height) - 1 });

	string s1 = "";
	string s2 = "";
	int coord1 = 0;
	int coord2 = 0;
	int last_layer = Height;

	while (nodes.size() > 0)
	{
		NodeDepth current = nodes.front();
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

		if (current.node->Left)
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

		if (current.node->Right)
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
		else
		{
			throw "The infix expression is illegal.";
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

int ComputePostfix(string postfix
	, const unordered_map<char, int>& dict)
{
	stack<int> numbers;
	for (char& c : postfix)
	{
		if ((c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z'))
		{
			numbers.push(dict.at(c));
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/')
		{
			if (numbers.size() < 2)
			{
				throw "The postfix expression is illegal.";
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
		else
		{
			throw "The postfix expression is illegal.";
		}
	}

	if (numbers.size() != 1)
	{
		throw "The postfix expression is illegal.";
	}

	return numbers.top();
}

Tree<char> PostfixToTree(string postfix)
{
	stack<Tree<char> > nodes;
	for (char& c : postfix)
	{
		if ((c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z'))
		{
			nodes.push(Tree<char>(
				new TreeNode<char>(c)));
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/')
		{
			if (nodes.size() < 2)
			{
				throw "Postfix is illegal and cannot convert to tree.";
			}
			Tree<char> right = nodes.top();
			nodes.pop();
			Tree<char> left = nodes.top();
			nodes.pop();

			nodes.push(Tree<char>(
				new TreeNode<char>(c, left, right)));
		}
		else
		{
			throw "Postfix is illegal and cannot convert to tree.";
		}
	}

	if (nodes.size() != 1)
	{
		throw "Postfix is illegal and cannot convert to tree.";
	}

	return nodes.top();
}
