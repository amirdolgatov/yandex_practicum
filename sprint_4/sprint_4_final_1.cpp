// https://contest.yandex.ru/contest/24414/run-report/168614089/

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
 * Пусть
 * N - количество уникальных слов во всех документах
 * a - доля повторяющихся слов, тогда общее количество слов N(1 + a)
 * L - максимальная длина слова в документе
 * M - количество уникальных слов в запросах
 * b - доля повторяющихся слов в запросах, тогда общее количество слов M(1 + b)
 * m - количество запросов, n - количство документов.
 *
 * При создании индекса для каждого слова необходимо выполнить поиск, то есть требуется вычисление хеша,
 * как в случае когда слово уже есть в индексе, так и в случае его отсутствия.
 * Поиск нужно выполнить N(1 + a) раз, сложность вычисления хеша O(L)
 * Проследим путь добавления в индекс уникального слова: необходимо вычислить хеш строки,
 * затем вычислить хеш номера документа и добавить пару документ - счетчик добавленного слова.
 * Сложность добавления уникальных слов N * (O(L) + O(1)).
 * Добавление неуникального слова потребует еще одной операции в сранении с добавлением уникального слова
 * - инкремент счетчика слова, значит сложность добавления неуникальных слов
 * будет aN * (O(L) + O(1) + 1). Но O(1) + 1 = O(1). Поэтому можно записать aN * (O(L) + O(1))
 *
 * Суммарная сложность создания индекса O(N(1 + a) * L)
 *
 * Для хранения слов всех запросов в контейнере необходимо M(1 + b) * O(L) действий.
 *
 * Расчет релевантности всех запросов, в худшем случае, имеет сложность m * M(1 + b) * O(n) = O(m * M(1 + b) * n).
 *
 * Перед выдачей результата документы сортируются по релевантности, что имеет сложность O(m * n * log 5)
 *
 * Итого имеем в худшем случае сложность O(N(1 + a) * L) + O(M(1 + b) * L) + O(m * M(1 + b) * n) + O(m * n * log 5)
 * 
 * ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ
 * Для хранения данных потребуется O(M + N) единиц памяти.
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

        int k = std::min(5, (int)output.size());
        std::partial_sort(output.begin(), output.begin() + k, output.end(), cmp);
        for (int i = 0; i < output.size() && i < 5; i++)
        {
            std::cout << output[i].first + 1 << " ";
        }

        std::cout << std::endl;
        result.clear();
    }

    return 0;
}
