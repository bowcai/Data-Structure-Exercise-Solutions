#include <iostream>
#include <vector>

using namespace std;

typedef int KeyType;

typedef struct Node
{
	KeyType key;
	struct Node* next;
}*PtrToNode;

struct List
{
	int length;
	struct Node head;
};

class HashTable
{
public:
	// Real length of hash table
	int length;
	int n_element;
	vector<List> lists;
	
	HashTable(int);
	~HashTable();
	int HashFunc(KeyType) const;
	int IsPrime(int) const;
	int NextPrime(int) const;
	void MakeEmpty(void);
	void AddToList(PtrToNode, int);
	void DeleteFromList(PtrToNode, PtrToNode);
	void InsertKey(KeyType);
	void InsertKey(vector<KeyType>);
	PtrToNode FindKey(KeyType) const;
	void DeleteKey(KeyType);
	void PrintTable(void) const;
	void PrintInfo(void) const;

private:

};

// n is the minimum length of hash table
HashTable::HashTable(int n)
{
	length = NextPrime(n);
	lists.resize(length);
	for (auto& l : lists)
	{
		l.length = 0;
		l.head.key = 0;
		l.head.next = NULL;
	}
	n_element = 0;
}

HashTable::~HashTable()
{
	MakeEmpty();
}

int HashTable::HashFunc(KeyType k) const
{
	return k % length;
}

int HashTable::IsPrime(int n) const
{
	if (n < 2)
	{
		return 0;
	}
	
	for (int i = 2; i < n / 2; i++)
	{
		if (n % i == 0)
		{
			return 0;
		}
	}

	return 1;
}

int HashTable::NextPrime(int n) const
{
	if (n <= 2)
	{
		return 2;
	}
	
	while (!IsPrime(n))
	{
		n++;
	}

	return n;
}

void HashTable::AddToList(PtrToNode x, int m)
{
	if (m >= length || m < 0)
	{
		cerr << "Table index out of range." << endl;
		return;
	}

	x->next = lists[m].head.next;
	lists[m].head.next = x;

	lists[m].length++;
}

void HashTable::DeleteFromList(PtrToNode former, PtrToNode current)
{
	former->next = current->next;
	delete current;
}

void HashTable::MakeEmpty(void)
{
	for (auto& i : lists)
	{
		PtrToNode temp = i.head.next;
		i.head.next = NULL;
		i.length = 0;

		PtrToNode temp_next = NULL;
		while (temp != NULL)
		{
			temp_next = temp->next;
			delete temp;
			temp = temp_next;
		}
	}
	n_element = 0;
}

void HashTable::InsertKey(KeyType k)
{
	int m = HashFunc(k);

	PtrToNode NewNode = new Node;
	NewNode->key = k;
	NewNode->next = NULL;
	AddToList(NewNode, m);

	n_element++;
}

void HashTable::InsertKey(vector<KeyType> ks)
{
	for (auto& k : ks)
	{
		InsertKey(k);
	}
}

PtrToNode HashTable::FindKey(KeyType k) const
{
	int m = HashFunc(k);

	PtrToNode current = lists[m].head.next;

	while (current != NULL)
	{
		if (current->key == k)
		{
			return current;
		}
		current = current->next;
	}
	
	cout << "Cannot find the key." << endl;
	return NULL;
}

void HashTable::DeleteKey(KeyType k)
{
	int m = HashFunc(k);

	PtrToNode former = &lists[m].head;
	PtrToNode current = former->next;

	while (current != NULL)
	{
		if (current->key == k)
		{
			DeleteFromList(former, current);
			current = NULL;
			n_element--;

			return;
		}
		former = current;
		current = current->next;
	}

	cout << "Cannot find the key." << endl;
}

void HashTable::PrintTable(void) const
{
	for (int i = 0; i < length; i++)
	{
		cout << i << ": ";
		
		PtrToNode current = lists[i].head.next;
		while (current != NULL)
		{
			cout << current->key << " ";
			current = current->next;
		}
		cout << endl;
	}
}

void HashTable::PrintInfo(void) const
{
	cout << "Length of hashtable: " << length << endl;
	cout << "Number of elements: " << n_element << endl;

	int sum = 0;
	for (auto& l : lists)
	{
		sum += l.length * (l.length + 1) / 2;
	}
	double ASL_S = (double)sum / (double)n_element;

	cout << "Successful ASL:" << ASL_S << endl;
}

int main(void)
{
	HashTable H(11);
	H.InsertKey({ 1,3,5,2,8,10,25,31 });

	H.PrintTable();
	cout << endl;
	H.PrintInfo();
	cout << endl;

	cout << "Address of key 8: " << H.FindKey(8) << endl;

	return 0;
}
