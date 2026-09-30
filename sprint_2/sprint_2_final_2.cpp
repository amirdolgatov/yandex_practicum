https://contest.yandex.ru/contest/22781/run-report/166346604/

#include <iostream>
#include <vector>
#include <string>

/*
-- ПРИНЦИП РАБОТЫ --

Реализован калькулятор на основе стека.
Операнды помещаются в стек.
Оператор, введенный пользователем, применяется к числу на вершине стека и
числу лежащему под вершиной. 

-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --

В обратной польской записи в начале записаны операнды, затем 
ариметический оператор, что легко реализовывается с помощью стека.

-- ВРЕМЕННАЯ СЛОЖНОСТЬ --

Каждая операция стека это O(1), соответственно при количестве операторов и операндов n,
получим сложность n * O(1) = O(n).

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --

Операнды помещаются и извлекаются из стека.
В худшем случае, если только добавлять операнды, пространственная сложность O(n).
*/

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

class Calculator
{
private:
    Stack<int> stack;
public:
    void process_token(std::string& token)
    {
        if ((token == "+") || (token == "-") || (token == "*") || (token == "/"))  // operator
        {
            int op1, op2;
            int result;
            char symbol = token[0];

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
                    result = floor_div(op2, op1);
                    stack.push(result);
                } 
                break;
            }
        }
        else
        {
            stack.push(stoi(token));                  // operand
        }
    }

    void get_result()
    {
        if (stack.size() == 0)
        {
            std::cout << "Error\n";
        }
        else
        {
            std::cout << stack.pop() << "\n";
        }
    }

    int floor_div(int a, int b) 
    {
        int q = a / b;
        int r = a % b;
        if (r != 0 && ((r < 0) != (b < 0))) 
        {
            --q;
        }
        return q;
    }
};


int main(void)
{
    std::string token;
    Calculator calculator;

    while (std::cin >> token) 
    {
        calculator.process_token(token);
    }

    calculator.get_result();

	return 0;
}
