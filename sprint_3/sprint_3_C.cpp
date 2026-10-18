#include <iostream>
#include <vector>

bool is_subsequence(std::string& s, std::string& t)
{
    if (t.size() <= s.size())
    {
        int t_i = 0;
        int s_i = 0;

        while (t_i < t.size() && s_i < s.size())
        {
            if (t[t_i] == s[s_i])
            {
                ++t_i;
            }
            ++s_i;
        }

        return t_i == t.size();
    }
    return false;
}

int main(int argc, char const *argv[])
{
    std::string s, t;
    std::cin >> t;
    std::cin.ignore();
    std::cin >> s;

    if (is_subsequence(s, t))
    {
        std::cout << "True" << std::endl;
    }
    else
    {
        std::cout << "False" << std::endl;
    }

    return 0;
}
