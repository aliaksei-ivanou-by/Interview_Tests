#include <iostream>
#include <ctime>

void bubble_sort(int* a, int N)
{
	for(int i = 0; i < N - 1; ++i)
	{
		bool changed = false;
		for(int j = 0; j < N - 1; ++j)
		{
			if(a[j] > a[j + 1])
			{
				int b = a[j];
				a[j] = a[j + 1];
				a[j + 1] = b;
				changed = true;
			}
		}
		if(!changed)
		{
			break;
		}
	}
}

void print_array(const int* a, const int N)
{
	for(int i = 0; i < N; ++i)
	{
		std::cout << a[i] << ' ';
	}
	std::cout << '\n';
}

int main()
{
	srand(time(NULL));
	int n;
	std::cin >> n;
	int a[n];
	for(int i = 0; i < n; ++i)
	{
		a[i] = 1 + rand() % 10;
	}
	print_array(a, n);
	bubble_sort(a, n);
	print_array(a, n);
	return 0;
}
