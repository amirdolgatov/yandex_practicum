// https://contest.yandex.ru/contest/23815/run-report/167403490/

/*
 * ИДЕЯ РЕШЕНИЯ
 *
 * Использовать алгоритм разбиения, приведенный в книге автора А.Шень, "Программирование. Теоремы и задачи."
 * Задача 1.2.32. 
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

// Участник соревнований
class Member
{
public:
    int points;         // решенные задачи
    int penalty;        // штраф
    std::string login;  // логин

    Member(int _points, int _penalty, const std::string& _login):
    points{_points}, penalty{_penalty}, login{_login}
    {}

     Member() = default;

    // lhs строго меньше rhs
    static bool is_less(const Member& lhs, const Member& rhs)
    {
        if (lhs.points != rhs.points)
        {
            return (lhs.points > rhs.points);
        }
        if (lhs.penalty != rhs.penalty)
        {
            return (lhs.penalty < rhs.penalty);
        }
        if (lhs.login != rhs.login)
        {
            return (lhs.login < rhs.login);
        }
        return false;
    }

    static bool is_equal(const Member& lhs, const Member& rhs)
    {
        return (lhs.points == rhs.points) && (lhs.penalty == rhs.penalty) && (lhs.login == rhs.login);
    }
};

// Источник идеи: А.Шень, "Программирование. Теоремы и задачи." 2017 г.
int partition(std::vector<Member>& vec, int l, int r)
{
    Member pivot = vec[(l + r) / 2];
    int m = l - 1;
    int left = l - 1;
    int right = r;

    while (m != right)
    {
        if (Member::is_equal(vec[m + 1], pivot)) 
        {
            m++;
        }
        else if (Member::is_less(pivot, vec[m + 1]))
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

void quicksort(std::vector<Member>& vec, int l, int r)
{
    if (l >= r)
    {
        return;
    }

    int m = partition(vec, l, r);
    quicksort(vec, l, m - 1);
    quicksort(vec, m + 1, r);
}

void print_vector(std::vector<Member>& v)
{
    for (const auto& m: v)
    {
        std::cout << m.login << '\n';
    }
}

int main(int argc, char const *argv[])
{
    int n = 0;

    std::cin >> n;

    std::vector<Member> v;
    v.resize(n);

    for (auto& member: v)
    {
        std::cin >> member.login;
        std::cin >> member.points;
        std::cin >> member.penalty;
    }

    quicksort(v, 0, v.size() - 1);
    print_vector(v);
    return 0;
}
    