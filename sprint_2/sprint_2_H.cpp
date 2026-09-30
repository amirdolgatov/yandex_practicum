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

inline char twin(char c)
{
	if(c == '}')
	{
		return '{';
	}
	else if (c == ']')
	{
		return '[';
	}
	else if (c == ')')
	{
		return '(';
	}
	return c;
}

int main()
{
	Stack<char> s;
	std::string str;
	std::getline(std::cin, str);
	
	for (auto ch: str)
	{
		switch (ch)
		{
			case '[':
			case '(':
			case '{':
			{
				s.push(ch);
			}
			break;
			
			case ']':
			case ')':
			case '}':
			{
				if (s.size() == 0)
				{
					std::cout << "False" << '\n';
					return 0;
				}
				else
				{
					auto top = s.pop();
					auto t = twin(ch);
					if (top != t)
					{
						std::cout << "False" << '\n';
						return 0;
					}
				}
			}
			break;
			default:
			{
				std::cout << "False" << '\n';
			}
			break;
		}
	}
	if (s.size() == 0)
	{
		std::cout << "True" << '\n';
	}
	else
	{
		std::cout << "False" << '\n';
	}
	return 0;
}
