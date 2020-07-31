#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 1024

typedef int datatype;

typedef struct
{
	int i, j;
	datatype v;
}SPMNode;

typedef struct
{
	int i;
	datatype v;
}SPVNode;

typedef struct
{
	// mu, nu is the size of the matrix
	// tu is the number of non-zero elements
	int mu, nu, tu;
	SPMNode data[MAXSIZE];
}SPMatrix;

typedef struct
{
	// mu is the size of the vector
	// tu is the number of non-zero elements
	int mu, tu;
	SPVNode data[MAXSIZE];
}SPVector;

SPMatrix* MakeSPMatrix(int m, int n)
{
	SPMatrix* A = malloc(sizeof(SPMatrix));
	A->mu = m;
	A->nu = n;
	A->tu = 0;
	return A;
}

SPVector* MakeSPVector(int m)
{
	SPVector* a = malloc(sizeof(SPVector));
	a->mu = m;
	a->tu = 0;
	return a;
}

void input_matrix(SPMatrix* A, const SPMNode* node)
{
	if (node->i < A->mu && node->j < A->nu
		&& A->tu < MAXSIZE && A->tu < A->mu * A->nu)
	{
		A->data[A->tu] = *node;
		A->tu++;
	}
}

void input_vector(SPVector* a, const SPVNode* node)
{
	if (node->i < a->mu && a->tu < MAXSIZE && a->tu < a->mu)
	{
		a->data[a->tu] = *node;
		a->tu++;
	}
}

void show_matrix(const SPMatrix* A)
{
	printf("     i|     j|    data|\n");
	printf("------|------|--------|\n");
	for (int k = 0; k < A->tu; k++)
	{
		printf("%6d|%6d|%8d|\n", A->data[k].i, A->data[k].j, A->data[k].v);
	}
}

void show_vector(const SPVector* a)
{
	printf("     i|    data|\n");
	printf("------|--------|\n");
	for (int k = 0; k < a->tu; k++)
	{
		printf("%6d|%8d|\n", a->data[k].i, a->data[k].v);
	}
}

SPVector* SP_multiply(const SPMatrix* A, const SPVector* b)
{
	if (A->nu != b->mu)
	{
		exit(1);
	}
	SPVector* c = MakeSPVector(A->mu);
	if (A->tu == 0 || b->tu == 0)
	{
		return c;
	}

	int Ak = 0, bk = 0;
	SPVNode ck = { 0,0 };
	while (Ak < A->tu)
	{
		if (ck.i != A->data[Ak].i)
		{
			if (ck.v != 0)
			{
				input_vector(c, &ck);
			}
			ck.i = A->data[Ak].i;
			ck.v = 0;
			bk = 0;
			continue;
		}
		if (A->data[Ak].j < b->data[bk].i)
		{
			Ak++;
			continue;
		}
		if (A->data[Ak].j > b->data[bk].i)
		{
			bk++;
			continue;
		}

		// Ak.j == bk.i
		ck.v += A->data[Ak].v * b->data[bk].v;
		Ak++;
		bk++;
	}

	if (ck.v != 0)
	{
		input_vector(c, &ck);
	}

	return c;
}

int main(void)
{
	SPMatrix* A = MakeSPMatrix(3, 4);
	SPVector* b = MakeSPVector(4);

	SPMNode A1 = { 0,0,3 };
	SPMNode A2 = { 0,2,2 };
	SPMNode A3 = { 1,1,5 };
	SPMNode A4 = { 1,3,4 };
	SPMNode A5 = { 2,2,6 };
	input_matrix(A, &A1);
	input_matrix(A, &A2);
	input_matrix(A, &A3);
	input_matrix(A, &A4);
	input_matrix(A, &A5);

	SPVNode b1 = { 0,2 };
	SPVNode b2 = { 2,6 };
	input_vector(b, &b1);
	input_vector(b, &b2);

	printf("Matrix A:\n");
	show_matrix(A);
	printf("\nVector b:\n");
	show_vector(b);

	SPVector* c = SP_multiply(A, b);
	printf("\nThe result c:\n");
	show_vector(c);

	return 0;
}
