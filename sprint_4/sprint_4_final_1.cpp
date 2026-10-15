#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <sstream>

using documents = std::unordered_map<int, int>;

int main(int argc, char const *argv[])
{
    int n, m;
    std::cin >> n;
    std::cin.ignore();

    // 1. как собрать таблицу?
    std::unordered_map<std::string, documents> main_table;
    std::vector<std::unordered_set<std::string>> requests_vector;

    for (int i = 0; i < n; ++i)
    {
        std::string document;
        std::getline(std::cin, document);  // читаем документ целиком

        std::istringstream iss(document);
        std::string word;
        while (iss >> word)
        {
            main_table[word][i]++;
        }
    }

    std::cin >> m;
    std::cin.ignore();

    for (int i = 0; i < m; i++)
    {
        std::unordered_set<std::string> unique_words;
        std::string request;

        std::getline(std::cin, request);  // читаем документ целиком
        std::istringstream iss(request);
        std::string word;
        while (iss >> word)
        {
            unique_words.emplace(word);
        }

        requests_vector.emplace_back(unique_words);
    }

    // 2. how to calculate relevance?
    std::unordered_map<int, int> result;
    for (auto& request: requests_vector)
    {
        for (auto& word: request)
        {
            auto documents = main_table.find(word);
            if (documents == main_table.end())
            {
                continue;
            }
            else
            {
                for (auto& [document_id, word_count]: documents->second)
                {
                    result[document_id] += word_count;
                }
            }
        }

        // now result consisits of relevance of each document
        std::vector<std::pair<int, int>> output(result.begin(), result.end());

        auto cmp = [](const auto &a, const auto &b)
        {
            if (a.second != b.second)
            {
                return a.second > b.second;
            }
            else
            {
                return a.first < b.first;
            }
        };

        std::sort(output.begin(), output.end(), cmp);
        for (int i = 0; i < output.size() && i < 5; i++)
        {
            std::cout << output[i].first + 1 << " ";
        }

        std::cout << std::endl;
        result.clear();
    }

    return 0;
}
