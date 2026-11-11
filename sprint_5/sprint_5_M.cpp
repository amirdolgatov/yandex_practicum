#include <vector>
#include <cassert>
#ifdef REMOTE_JUDGE
#include "solution.h"
#endif


// we add element to bottom 

int siftUp(std::vector<int>& heap, int idx) 
{
    if (idx <= 1)
    {
        return idx;
    }

    int parent = idx / 2;

    if (heap[idx] > heap[parent])
    {
        std::swap(heap[idx], heap[parent]);
        return siftUp(heap, parent);
    }
    else
    {
        return idx;
    }
}

#ifndef REMOTE_JUDGE
void test() 
{
    std::vector<int> sample = {-1, 12, 6, 8, 3, 15, 7};
    assert(siftUp(sample, 5) == 1);
}


int main() {
    test();
}
#endif