#include <iostream>
#include <vector>
#include <unordered_map>



int main(int argc, char const *argv[])
{
    int n = 0;
    std::cin >> n;
    std::cin.ignore(); // Удаляет символ новой строки

    std::unordered_map<int, std::pair<int, int>> table;

    int summ = 0;
    table.insert({summ, {0, 0}});
    int res;

    for (int i = 1; i <= n; i++)
    {
        std::cin >> res;

        if (res)
        {
            summ++;
        }
        else
        {
            summ--;
        }

        auto iter = table.find(summ);
        if (iter == table.end())
        {
            table.insert({summ, {i, i}});
        }
        else
        {
            iter->second.second = i;
        }
    }

    int max = 0;
    for(auto& [key, pair]: table)
    {
        auto distance = pair.second - pair.first;
        if (distance > max)
        {
            max = distance;
        }
    }

    std::cout << max << std::endl;

    return 0;
}
