#include <iostream>
#include <unordered_map>
#include <string>
#include <random>

// Если сравнивать только с хешем первой строки
//     Пусть R = 123987123. Вы генерируете случайную строку и проверяете: h(new) == h(first)?.
//     Вероятность совпадения с одним конкретным хешем:
//      P ≈ 1 / R ≈ 1 / 1.24·10⁸

/*
 *
 * Если хранить все встреченные хеши
 * Тогда вы сравниваете новую строку не с одной, а со всеми предыдущими.
 * После генерации k строк число возможных пар:
 *
 * k ≈ sqrt(2R) ≈ sqrt(2.48·10⁸) ≈ 15 700
 */

const long long A = 1000;
const long long M = 123987123;

long long get_hash(const std::string& s) {
    long long h = 0;
    for (unsigned char c : s) {
        h = (h * A + c) % M;
    }
    return h;
}

int main()
{
    std::mt19937 rng(12345);
    // Это распределение. Оно превращает «сырые» числа из rng в числа из заданного диапазона равномерно (без смещения).
    std::uniform_int_distribution<int> len_dist(10, 20);
    // То же самое, но для символов. 'a' = 97, 'z' = 122. Возвращает число от 97 до 122, которое мы приводим к char
    std::uniform_int_distribution<int> char_dist('a', 'z');

    std::unordered_map<long long, std::string> seen;

    long long iter = 0;

    while (true)
    {
        ++iter;
        int len = len_dist(rng);
        std::string s;
        for (int i = 0; i < len; ++i)
        {
            s.push_back(static_cast<char>(char_dist(rng)));
        }

        long long h = get_hash(s);

        auto it = seen.find(h);
        if (it != seen.end() && it->second != s)
        {
            std::cout << it->second << "\n" << s << "\n" << iter << std::endl;
            return 0;
        }

        seen[h] = s;
    }
}
