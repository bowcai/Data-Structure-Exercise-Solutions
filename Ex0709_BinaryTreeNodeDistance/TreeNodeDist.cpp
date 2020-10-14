#include <iostream>
#include <stack>
using namespace std;

typedef int ElementType;

typedef struct TreeNode* PtrToNode;
typedef PtrToNode Tree;

struct TreeNode
{
	ElementType data;
	Tree Left;
	Tree Right;
	Tree Parent;
};

Tree CreateTree(ElementType x)
{
	Tree T = new TreeNode;
	T->data = x;
	T->Left = nullptr;
	T->Right = nullptr;
	T->Parent = nullptr;
	return T;
}

void DelTree(PtrToNode T)
{
	if (T == nullptr)
	{
		return;
	}
	DelTree(T->Left);
	DelTree(T->Right);
	delete T;
}

// Insert a node into Tree
// Direction=0 means insert into left
// Direction=1 means insert into right
PtrToNode Insert(ElementType x, PtrToNode p, int direction)
{
	if (p == nullptr)
	{
		cout << "Error in inserting." << endl;
		return nullptr;
	}
	PtrToNode temp = CreateTree(x);
	temp->Parent = p;
	if (direction == 0)
	{
		p->Left = temp;
	}
	else
	{
		p->Right = temp;
	}
	return temp;
}

int Distance(PtrToNode a, PtrToNode b)
{
	if (a == nullptr || b == nullptr)
	{
		cout << "Error in computing distance." << endl;
		return -1;
	}
	
	stack<PtrToNode> a_ancestor;
	stack<PtrToNode> b_ancestor;
	PtrToNode current;
	for (current = a; current != nullptr; current = current->Parent)
	{
		a_ancestor.push(current);
	}
	for (current = b; current != nullptr; current = current->Parent)
	{
		b_ancestor.push(current);
	}

	while (a_ancestor.size() > 0 && b_ancestor.size() > 0 &&
		a_ancestor.top() == b_ancestor.top())
	{
		a_ancestor.pop();
		b_ancestor.pop();
	}

	return a_ancestor.size() + b_ancestor.size();
}

int main(void)
{
	Tree T = CreateTree(1);
	PtrToNode node1 = T;
	PtrToNode node2 = Insert(2, node1, 0);
	PtrToNode node3 = Insert(3, node1, 1);
	PtrToNode node4 = Insert(4, node2, 0);
	PtrToNode node5 = Insert(5, node2, 1);
	PtrToNode node6 = Insert(6, node3, 0);
	PtrToNode node7 = Insert(7, node3, 1);
	cout << "Distance between node4 and node7: " << Distance(node4, node7) << endl;
	cout << "Distance between node6 and node7: " << Distance(node6, node7) << endl;
	cout << "Distance between node3 and node7: " << Distance(node3, node7) << endl;

	DelTree(T);

	return 0;
}
