#include <vector>
#include <cassert>
#ifdef REMOTE_JUDGE
#include "solution.h"
#endif

// sift down

int siftDown(std::vector<int>& heap, int idx) 
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
        return siftDown(heap, max);
    }
    else
    {
        return idx;
    }
}

#ifndef REMOTE_JUDGE
void test() 
{
    std::vector<int> sample = {-1, 12, 1, 8, 3, 4, 7};
    assert(siftDown(sample, 2) == 5);
}


int main() {
    test();
}
#endif