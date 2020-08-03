#include <iostream>
#include <vector>

using namespace std;

typedef int datatype;

struct node
{
	datatype data;
	struct node* next;
};
typedef struct node* PtrToNode;
typedef PtrToNode List, Position;

int IsEmpty(const List L);
int IsLast(const Position P);
List MakeList(void);
void DeleteList(List& L);
void ShowList(const List L);
void Insert(datatype x, List L, Position P);
List BuildList(const vector<datatype>& input_array);
int GetLength(const List L);

void MergeSort(List L);
void MergePass(vector<Position>& Ptrs
	, int k, int length);
void Merge(vector<Position>& Ptrs
	, int begin1, int begin2);

int main(void)
{
	vector<datatype> input = { 32,59,21,12,45,89
		,63,34,26,7,6,18,24,45 };

	List L = BuildList(input);

	cout << "Origin list:" << endl;
	ShowList(L);

	MergeSort(L);

	cout << endl << "After sorting:" << endl;
	ShowList(L);

	DeleteList(L);

	return 0;
}

int IsEmpty(const List L)
{
	return L->next == NULL;
}

int IsLast(const Position P)
{
	return P->next == NULL;
}

// Generate a new empty list
List MakeList(void)
{
	List L = new node;
	L->data = 0;
	L->next = NULL;

	return L;
}

// Delete list
void DeleteList(List& L)
{
	Position P, tmp;
	P = L;
	L = NULL;
	while (P != NULL)
	{
		tmp = P->next;
		delete P;
		P = tmp;
	}
}

void ShowList(const List L)
{
	Position P = L->next;
	while (P != NULL)
	{
		printf("%d, ", P->data);
		P = P->next;
	}
	printf("\n");
}

// Insert a node after position p
void Insert(datatype x, List L, Position P)
{
	Position TmpCell;

	TmpCell = new node;

	TmpCell->data = x;
	TmpCell->next = P->next;
	P->next = TmpCell;
}

List BuildList(const vector<datatype>& input_array)
{
	List L = MakeList();
	Position last = L;
	for (auto& i: input_array)
	{
		Insert(i, L, last);
		last = last->next;
	}
	return L;
}

int GetLength(const List L)
{
	int l = 0;
	Position P = L->next;

	while (P != NULL)
	{
		l++;
		P = P->next;
	}

	return l;
}

void MergeSort(List L)
{
	int k = 1;
	int length = GetLength(L);

	// Auxiliary array to store the address of each element
	// The index begin from 1
	vector<Position> Ptrs;
	Ptrs.push_back(NULL);

	Position P = L->next;
	L->next = NULL;
	Position P_temp = P;
	while (P != NULL)
	{
		Ptrs.push_back(P);
		P_temp = P->next;
		P->next = NULL;
		P = P_temp;
	}

	while (k < length)
	{
		MergePass(Ptrs, k, length);
		k *= 2;
	}

	L->next = Ptrs[1];
}

void MergePass(vector<Position>& Ptrs
	, int k, int length)
{
	int i = 1;
	while (i <= length - 2 * k + 1)
	{
		Merge(Ptrs, i, i + k);
		i += 2 * k;
	}
	if (i < length - k + 1)
	{
		Merge(Ptrs, i, i + k);
	}
}

void Merge(vector<Position>& Ptrs
	, int begin1, int begin2)
{
	Position former = NULL;
	Position P1, P2;
	Position P;

	P1 = Ptrs[begin1];
	P2 = Ptrs[begin2];

	if (P1->data <= P2->data)
	{
		P = former = P1;
		P1 = P1->next;
	}
	else
	{
		P = former = P2;
		P2 = P2->next;
	}
	
	while (P1 != NULL && P2 != NULL)
	{
		if (P1->data <= P2->data)
		{
			former->next = P1;
			former = P1;
			P1 = P1->next;
		}
		else
		{
			former->next = P2;
			former = P2;
			P2 = P2->next;
		}
	}

	while (P1 != NULL)
	{
		former->next = P1;
		former = P1;
		P1 = P1->next;
	}
	while (P2 != NULL)
	{
		former->next = P2;
		former = P2;
		P2 = P2->next;
	}

	// Update vector Ptrs
	int i = begin1;
	while (P != NULL)
	{
		Ptrs[i] = P;
		P = P->next;
		i++;
	}
}
