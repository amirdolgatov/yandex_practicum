#include <iostream>
#include <vector>
#include <unordered_map>

long long str_hash(const std::string& str, int q, int R)
{
    long long hash = 0;
    for(char s: str)
    {
        hash = (hash * q + s) % R;
    }
    return hash;
}

int main(int argc, char const *argv[])
{
    std::string s;
    int q, M;
    std::cin >> q;
    std::cin >> M;
    std::cin.ignore(); // Удаляет символ новой строки
    std::cin >> s;

    std::cout << str_hash(s, q, M) << std::endl;

    return 0;
}
