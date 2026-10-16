// https://contest.yandex.ru/contest/24414/run-report/168138306/

/*
 * ИДЕЯ РЕШЕНИЯ
 *
 * Будем хранить документы в виде хитрой хеш таблицы, ключами в ней являются слова,
 * а значениями будет другая хеш таблица с документами содержащими данное слово.
 * Таким образом ускорится расчет релевантности документа.
 * Пример основной таблицы 
 * слово 1 ---> документ 2 ---> количество повторений слова 1
 *              документ 5 ---> количество повторений слова 1
 *
 * слово N ---> документ 1 ---> количество повторений слова N
 *              документ 10 ---> количество повторений слова N
 *
 * Запрос хранится в виде множества, поскольку нас интересуют только уникальные слова запроса.
 *
 * СЛОЖНОСТЬ
 * Пусть N - количество уникальных слов во всех документах
 * M - количество уникальных слов в запросах
 * m - количество запросов, n - количство документов.
 * Для создания основной таблицы потребуется порядка N * O(1) операций, ибо операции в хеш таблицах в среднем
 * имеют константную сложность.
 * Аналогично для хранения слов всех запросов M * O(1). Итого на создание контейнеров порядка O(N + M) операций.
 * Расчет релевантности всех запросов, в худшем случае, имеет сложность m * O(n) = O(m * n).
 * Однако в этом вопросе решающее значение имеет то из каких слов состоят запросы, если они редкие,
 * то количество операций для вычисления релевантности будет меньше, так, если каждое слово запроса
 * содержится ровно в одном документе, то получим O(m) операций.
 *
 * Перед выдачей результата документы сортируются по релевантности, что имеет сложность O(m * n * log n)
 *
 * Итого имеем в худшем случае сложность O(M + N) + O(m * n) + O(m * n * log n)
 * 
 * ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ
 * Для хранения данных потребуется O(M + N) + O(n) единиц памяти.
*/

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

    std::unordered_map<std::string, documents> main_table;
    std::vector<std::unordered_set<std::string>> requests_vector;

    // Читаем, добавляем документы
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

    // Читаем, добавляем запросы
    for (int i = 0; i < m; i++)
    {
        std::unordered_set<std::string> unique_words;
        std::string request;

        std::getline(std::cin, request);  
        std::istringstream iss(request);
        std::string word;
        while (iss >> word)
        {
            unique_words.emplace(word);
        }

        requests_vector.emplace_back(unique_words);
    }

    // Считаем релевантность
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

        // для сортировки результатов придется переложить в вектор
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
