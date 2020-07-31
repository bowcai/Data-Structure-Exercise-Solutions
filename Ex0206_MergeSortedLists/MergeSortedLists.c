#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

typedef int datatype;

typedef struct Sequence_list
{
	datatype elem[MAXSIZE];
	int last;
}*SeqList;

void EmptyList(SeqList L)
{
	L->last = -1;
}

void BuildList(SeqList L, const datatype in_array[], int size)
{
	// Make sure the input size is smaller than MAXSIZE
	int n = size < MAXSIZE ? size : MAXSIZE;
	for (int i = 0; i < n; i++)
	{
		L->elem[i] = in_array[i];
	}
	L->last = n - 1;
}

void ShowList(const SeqList L)
{
	for (int i = 0; i <= L->last; i++)
	{
		printf("%d, ", L->elem[i]);
	}
}

void DeleteList(SeqList L)
{
	free(L);
	L = NULL;
}

void AppendList(SeqList L, datatype x)
{
	L->last++;
	L->elem[L->last] = x;
}

SeqList UnionList(const SeqList a, const SeqList b)
{
	SeqList c = (SeqList)malloc(sizeof(struct Sequence_list));
	EmptyList(c);

	int i = 0, j = 0;
	while (i <= a->last && j <= b->last)
	{
		if (a->elem[i] < b->elem[j])
		{
			AppendList(c, a->elem[i]);
			i++;
		}
		else if (a->elem[i] > b->elem[j])
		{
			AppendList(c, b->elem[j]);
			j++;
		}
		else
		{
			AppendList(c, a->elem[i]);
			i++;
			j++;
		}
	}

	if (i > a->last)
	{
		for (;j <= b->last;j++)
		{
			AppendList(c, b->elem[j]);
		}
	}
	else if (j > b->last)
	{
		for (;i <= a->last;i++)
		{
			AppendList(c, a->elem[i]);
		}
	}

	return c;
}

int main(void)
{
	SeqList a = (SeqList)malloc(sizeof(struct Sequence_list));
	SeqList b = (SeqList)malloc(sizeof(struct Sequence_list));

	datatype a_input[] = { 1,3,5,6,7,8,9,14,15,17,18,19 };
	datatype b_input[] = { 2,4,6,8,10,12,14,16,18,22,25,27,40 };
	BuildList(a, a_input, sizeof(a_input) / sizeof(a_input[0]));
	BuildList(b, b_input, sizeof(b_input) / sizeof(b_input[0]));

	SeqList c = UnionList(a, b);
	
	printf("List a:\n");
	ShowList(a);
	printf("\nList b:\n");
	ShowList(b);
	printf("\nList c:\n");
	ShowList(c);
	printf("\n");
 
	DeleteList(a);
	DeleteList(b);
	DeleteList(c);

	return 0;
}
