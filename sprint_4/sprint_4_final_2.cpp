#include <iostream>
#include <vector>
#include <unordered_map>

int main()
{
	for (int i = 100003 - 10013; i < 100100; i = i + 500)
	{
		std::cout << i << " % M = " << i % 100003 << '\n';
	}

	return 0;
}