#include <iostream>
#include <vector>
#include <unordered_map>

int main(int argc, char const *argv[])
{
    std::string s, t;
    std::cin >> s;
    std::cin.ignore(); // Удаляет символ новой строки
    std::cin >> t;

    if (t.size() != s.size())
    {
        std::cout << "NO" << std::endl;
        return 0;
    }

    std::unordered_map<char, char> table;

    std::string output = "YES";

    for (int i = 0; i < s.size(); i++)
    {
        auto iter = table.find(s[i]);
        if (iter == table.end())
        {
            table.insert({s[i], t[i]});
        }
        else if (iter->second != t[i])
        {
            output = "NO";
            std::cout << output << std::endl;
            return 0;
        }
    }

    table.clear();

    for (int i = 0; i < t.size(); i++)
    {
        auto iter = table.find(t[i]);
        if (iter == table.end())
        {
            table.insert({t[i], s[i]});
        }
        else if (iter->second != s[i])
        {
            output = "NO";
            std::cout << output << std::endl;
            return 0;
        }
    }

    std::cout << output << std::endl;

    return 0;
}
