#include <stdio.h>
#include <stdlib.h>

typedef int datatype;

typedef struct node
{
	datatype data;
	struct node *next;
}*PtrToNode;

typedef struct listqueue
{
	PtrToNode tail;
}*LQueue;

LQueue CreateQueue(void)
{
	PtrToNode head = malloc(sizeof(struct node));
	if (head == NULL)
	{
		printf("Malloc Error.\n");
		exit(1);
	}
	head->next = head;
	LQueue Q = malloc(sizeof(struct listqueue));
	if (Q == NULL)
	{
		printf("Malloc Error.\n");
		exit(1);
	}
	Q->tail = head;
	return Q;
}


int IsEmpty(LQueue Q)
{
	if (Q == NULL || Q->tail == NULL || Q->tail->next == Q->tail)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Enqueue(LQueue Q, datatype x)
{
	if (Q == NULL || Q->tail == NULL)
	{
		printf("Cannot enqueue to an un-initialized queue");
		exit(1);
	}
	
	PtrToNode temp = malloc(sizeof(struct node));

	if (temp == NULL)
	{
		printf("Malloc Error.\n");
		exit(1);
	}

	temp->data = x;
	temp->next = Q->tail->next;
	Q->tail->next = temp;
	Q->tail = temp;
}

datatype Dequeue(LQueue Q)
{
	if (IsEmpty(Q))
	{
		printf("No node to dequeue.\n");
		exit(1);
	}
	
	// The node going to dequeue is the next node of head
	PtrToNode temp = Q->tail->next->next;
	datatype x = temp->data;
	
	// Check if the dequeuing node is the last node
	if (temp != Q->tail)
	{
		Q->tail->next->next = temp->next;
	}
	else
	{
		Q->tail = temp->next;
		Q->tail->next = Q->tail;
	}

	free(temp);
	temp = NULL;

	return x;
}

void DisposeQueue(LQueue Q)
{
	while (!IsEmpty(Q))
	{
		Dequeue(Q);
	}
	free(Q->tail);
	free(Q);
}

int main(void)
{
	int input[] = { 3,2,5,4,1,3,6 };
	int n = sizeof(input) / sizeof(input[0]);

	LQueue Q = CreateQueue();

	for (int i = 0; i < n; i++)
	{
		Enqueue(Q, input[i]);
	}
	
	for (int i = 0; i < n; i++)
	{
		printf("Dequeuing: %d\n", Dequeue(Q));
	}

	DisposeQueue(Q);
	Q = NULL;

	return 0;
}