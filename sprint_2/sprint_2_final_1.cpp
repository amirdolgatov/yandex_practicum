// https://contest.yandex.ru/contest/22781/run-report/166749216/

#include <iostream>
#include <vector>

/*
-- ПРИНЦИП РАБОТЫ --

Реализован дек, на основе std::vector.
Поскольку максимальный размер известен заранее (capacity), то возможно использование кольцевого буфера в памяти std::vector.
Произведена доработка реализации очереди. 

Интуитивно может показаться, что добавление push_front производится также,
как и привычное добавление в конец контейнера: вначале записать элемент, затем сместить указатель (декрементировать при добавлении
в начало, при добавлении в конец мы инкрементируем указатель).
Такой подход создаст проблему при пустом деке. Лучший подход это вначале декрементировать указатель, затем записывать данные.
При изьятии элемента с начала pop_front, считываем данные, затем смещаем указатель.

Для оперций с хвостом дека, действия зеркальные: при добавлении, вначале пишем данные, затем смещаем указатель,
при изъятии смещаем указатель, затем читаем данные.


-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --

Размер известине заранее , память предвыделяется, переполнения не должно быть.
Во избежания перезаписи данных или некорреткного извлечения, всегда контроллируется размер 
дека. Поддерживаются следующие инварианты:

    - head всегда указывает на начало дека
    - size никогда не превосходит доступный объем памяти capacity 

-- ВРЕМЕННАЯ СЛОЖНОСТЬ --

Все операции это операции с непрерывным массивом памяти, с известными адресами для извлечения 
и добавления элементов. Все операции имеют сложность O(1).

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --

Объем требуемой памяти фиксирован и известен заранее, пространственная сложность O(n).
*/

class Deque
{
private:

	std::vector<int> array;

    /* итераторы */
    int head;
    int tail;

    int capacity;
    int size;

public:

	Deque(int n):head{0}, tail{0}, capacity{n}, size{0}
	{
        array.resize(n);
    }

    bool is_empty() 
    {
        return size == 0;
    }

    bool push_back(int x) 
    {
        if (size != capacity) 
        {
            array[tail] = x;
            tail = (tail + 1) % capacity;
            ++size;
            return true;
        }
        return false;
    }

    bool push_front(int x) 
    {
        if (size != capacity) 
        {
            head = (head - 1 + capacity) % capacity; // step back
            array[head] = x;
            ++size;
            return true;
        }
        return false;
    }

    bool pop_back(int& data) 
    {
        if (is_empty())
        {
            return false;
        }
        else
        {
            tail = (tail - 1 + capacity) % capacity;
            data = array[tail];
            size--;
            return true;
        }        
    }

    bool pop_front(int& data) 
    {
        if (is_empty())
        {
            return false;
        }
        else
        {
            data = array[head];
            head = (head + 1) % capacity;
            size--;
            return true;
        }        
    }
}; 

int main(void)
{
	int n, m;
    std::cin >> n;
    std::cin >> m;

    Deque deque(m);
    std::string cmd;
    int data;
    bool error = true;

    while (n--) 
    {
        std::cin >> cmd;

        if (cmd == "push_back") 
        {
            std::cin >> data;
            bool result = deque.push_back(data);
            error = !result;
        } 
        else if (cmd == "push_front") 
        {
            std::cin >> data;
            bool result = deque.push_front(data);
            error = !result;
        } 
        else if (cmd == "pop_back") 
        {
            bool result = deque.pop_back(data);
            error = !result;
        	if (result)
        	{
        		std::cout << data << '\n';
        	}
        } 
        else if (cmd == "pop_front") 
        {
            bool result = deque.pop_front(data);
            error = !result;
            if (result)
            {
                std::cout << data << '\n';
            }
        }

        if (error)
        {
        	std::cout << "error\n";
        }
    }

	return 0;
}