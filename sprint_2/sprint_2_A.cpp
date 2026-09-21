#include <iostream>

int main()
{
	int m, n;
	std::cin >> m >> n;
	
	int *p = new int[m * n];

	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			int index = i * n + j;
			std::cin >> p[index];
		}
	}

	for (int i = 0; i < n; ++i)
	{
		for(int j = 0; j < m; ++j)
		{
			if (j != 0)
			{
				std::cout << " ";
			}
			int index = j * n + i;
			std::cout << p[index];
		}
		std::cout << '\n';
	}

	std::cout << std::endl;
	delete(p);
	return 0;
}
