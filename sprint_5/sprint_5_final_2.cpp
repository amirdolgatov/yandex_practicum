#include <iostream>
#include <tuple>
#include <vector>

class member 
{
public:
    member(int points, int penalty, std::string login) 
        : points(points), penalty(penalty), login(std::move(login)) {}

    bool operator>(const member& other) const 
    {
        if (points != other.points) 
            return points > other.points;
        if (penalty != other.penalty) 
            return penalty < other.penalty;
        return login < other.login;
    }
    
    bool operator<(const member& other) const 
    {
        return other > *this;
    }

    const std::string& get_login() const 
    { 
        return login; 
    }
    
private:
    int points;
    int penalty;
    std::string login;
};

// we add element to bottom 
int sift_up(std::vector<member>& heap, int idx) 
{
    if (idx <= 1)
    {
        return idx;
    }

    int parent = idx / 2;

    if (heap[idx] > heap[parent])
    {
        std::swap(heap[idx], heap[parent]);
        return sift_up(heap, parent);
    }
    else
    {
        return idx;
    }
}

// sift down
int sift_down(std::vector<member>& heap, int idx) 
{
    int left =  2 * idx;
    int right = 2 * idx + 1;

    if (left >= heap.size())
    {
        return idx;
    }

    int max = left;

    if (right < heap.size() && heap[right] > heap[left])
    {
        max = right;
    }

    if (heap[max] > heap[idx])
    {
        std::swap(heap[max], heap[idx]);
        return sift_down(heap, max);
    }
    else
    {
        return idx;
    }
}

void heap_add(std::vector<member>& heap, member key) 
{
    heap.push_back(key);
    int index = heap.size() - 1;
    sift_up(heap, index);
}

member pop_max(std::vector<member>& heap) 
{
    member result = heap[1];
    heap[1] = heap[heap.size() - 1];
    heap.pop_back();
    sift_down(heap, 1);
    return result;
} 

void heapsort(const std::vector<member>& array) 
{
    // Создадим бинарную кучу с одним элементом
    std::vector<member> heap = { {0, 0, ""} };

    // Вставим в неё по одному все элементы массива, сохраняя свойства кучи.
    for (const auto& item : array) 
    {
        heap_add(heap, item);  
    }

    while (heap.size() > 1) 
    {
        auto max = pop_max(heap);
        std::cout << max.get_login() << '\n';
    }
}

int main(int argc, char const *argv[])
{
    int n = 0;
    std::cin >> n;
    std::vector<member> v;

    int points;
    int penalty;
    std::string login;

    while (n-- > 0)
    {
        std::cin >> login;
        std::cin >> points;
        std::cin >> penalty;
        v.emplace_back(points, penalty, login);
    }

    heapsort(v);
    return 0;
}