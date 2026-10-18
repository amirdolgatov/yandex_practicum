#include<iostream>
#include<unordered_map>
#include<vector>

long long str_hash(const std::string& str, int q, int R, int len)
{
    long long hash = 0;
    for(int i = 0; i < len; i++)
    {
        hash = (hash * q + str[i]) % R;
    }
    return hash;
}

int main()
{
    std::string input;
    long long m, q;
    int t;
    std::vector<int64_t> base;
    std::vector<std::pair<int, int>> indexes;
    std::unordered_map<int, long long> hashes;

    std::cin >> q;
    std::cin >> m;
    std::cin.ignore(); // Удаляет символ новой строки
    std::cin >> input;
    std::cin >> t;

    while(t--)
    {
        int l;
        int r;
        std::cin >> l >> r;
        indexes.emplace_back(l, r);
    }

    base.resize(input.size() + 1);

    long long left_hash;
    long long right_hash;

    base[0] = 1;
    for (int i = 1; i <= input.size(); i++)
    {
        base[i] = (base[i - 1] * q) % m;
    }

    for (auto& [l, r]: indexes)
    {
        // have l hash ?
        auto iter = hashes.find(l - 1);
        if (iter == hashes.end())
        {
            // have not
            left_hash = str_hash(input, q, m, l - 1);
            hashes[l - 1] = left_hash;
        }
        else
        {
            left_hash = iter->second;
        }

        // have r hash ?
        iter = hashes.find(r);
        if (iter == hashes.end())
        {
            // have not
            right_hash = str_hash(input, q, m, r);
            hashes[r] = right_hash;
        }
        else
        {
            right_hash = iter->second;
        }

        int a = base[r - l + 1];

        // std::cout << "right_hash = " << right_hash << '\n';
        // std::cout << "left_hash = " << left_hash << '\n';
        // std::cout << "q = " << a << '\n';

        std::cout << (right_hash + m - ((left_hash * a) % m) ) % m << '\n';
    }

}
