#include <iostream>
using namespace std;

typedef int RecordType;

int Partition(RecordType R[], int low, int high);
void QSort(RecordType R[], int s, int t);

int main(void)
{
	RecordType R[] = { 0,32,59,21,12,45,89
		,63,34,26,7,6,18,24,45 };

	cout << "Before sorting:" << endl;
	for (int i = 1; i <= 14; i++)
	{
		cout << R[i] << " ";
	}
	cout << endl;

	QSort(R, 1, 14);
	
	cout << "After sorting:" << endl;
	for (int i = 1; i <= 14; i++)
	{
		cout << R[i] << " ";
	}
	cout << endl;
}

int Partition(RecordType R[], int low, int high)
{
	int n = 0;
	RecordType avg = 0;
	for (int i = low; i <= high; i++)
	{
		avg += R[i];
		n++;
	}
	avg /= n;

	while (R[high] >= avg)
	{
		high--;
	}

	if (low == high)
	{
		return low;
	}

	R[0] = R[high];
	while (low < high)
	{
		while (low < high && R[low] <= avg)
		{
			low++;
		}

		if (low == high)
		{
			break;
		}

		R[high--] = R[low];

		while (low < high && R[high] >= avg)
		{
			high--;
		}

		if (low == high)
		{
			break;
		}

		R[low] = R[high];
		low++;
	}

	R[low] = R[0];
	return low;
}

void QSort(RecordType R[], int s, int t)
{
	if (s < t - 1)
	{
		int pivotloc = Partition(R, s, t);
		QSort(R, s, pivotloc);
		QSort(R, pivotloc + 1, t);
	}
	else if (s == t - 1)
	{
		if (R[s] > R[t])
		{
			RecordType temp = R[s];
			R[t] = R[s];
			R[t] = temp;
		}
	}
}
