#include <iostream>
#include <array>

int bst_num(const int num)
{
    int T[num + 1] = {};
    T[0] = 1;

    for (int i = 1; i <= num; i++)
    {
        for (int k = 0; k < i; k++)
        {
            T[i] += (T[k] * T[i - k - 1]);
        }
    }

    return T[num];
}

int main(void)
{
    int n;
    std::cin >> n;
    std::cout << bst_num(n) << std::endl;
    return 0;
}
