#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using documents = std::unordered_map<int, int>;

int main(int argc, char const *argv[])
{
    std::cin.ignore(); // Удаляет символ новой строки
    std::cin >> t;

    // 1. как собрать таблицу?
    std::unordered_map<std::string, documents> main_table;
    std::vector<unordered_set<std::string>> requests_vector;

    for (int i = 0; i < n; ++i)
    {
        std::string document;
        std::getline(cin, document);  // читаем документ целиком

        std::istringstream iss(document);
        std::string word;
        while (iss >> word)
        {
            auto iter = main_table.find(word);
            if (iter == main_table.end())
            {
                main_table.insert({word, {0, 0}});
            }
            else
            {
                iter->second[i]++;
            }
        }
    }

    // 2. how to calculate relevance?
    std::vector<std::pair<int, int>> output;
    for (auto& request: requests_vector)
    {
        for (auto& word: request)
        {

        }
    }

    if (t.size() != s.size())
    {
        std::cout << "NO" << std::endl;
        return 0;
    }




    std::cout << output << std::endl;

    return 0;
}
