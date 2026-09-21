#include <iostream>
#include <vector>

class Queue 
{
private:

	std::vector<int> queue;
    int head;
    int tail;
    int max_n;
    int size;

public:

	Queue(int n) 
	{
        queue.resize(n);
        head = 0;
        tail = 0;
        max_n = n;
        size = 0;
     }

    bool is_empty() 
    {
        return size == 0;
    }

    bool push_back(int x) 
    {
        if (size != max_n) 
        {
            queue[tail] = x;
            tail = (tail + 1) % max_n;
            size += 1;
            return true;
        }
        return false;
    }

    bool push_front(int x) 
    {
        if (size != max_n) 
        {
            queue[head] = x;
            head = (head - 1 + max_n) % max_n; // step back
            size += 1;
            return true;
        }
        return false;
    }

    void pop_back() 
    {
        tail = (tail - 1 + max_n) % max_n;
        size -= 1;
    }

    void pop_front() 
    {
        head = (head + 1) % max_n;
        size -= 1;
    }

    int *back()
    {
    	std::cout << "tail " << tail << '\n';
    	if (is_empty()) 
        {
            return nullptr;
        }
        return &queue[tail];
    }

    int *front()
    {
    	std::cout << "head " << head << '\n';
    	if (is_empty()) 
        {
            return nullptr;
        }
        return &queue[head];
    }
}; 

int main(void)
{
	int n, m;
    std::cin >> n;
    std::cin >> m;

    Queue q(m);
    std::string cmd;
    int x;
    bool error = true;

    while (n--) 
    {
        std::cin >> cmd;

        if (cmd == "push_back") 
        {
            std::cin >> x;
            error = !(q.push_back(x));
        } 
        if (cmd == "push_front") 
        {
            std::cin >> x;
            error = !(q.push_front(x));
        } 
        else if (cmd == "pop_back") 
        {
        	int *data_ptr = q.back();
        	if (data_ptr == nullptr)
        	{
        		error = true;
        	}
        	else
        	{
        		std::cout << *data_ptr << '\n';
        		q.pop_back();
        		error = false;
        	}
        } 
        else if (cmd == "pop_front") 
        {
            int *data_ptr = q.front();
        	if (data_ptr == nullptr)
        	{
        		error = true;
        	}
        	else
        	{
        		std::cout << *data_ptr << '\n';
        		q.pop_front();
        		error = false;
        	}
        }

        if (error)
        {
        	std::cout << "error\n";
        }
    }

	return 0;
}