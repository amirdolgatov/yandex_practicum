#include <iostream>
#include <vector>

void print(const std::vector<std::string>& sets, const std::string& input, int num, std::string output)
{
	if (input.size() == num)
	{
		std::cout << output << " ";
		return;
	}

	int index = input[num] - '0';
	for (char ch: sets[index])
	{
		print(sets, input, num + 1, output + ch);
	}
}

int main(void)
{
	std::vector<std::string> sets = {
		"",
		"",
		"abc",
		"def",
		"ghi",
		"jkl",
		"mno",
		"pqrs",
		"tuv",
		"wxyz"
	};

	std::string input;
	std::cin >> input;
	print(sets, input, 0, "");
	std::cout << std::endl;
}