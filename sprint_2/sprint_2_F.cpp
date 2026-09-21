#include <iostream>
#include <vector>
struct Node
{
	int n = 0;
	Node *next = nullptr;
    Node *prev = nullptr;
};

struct ordered_list
{
	Node *head = nullptr;

	Node *get_head()
	{
		return head;
	}

	Node *insert(int n)
	{
		Node *node = new Node;
		node->n = n;

		if (head == nullptr)
		{
			head = node;
		}
		else
		{
			Node *it = head;
			while(it->next != nullptr && it->n >= n)
			{
				it = it->next;
			}
            if (it->next == nullptr && it->n >= n)
			{
				node->prev = it;
				it->next = node;
			}
			else
			{
				node->prev = it->prev;
				node->next = it;
				it->prev = node;
				if (node->prev)
				{
					node->prev->next = node;
				}
                if (it == head)
                {
                    head = node;
                }
			}
		}
        return node;
	}

    void erase(Node *node)
	{
        if (node == head)
        {
            if (head->next)
            {
                head = head->next;
                head->prev = nullptr;
            }
            else
            {
                head = nullptr;
            }
        }
        else
        {
            if (node->next)
            {
                node->next->prev = node->prev;
            }
            node->prev->next = node->next;
        }
        delete node;
	}
};

struct StackMax
{
    void pop()
    {
        if (items.empty())
        {
            std::cout << "error" << '\n';
        }
        else
        {
            Node *item = items.back();
            max_list.erase(item);
            items.pop_back();
        }
    }

    void push(int x)
    {
        Node *item = max_list.insert(x);
        items.push_back(item);
    }

    void get_max()
    {
        Node *top = max_list.get_head();
        if (top)
        {
            std::cout << top->n << '\n';
        }
        else
        {
            std::cout << "None" << '\n';
        }
    }

    std::vector<Node*> items;
    ordered_list max_list;
};

int main() {
    int n;
    std::cin >> n;

    StackMax s;
    std::string cmd;
    int x;

    while (n--) {
        std::cin >> cmd;
        if (cmd == "push") {
            std::cin >> x;
            s.push(x);
        } else if (cmd == "pop") {
            s.pop();
        } else if (cmd == "get_max") {
            s.get_max();
        }
    }

    return 0;
}
