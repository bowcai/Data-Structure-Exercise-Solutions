#include <iostream>

using namespace std;

typedef int ElementType;

typedef struct AvlNode
{
	ElementType Element;
	AvlNode *Left;
	AvlNode *Right;
	int Height;
}*Position, *AvlTree;

AvlTree MakeEmpty(AvlTree T);
Position Find(ElementType x, const AvlTree T);
Position FindMin(const AvlTree T);
Position FindMax(const AvlTree T);
ElementType Retrieve(const Position P);
AvlTree Insert(ElementType x, AvlTree T);
Position SingleRotateWithLeft(Position K2);
Position SingleRotateWithRight(Position K2);
Position DoubleRotateWithLeft(Position K3);
Position DoubleRotateWithRight(Position K3);


int main(void)
{
	AvlTree T = nullptr;
	T = Insert(1, T);
	T = Insert(2, T);
	T = Insert(3, T);
	T = Insert(4, T);
	T = Insert(5, T);
	T = Insert(6, T);
	T = Insert(7, T);

	Position P = Find(5, T);
	int x = Retrieve(P);
	cout << "Position: " << P << endl;
	cout << "Element: " << x << endl;
	
	MakeEmpty(T);
	return 0;
}

AvlTree MakeEmpty(AvlTree T)
{
	if (T != nullptr)
	{
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);

		delete T;
	}
	return nullptr;
}

Position Find(ElementType x, const AvlTree T)
{
	Position ptr = T;
	while (ptr != nullptr)
	{
		if (x < ptr->Element)
		{
			ptr = ptr->Left;
		}
		else if (x > ptr->Element)
		{
			ptr = ptr->Right;
		}
		else return ptr;
	}
	return nullptr;
}

Position FindMin(const AvlTree T)
{
	Position ptr = T;
	if (ptr != nullptr)
	{
		while (ptr->Left != nullptr)
		{
			ptr = ptr->Left;
		}
	}
	return ptr;
}

Position FindMax(const AvlTree T)
{
	Position ptr = T;
	if (ptr != nullptr)
	{
		while (ptr->Right != nullptr)
		{
			ptr = ptr->Right;
		}
	}
	return ptr;
}

ElementType Retrieve(const Position P)
{
	if (P == nullptr)
	{
		throw "Empty Position";
	}
	else
	{
		return P->Element;
	}
}

int Height(const Position P)
{
	if (P == nullptr)
	{
		return -1;
	}
	else return P->Height;
}

AvlTree Insert(ElementType x, AvlTree T)
{
	if (T == nullptr)
	{
		T = new AvlNode;
		T->Element = x;
		T->Height = 0;
		T->Left = T->Right = nullptr;
	}
	else if (x < T->Element)
	{
		T->Left = Insert(x, T->Left);
		if (Height(T->Left) - Height(T->Right) == 2)
		{
			if (x < T->Left->Element)
			{
				T = SingleRotateWithLeft(T);
			}
			else
			{
				T = DoubleRotateWithLeft(T);
			}
		}
	}
	else if (x > T->Element)
	{
		T->Right = Insert(x, T->Right);
		if (Height(T->Right) - Height(T->Left) == 2)
		{
			if (x > T->Right->Element)
			{
				T = SingleRotateWithRight(T);
			}
			else
			{
				T = DoubleRotateWithRight(T);
			}
		}
	}

	T->Height = Height(T->Left) > Height(T->Right) 
		? Height(T->Left) + 1 : Height(T->Right) + 1;

	return T;
}

Position SingleRotateWithLeft(Position K2)
{
	Position K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;

	K2->Height = Height(K2->Left) > Height(K2->Right)
		? Height(K2->Left) + 1 : Height(K2->Right) + 1;
	K1->Height = Height(K1->Left) > Height(K2)
		? Height(K1->Left) + 1 : Height(K2) + 1;

	return K1;
}

Position SingleRotateWithRight(Position K2)
{
	Position K1 = K2->Right;
	K2->Right = K1->Left;
	K1->Left = K2;

	K2->Height = Height(K2->Left) > Height(K2->Right)
		? Height(K2->Left) + 1 : Height(K2->Right) + 1;
	K1->Height = Height(K1->Left) > Height(K2)
		? Height(K1->Left) + 1 : Height(K2) + 1;

	return K1;
}

Position DoubleRotateWithLeft(Position K3)
{
	K3->Left = SingleRotateWithRight(K3->Left);

	return SingleRotateWithLeft(K3);
}

Position DoubleRotateWithRight(Position K3)
{
	K3->Right = SingleRotateWithLeft(K3->Right);

	return SingleRotateWithRight(K3);
}
