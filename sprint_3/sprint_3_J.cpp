#include <iostream>
#include <vector>

void bubble_sort(std::vector<int>& vec)
{
    bool permutations = true;
    while (permutatins)
    {
        permutations = false;
        for (int i = 0; i < vec.size() - 1; i++)
        {
            if (vec[i] > vec[i + 1])
            {
                std::swap(vec[i], vec[i + 1]);
                permutatins = true;
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    std::string s, t;
    std::cin >> t;
    std::cin.ignore();
    std::cin >> s;

    if (is_subsequence(s, t))
    {
        std::cout << "True" << std::endl;
    }
    else
    {
        std::cout << "False" << std::endl;
    }

    return 0;
}
