// https://contest.yandex.ru/contest/24414/run-report/168494889/

/*
 * ИДЕЯ РЕШЕНИЯ
 *
 * Используется простейшее хеширование через взятие остатка от деления,
 * чтобы отобразить диапазон целых чисел в натуральные, используем операцию ((key % M) + M) % M.
 * Поскольку в C++ операция модуля возвращает отрицательные значения.
 *
 * Для разрешеия коллизий применим открытую адресацию.
 * Поскольку функция хеширования примитивная, нелавинная, применим линейное пробирование.  
 * Возьмем константу пробирования равную простому числу.  
 * 
 * Потребуем чтобы буффер хеш таблицы не заполнялся более чем на 75%.
 * Для это выберем объем массива M = 131927, при том что занято будет не более 100000 (по условию задачи)
 *
 * СЛОЖНОСТЬ
 * Сложность всех операций O(1),
 * в худшем случае, когда все клетки заняты, сложность может быть O(M).
 * 
 * ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ
 * Памяти нужно не более O(M), M - модуль хеширования
*/

#include <iostream>
#include <array>
#include <string>

enum class state { free = 0, occupied = 1, deleted = 2 };

struct entity
{
    int key = 0;
    int value = 0;
    state status = state::free;
};

class hash_table
{
private:
    static constexpr int M = 131927;         // размер массива и модуль хеша
    static constexpr int capacity = 100000;  // максимум ключей
    static constexpr int c = 41;             // шаг пробирования

    std::array<entity, M> data_buffer{};     // все элементы value-инициализированы
    int size = 0;

    inline int hash(int key) const
    {
        return ((key % M) + M) % M;
    }

    inline int linear_probing(int start) const
    {
        return (start + c) % M;
    }

public:

    int find_free(int key)
    {
        if (size < capacity)
        {
            int index = hash(key);
            while (data_buffer[index].status == state::occupied)
            {
                index = linear_probing(index);
            }
            return index;
        }
        return -1;
    }

    int find_value(int key)
    {
        if (size != 0)
        {
            int index = hash(key);
            while (data_buffer[index].status != state::free)
            {
                if (data_buffer[index].status == state::occupied &&
                    data_buffer[index].key == key)
                {
                    return index;
                }
                index = linear_probing(index);
            }
            return -1;
        }
        return -1;
    }

    bool delete_value(int key)
    {
        int index = find_value(key);
        if (index < 0)
        {
            return false;
        }

        data_buffer[index].status = state::deleted;
        size--;

        return true;
    }

    bool insert_value(int key, int data)
    {
        int index = find_value(key);
        if (index < 0)
        {
            index = find_free(key);
            if (index < 0)
            {
                return false;
            }

            data_buffer[index].key = key;
            data_buffer[index].value = data;
            data_buffer[index].status = state::occupied;
            size++;
        }
        else
        {
            data_buffer[index].value = data;
        }

        return true;
    }

    int get_value_at(int index) const
    {
        return data_buffer[index].value;
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    hash_table table;
    std::string cmd;

    while (n--)
    {
        std::cin >> cmd;

        if (cmd == "put")
        {
            int key, value;
            std::cin >> key >> value;
            table.insert_value(key, value);
        }
        else if (cmd == "get")
        {
            int key;
            std::cin >> key;
            int idx = table.find_value(key);
            if (idx == -1)
                std::cout << "None\n";
            else
                std::cout << table.get_value_at(idx) << "\n";
        }
        else if (cmd == "delete")
        {
            int key;
            std::cin >> key;
            int idx = table.find_value(key);
            if (idx == -1)
            {
                std::cout << "None\n";
            }
            else
            {
                std::cout << table.get_value_at(idx) << "\n";
                table.delete_value(key);
            }
        }
    }

    return 0;
}
