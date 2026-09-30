#include <iostream>
#include <vector>
#include <string>

template <class T>
class Stack 
{
private:
    std::vector<T> items;

public:
    void push(T item) {
        items.push_back(item);
    }

    T pop() {
        T lastItem = items.back();
        items.pop_back();
        return lastItem;
    }

    T peek() {
        return items.back();
    }

    int size() {
        return items.size();
    }
};



int main() 
{
    	int n;
    	std::cin >> n;

    	Stack<int> main_stack;
	Stack<int> max_stack;

    	std::string cmd;
    	int x;

    	while (n--) 
	{
        	std::cin >> cmd;
        	if (cmd == "push") 
		{
            		std::cin >> x;
            		main_stack.push(x);
			if (max_stack.size() == 0)
			{
				max_stack.push(x);
			}
			else
			{
				int max = max_stack.peek();
				max_stack.push(std::max(max, x));
			}
			
        	} 
		else if (cmd == "pop") 
		{
			if (main_stack.size() == 0)
			{
				std::cout << "error" << '\n';
			}
			else
			{
            			main_stack.pop();
				max_stack.pop();
			}
        	} 
		else if (cmd == "get_max") 
		{
			if (max_stack.size() == 0)
			{
				std::cout << "None" << '\n';
			}
			else
			{
				std::cout << max_stack.peek() << '\n';
			}
        	}
		else if (cmd == "top")
		{
			if (main_stack.size() == 0)
			{
				std::cout << "error" << '\n';
			}
			else
			{
				std::cout << main_stack.peek() << '\n';
			}
		}
    	}

    return 0;
}
