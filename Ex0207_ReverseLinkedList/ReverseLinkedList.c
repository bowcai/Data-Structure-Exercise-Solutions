#include <stdio.h>
#include <stdlib.h>

typedef int datatype;

struct node
{
	datatype data;
	struct node* next;
};

typedef struct node* PtrToNode;
typedef PtrToNode List, Position;

int IsEmpty(List L)
{
	return L->next == NULL;
}

int IsLast(Position P)
{
	return P->next == NULL;
}

// Generate a new empty list
List MakeEmpty(void)
{
	List L = (List)malloc(sizeof(struct node));
	if (L == NULL)
	{
		printf("Error in allocate space.\n");
		exit(1);
	}
	L->next = NULL;

	return L;
}

// Delete list elements and make it an empty list
void DeleteList(List L)
{
	Position P, tmp;
	P = L->next;
	L->next = NULL;
	while (P != NULL)
	{
		tmp = P->next;
		free(P);
		P = tmp;
	}
}

void ShowList(List L)
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

	TmpCell = malloc(sizeof(struct node));
	if (TmpCell == NULL)
	{
		printf("Error in allocate space.\n");
		exit(1);
	}
	
	TmpCell->data = x;
	TmpCell->next = P->next;
	P->next = TmpCell;
}

void BuildList(List L, const datatype input_array[], int size)
{
	Position last = L;
	for (int i = 0; i < size; i++)
	{
		Insert(input_array[i], L, last);
		last = last->next;
	}
}

void Reverse(List L)
{
	if (IsEmpty(L) || IsLast(L->next))
	{
		printf("Do not need to reverse the list.\n");
		return;
	}

	Position current, nextnode;
	current = nextnode = L->next->next;
	L->next->next = NULL;
	while (current != NULL)
	{
		nextnode = current->next;
		current->next = L->next;
		L->next = current;
		current = nextnode;
	}
}

int main(void)
{
	List L = MakeEmpty();
	datatype input_array[] = { 1,9,3,5,4,2,7,4,5 };
	BuildList(L, input_array, sizeof(input_array) / sizeof(input_array[0]));
	printf("List before reversion:\n");
	ShowList(L);

	Reverse(L);

	printf("List after reversion:\n");
	ShowList(L);
	DeleteList(L);
	free(L);
	L = NULL;
}
