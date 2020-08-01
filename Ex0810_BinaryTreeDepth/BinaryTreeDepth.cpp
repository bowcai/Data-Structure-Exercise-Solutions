#include <iostream>
#include <vector>
using namespace std;

struct TreeNode
{
	int id;
	int depth;
	TreeNode* lchild;
	TreeNode* rchild;
};

typedef TreeNode *Tree;

Tree CreateTree(int id)
{
	Tree T = new TreeNode;
	T->depth = 1;
	T->id = id;
	T->lchild = NULL;
	T->rchild = NULL;
	
	return T;
}

void DelTree(Tree T)
{
	if (T == NULL)
	{
		return;
	}
	DelTree(T->lchild);
	DelTree(T->rchild);
	
	delete T;
	T = NULL;
}

int TreeDepth(const vector<pair<int, int> > &v)
{
	vector<Tree> nodes;
	int maxdepth = 0;
	for (int i = 0; i < (int)v.size(); i++)
	{
		nodes.push_back(CreateTree(i + 1));
	}
	
	for (int i = 0; i < (int)v.size(); i++)
	{
		if (v[i].first > 0)
		{
			nodes[i]->lchild = nodes[v[i].first-1];
			nodes[v[i].first-1]->depth = nodes[i]->depth + 1;

			if (nodes[v[i].first-1]->depth > maxdepth)
			{
				maxdepth = nodes[v[i].first-1]->depth;
			}
		}

		if (v[i].second > 0)
		{
			nodes[i]->rchild = nodes[v[i].second-1];
			nodes[v[i].second-1]->depth = nodes[i]->depth + 1;

			if (nodes[v[i].second-1]->depth > maxdepth)
			{
				maxdepth = nodes[v[i].second-1]->depth;
			}
		}
	}

	for (auto& i : nodes)
	{
		delete i;
		i = NULL;
	}

	return maxdepth;
}


int main(void)
{
	int n;
	cin >> n;

	vector<pair<int, int> > v;
	for (int i = 0; i < n; i++)
	{
		pair<int, int> temp;
		cin >> temp.first;
		cin >> temp.second;
		v.push_back(temp);
	}

	cout << endl << "Output:" << endl;
	cout << TreeDepth(v) << endl;

	return 0;
}
