// https://contest.yandex.ru/contest/23815/run-report/167574837/

/*
 * ИДЕЯ РЕШЕНИЯ
 *
 * Функция разбиения должна возвращать индекс опорного элемента.
 * Опорный элемент занимает свое конечное место в массиве.
 * Сортировка рекурсивно вызывается для элементов справа и слева опрного элемента
 * Используется алгоритм разбиения, приведенный в книге автора А.Шень, "Программирование. Теоремы и задачи."
 * Задача 1.2.32.
 *
 * Данный алгоритм переместит элементы больше опорного вправо, меньше опорного влево.
 * Элементы равные опорному разместятся в середине массива (после меньших опорного и перед большими опорного).
 * Алгоритм вернет правую границу расположения элемнтов равных опорному - число m.
 * [0,......,l] [l + 1,...., m] [r,....., n - 1]
 * Поскольку по условию задачи равные элементы отсутствуют, всегда будет только один опорный элемент.
 *
 * СЛОЖНОСТЬ
 * Суммарно все разбиения требуют порядка O(n) операций
 * Количество рекурсивных вызовов O(log(n))
 * Итого получим сложность сортировки O(n * log(n)).
 *
 * ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ
 * Дополнительной памяти не требуется (кроме входного массива).
 */

#include <iostream>
#include <vector>
#include <tuple>

using member = std::tuple<int, int, std::string>;

// Источник идеи: А.Шень, "Программирование. Теоремы и задачи." 2017 г.
int partition(std::vector<member>& vec, int l, int r)
{
    member pivot = vec[(l + r) / 2];
    int m = l - 1;
    int left = l - 1;
    int right = r;

    while (m != right)
    {
        if (vec[m + 1] == pivot)
        {
            m++;
        }
        else if (pivot < vec[m + 1])
        {
            std::swap(vec[m + 1], vec[right]);
            right--;
        }
        else
        {
            std::swap(vec[m + 1], vec[left + 1]);
            m++;
            left++;
        }
    }
    return m;
}

void quicksort(std::vector<member>& vec, int l, int r)
{
    if (l >= r)
    {
        return;
    }

    int m = partition(vec, l, r);
    quicksort(vec, l, m - 1);
    quicksort(vec, m + 1, r);
}

void print_vector(std::vector<member>& v)
{
    for (const auto&[points, penalty, login]: v)
    {
        std::cout << login << '\n';
    }
}

int main(int argc, char const *argv[])
{
    int n = 0;

    std::cin >> n;

    std::vector<member> v;

    int points;
    int penalty;
    std::string login;

    while (n-- > 0)
    {
        std::cin >> login;
        std::cin >> points;
        std::cin >> penalty;
        v.emplace_back(-points, penalty, login);
    }

    quicksort(v, 0, v.size() - 1);
    print_vector(v);
    return 0;
}
    
