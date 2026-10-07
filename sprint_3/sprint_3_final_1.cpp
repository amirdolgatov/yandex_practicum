// https://contest.yandex.ru/contest/23815/run-report/167502974/

/*
 * ИДЕЯ РЕШЕНИЯ
 *
 * В сломанном массиве расположены два отсортированных подмассива
 * Если нам будет известна грань, то мы можем провести бинарный поиск в каждом
 * 
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
 * Дополнительной памяти не требуется (кроме входного массива).
*/

#include <iostream>
#include <vector>

// инвариант {если x етсь в массиве, то он в полуинтервале [l, r)}
int binarySearch(const std::vector<int>& arr, int x, int left, int right)
{
    while (left < right)  // работаем на полуинтервале [l, r)
    {
        // промежуток не пуст
        int mid = (left + right) / 2;
        if (arr[mid] == x)
        {
            // искомый элемент меньше центрального значит следует искать в левой половине
            return mid;
        }
        else if (x < arr[mid])
        {
            // искомый элемент меньше центрального значит следует искать в левой половине
            right = mid;
        }
        else
        {
            // иначе следует искать в правой половине
            left = mid + 1;
        }
    }
    // промежуток пуст
    return -1;
}

// инвариант {минимум массива в полуинтервале [l, r)}
int findZero(const std::vector<int>& arr, int left, int right)
{
    while (left < right)
    {
        int mid = (left + right) / 2;
        if (arr[mid] > arr[right])
        {
            left = mid + 1; // граница правее
        }
        else
        {
            right = mid; // граница левее
        }
    }

    return left;
}


int broken_search(const std::vector<int>& vec, int k)
{
    int start = findZero(vec, 0, vec.size() - 1);  // начальный (минимальный) элемент

    if (k <= vec.back())  // поиск 
    {
        return binarySearch(vec, k, start, vec.size());
    }
    else
    {
        return binarySearch(vec, k, 0, start);
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
