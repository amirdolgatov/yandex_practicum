#include <iostream>
#include <string>

struct entity
{
    int key;
    int value;
    bool is_deleted;
    bool is_occupied;
};

class hash_table
{
private:
    static constexpr int M = 131927;         // размер массива и модуль хеша — одно и то же число
    static constexpr int capacity = 100000;  // максимум ключей
    static constexpr int c = 41;            // тоже простое число, не слишком большое, чтобы попадать в кэш (вначале было 757)

    entity data_buffer[M] = {};              // массив размером M
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
            while (data_buffer[index].is_occupied)
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
            while (data_buffer[index].is_occupied || data_buffer[index].is_deleted)
            {
                if (data_buffer[index].is_occupied && data_buffer[index].key == key)
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

        data_buffer[index].is_occupied = false;
        data_buffer[index].is_deleted = true;
        size--;

        return true;
    }

    bool insert_value(int key, int data)
    {
        // а может такой уже есть ?
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
            data_buffer[index].is_occupied = true;
            data_buffer[index].is_deleted = false;
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

#include <iostream>
#include <string>

int main() {
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
            {
                std::cout << "None\n";
            }
            else
            {
                std::cout << table.get_value_at(idx) << "\n";
            }
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
