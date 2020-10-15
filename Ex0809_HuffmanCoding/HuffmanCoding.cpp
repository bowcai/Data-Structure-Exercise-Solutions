#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

typedef char ElementType;
typedef int WeightType;

struct HuffmanNode
{
	ElementType data;

	// The total number of bits to encode
	// all the child leaves' characters in the string
	// if this node is the root node.
	WeightType totalBits;

	// Sum of all the child leaves' weight
	WeightType leafWeight;
	HuffmanNode* lchild;
	HuffmanNode* rchild;
};

typedef HuffmanNode* HuffmanTree;

bool Isleaf(const HuffmanTree T)
{
	return T->lchild && T->rchild;
}

HuffmanTree CreateLeaf(ElementType data, WeightType weight)
{
	HuffmanTree leaf = new HuffmanNode;
	leaf->lchild = nullptr;
	leaf->rchild = nullptr;
	leaf->data = data;
	leaf->leafWeight = weight;
	leaf->totalBits = 0;

	return leaf;
}

HuffmanTree CombineHuffman(const HuffmanTree a, const HuffmanTree b)
{
	HuffmanTree T = new HuffmanNode;
	T->lchild = a;
	T->rchild = b;

	// Each child leaves' character gets one more bit to encode.
	T->totalBits = a->totalBits + b->totalBits
		+ a->leafWeight + b->leafWeight;

	T->leafWeight = a->leafWeight + b->leafWeight;

	return T;
}

void DelHuffman(HuffmanTree T)
{
	if (T == nullptr)
	{
		return;
	}
	DelHuffman(T->lchild);
	DelHuffman(T->rchild);

	delete T;
	T = nullptr;
}

HuffmanTree BuildHuffman(const unordered_map<ElementType, WeightType>& count)
{
	auto greaterWeight = [](const HuffmanTree a, const HuffmanTree b)
	{
		return a->leafWeight > b->leafWeight;
	};
	
	priority_queue<HuffmanTree, vector<HuffmanTree>
				, decltype(greaterWeight)> Trees(greaterWeight);

	for (auto& c : count)
	{
		HuffmanTree leaf = CreateLeaf(c.first, c.second);
		Trees.push(leaf);
	}

	while (Trees.size() >= 2)
	{
		HuffmanTree a = Trees.top();
		Trees.pop();

		HuffmanTree b = Trees.top();
		Trees.pop();

		Trees.push(CombineHuffman(a, b));
	}

	HuffmanTree root = Trees.top();
	return root;
}

unordered_map<char, int> ToFrequency(string S)
{
	unordered_map<char, int> count;

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

	return count;
}

int main(void)
{
	string S;
	getline(cin, S);

	unordered_map<char, int> count = ToFrequency(S);

	HuffmanTree T = BuildHuffman(count);

	cout << T->totalBits << endl;
	DelHuffman(T);

	return 0;
}
