#include <iostream>
#include <vector>
#include <string>


template <class T>
class Stack 
{
private:
    std::vector<T> items;

public:
    void push(T item) 
    {
        items.push_back(item);
    }

    T pop() 
    {
        T lastItem = items.back();
        items.pop_back();
        return lastItem;
    }

    T peek() 
    {
        return items.back();
    }

    int size() 
    {
        return items.size();
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

	Stack stack;
    char symbol = 0;
    int op1, op2;
    int result;

    if (std::is_digit(symbol))
    {
    	stack.push(to_int(symbol));
    }
    else
    {
    	switch(symbol)
	    {
	    	case '+': 
	    	{
	    		op1 = stack.pop();
	    		op2 = stack.pop();
	    		result = op2 + op1;
	    		stack.push(result);
	    	} 
	    	break;
	    	case '-': 
	    	{
	    		op1 = stack.pop();
	    		op2 = stack.pop();
	    		result = op2 - op1;
	    		stack.push(result);
	    	} 
	    	break;
	    	case '*': 
	    	{
	    		op1 = stack.pop();
	    		op2 = stack.pop();
	    		result = op1 * op2;
	    		stack.push(result);
	    	} 
	    	break;
	    	case '/': 
	    	{
	    		op1 = stack.pop();
	    		op2 = stack.pop();
	    		result = op2 / op1;
	    		stack.push(result);
	    	} 
	    	break;
	    }
    }

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
