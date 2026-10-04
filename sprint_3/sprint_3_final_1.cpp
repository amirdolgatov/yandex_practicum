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


int binarySearch(const std::vector<int>& arr, int x, int left, int right)
{
    if (right <= left)
    {
        // промежуток пуст
        return -1;
    }

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
        return binarySearch(arr, x, left, mid);
    }
    else
    {
        // иначе следует искать в правой половине
        return binarySearch(arr, x, mid + 1, right);
    }
}


int findZero(const std::vector<int>& arr, int left, int right)
{
    if (left >= right)
    {
        return left;
    }

    int mid = (left + right) / 2;
    if (arr[mid] > arr[right])
    {
        return findZero(arr, mid + 1, right); // граница правее
    }
    else
    {
        return findZero(arr, left, mid); // граница левее
    }
}


int broken_search(const std::vector<int>& vec, int k)
{
    int start = findZero(vec, 0, vec.size() - 1);
    int last = vec.size() - 1;

    if (k >= vec[start] && k <= vec[last])
    {
        if (k == vec[start])
        {
            return start;
        }
        else if (k == vec[last])
        {
            return last;
        }
        else
        {
            return binarySearch(vec, k, start, last);
        }
    }
    else if (start != 0 && k >= vec[0] && k <= vec[start - 1]) // чем дальше в лес, тем больше дров...
    {
        if (k == vec[0])
        {
            return 0;
        }
        else if (k == vec[start - 1])
        {
            return start - 1;
        }
        else
        {
            return binarySearch(vec, k, 0, start - 1);
        }
    }
    else
    {
        return -1;
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
