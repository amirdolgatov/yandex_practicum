// https://contest.yandex.ru/contest/23815/run-report/167237549/

/*
 * ИДЕЯ РЕШЕНИЯ
 *
 * В сломанном массиве расположены два отсортированных подмассива
 * Если нам будет известна грань, то мы можем провести поиск в каждом
 * из них. То есть в начале найти start - минимальный (нулевой) элемент
 * в массиве, и затем провести обычный поиск в двух подмассивах
 * [0, start - 1] - "старший" подмассив
 * [start , last] - "младший" подмассив
 *
 * СЛОЖНОСТЬ
 * На поиск нулевого элемента потратим O(log(n)) действий
 * На поиск в подмассивах O(log(N1) + O(log(N2) = O(log(n))
 * В сумме получим сложность O(log(n)).
 *
 * ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ
 * Дополнительной памяти не требуется (кроме входного массива). Стоит учитывать рекурсию и возможное
 * переполнение стека.
*/

#include <iostream>
#include <vector>

int partition_1(a[], l, r)
{
    int pivot = (l + r) / 2;

    while (l <= r)
    {
        bool left_ok = (a[l] <= pivot);
        bool right_ok = (a[r] >= pivot);
        if (left_ok)
        {
            ++l;
        }
        if (right_ok)
        {
            r--;
        }
        if (!left_ok && !right_ok)
        {
            swap(a[], l, r);
            ++l;
            r--;
        }
    }
}

int partition_2(a[], l, r)
{
    int pivot = (l + r) / 2;

    while (l != r)
    {
        bool left_ok = (a[l] <= pivot);
        bool right_ok = (a[r] >= pivot);
        if (a[l] <= pivot)
        {
            ++l;
        }
        else if (a[r] >= pivot)
        {
            r--;
        }
        else
        {
            swap(a[], l, r);
        }
    }
}

int main(int argc, char const *argv[])
{
    int n = 0;
    int k = 0;

    std::cin >> n;
    std::cin >> k;

    std::vector<int> arr;
    arr.resize(n);

    for (int& num: arr)
    {
        std::cin >> num;
    }

    std::cout << broken_search(arr, k) << std::endl;
    return 0;
}
