#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

typedef char ElementType;
typedef int WeightType;

struct Elem
{
	ElementType data;
	WeightType weight;
};

struct HuffmanNode
{
	int id;
	
	WeightType weight;

	// Sum of all the child leaves' weight
	WeightType leafweight;
	HuffmanNode* lchild;
	HuffmanNode* rchild;
};

typedef HuffmanNode *HuffmanTree;

int Isleaf(const HuffmanTree T)
{
	if (T->lchild == NULL && T->rchild == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

HuffmanTree CreateLeaf(int id, WeightType weight)
{
	HuffmanTree leaf = new HuffmanNode;
	leaf->lchild = NULL;
	leaf->rchild = NULL;
	leaf->id = id;
	leaf->leafweight = 0;
	leaf->weight = weight;
	
	return leaf;
}

HuffmanTree CombineHuffman(const HuffmanTree a, const HuffmanTree b)
{
	HuffmanTree T = new HuffmanNode;
	T->lchild = a;
	T->rchild = b;
	T->id = -1;
	
	T->weight = a->weight + b->weight
			+ a->leafweight + b->leafweight;
	T->leafweight = a->leafweight + b->leafweight;
	
	// If a or b is a leaf, then we should add its weight
	// to T's leafweight.
	// But leaf's weight is stored in its "weight" but not
	// its "leafweight"
	if (Isleaf(a))
	{
		T->leafweight += a->weight;
	}
	if (Isleaf(b))
	{
		T->leafweight += b->weight;
	}

	return T;
}

void DelHuffman(HuffmanTree T)
{
	if (T == NULL)
	{
		return;
	}
	DelHuffman(T->lchild);
	DelHuffman(T->rchild);
	
	delete T;
	T = NULL;
}

bool CompareWeight(const HuffmanTree a, const HuffmanTree b)
{
	return a->weight < b->weight;
}

HuffmanTree BuildHuffman(const vector<Elem>& v)
{
	vector<HuffmanTree> Trees;
	for (int i = 0; i < (int)v.size(); i++)
	{
		HuffmanTree leaf = CreateLeaf(i, v[i].weight);
		Trees.push_back(leaf);
	}
	
	while (Trees.size() >= 2)
	{
		vector<HuffmanTree>::iterator iter_a
			= min_element(Trees.begin(), Trees.end(), CompareWeight);
		HuffmanTree a = *iter_a;
		Trees.erase(iter_a);

		vector<HuffmanTree>::iterator iter_b
			= min_element(Trees.begin(), Trees.end(), CompareWeight);
		HuffmanTree b = *iter_b;
		Trees.erase(iter_b);

		HuffmanTree temp = CombineHuffman(a, b);
		Trees.push_back(temp);
	}

	return Trees[0];
}

void ToFrequency(string S, vector<Elem>& v)
{
	map<char, int> count;
	
	for (char& c : S)
	{
		if (count.find(c) == count.end())
		{
			count[c] = 1;
		}
		else
		{
			count[c]++;
		}
	}

	for (auto& i : count)
	{
		v.push_back({ i.first, i.second });
	}
}

int main(void)
{
	string S;
	cin >> S;

	vector<Elem> v;
	ToFrequency(S, v);

	HuffmanTree T = BuildHuffman(v);

	cout << T->weight << endl;
	DelHuffman(T);

	return 0;
}
