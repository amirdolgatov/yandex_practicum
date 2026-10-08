#include <iostream>
#include <vector>
#include <unordered_map>



int main(int argc, char const *argv[])
{
    int n = 0;
    std::cin >> n;
    std::cin.ignore(); // Удаляет символ новой строки

    std::unordered_map<std::string, int> club_table;
    std::vector<std::string> queue;
    std::string tmp;

    while (n-- > 0)
    {
        getline(std::cin, tmp);
        auto iter = club_table.find(tmp);
        if (iter == club_table.end())
        {
            club_table.insert({tmp, 1});
            queue.push_back(tmp);
        }
    }

    for (auto& str: queue)
    {
        std::cout << str << "\n";
    }

    return 0;
}