#include <iostream>
#include <ctime>

using namespace std;

// The first algorithm with complexity O(N^2)
void fibonacci1(int n)
{
	if (n <= 0)
	{
		cerr << "The input must be a positive integer." << endl;
	}
	
	// cout << "Fibonacci number " << 1 << ": " << 1 << endl;
	// cout << "Fibonacci number " << 2 << ": " << 1 << endl;
	
	for (int i = 3; i <= n; i++)
	{
		long long int current = 1;
		long long int previous = 1;
		long long int temp;
		for (int j = 3; j <= i; j++)
		{
			temp = current;
			current += previous;
			previous = temp;
		}
		// cout << "Fibonacci number " << i << ": " << current << endl;
	}
}

// The second algorithm with complexity O(N)
void fibonacci2(int n)
{
	if (n <= 0)
	{
		cerr << "The input must be a positive integer." << endl;
	}
	
	// cout << "Fibonacci number " << 1 << ": " << 1 << endl;
	// cout << "Fibonacci number " << 2 << ": " << 1 << endl;

	long long int current = 1;
	long long int previous = 1;
	long long int temp;

	for (int i = 3; i <= n; i++)
	{
		temp = current;
		current += previous;
		previous = temp;
		// cout << "Fibonacci number " << i << ": " << current << endl;
	}
}

// The third algorithm that use recursion with complexity O(2^n)
int fibonacci3(int n)
{
	if (n > 2)
	{
		return fibonacci3(n - 1) + fibonacci3(n - 2);
	}
	else if (n == 1)
	{
		return 1;
	}
	else if (n == 2)
	{
		return 1;
	}
	else
	{
		cerr << "The input must be a positive integer." << endl;
		return 0;
	}
}

int main(void)
{
	constexpr int test_times = 100000;
	constexpr int n_fibonacci = 25;
	
	time_t time1_start = clock();
	// Test for multiple times
	for (int i = 1; i <= test_times; i++)
	{
		fibonacci1(n_fibonacci);
	}
	time_t time1_end = clock();
	cout << "Total run time for algorithm 1 is " 
		<< (time1_end - time1_start) << " ms" << endl;

	time_t time2_start = clock();
	// Test for multiple times
	for (int i = 1; i <= test_times; i++)
	{
		fibonacci2(n_fibonacci);
	}
	time_t time2_end = clock();
	cout << "Total run time for algorithm 2 is " 
		<< (time2_end - time2_start) << " ms" << endl;

	time_t time3_start = clock();
	// Test for multiple times
	for (int i = 1; i <= test_times; i++)
	{
		fibonacci3(n_fibonacci);
	}
	time_t time3_end = clock();
	cout << "Total run time for algorithm 3 is " 
		<< (time3_end - time3_start) << " ms" << endl;

	return 0;
}
