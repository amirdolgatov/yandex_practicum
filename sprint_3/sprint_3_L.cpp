#include <iostream>
#include <vector>


int binarySearch(std::vector<int>& arr, int x, int left, int right) 
{
    if (right <= left) 
    {
        // промежуток пуст
        return left;
    }

    // промежуток не пуст
    int mid = (left + right) / 2;
    if (x <= arr[mid]) 
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


int main(int argc, char const *argv[])
{
    int n = 0;
    std::cin >> n;

    std::vector<int> arr;
    arr.resize(n);

    for (int& num: arr)
    {
        std::cin >> num;
    }

    std::cin >> n;

    int end = arr.size();

    if (n <= arr[end - 1])
    {
        int index = binarySearch(arr, n, 0, arr.size());
        std::cout << index + 1 << " ";
        if (2 * n <= arr[end - 1])
        {
            index = binarySearch(arr, 2 * n, index, arr.size());
            std::cout << index + 1 << std::endl;
        }
        else
        {
            std::cout << -1 << std::endl;
        }        
    }
    else
    {
        std::cout << -1 << " " << -1 << std::endl;
    }

   
    return 0;
}