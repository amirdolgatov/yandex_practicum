#include <algorithm>
#include <cassert>
#include <iterator>
#include <vector>

using Iterator = std::vector<int>::iterator;
using CIterator = std::vector<int>::const_iterator;

std::vector<int> merge(
    CIterator left_begin, CIterator left_end,
    CIterator right_begin, CIterator right_end)
{
    std::vector<int> result;
    result.reserve(std::distance(left_begin, left_end) +
                   std::distance(right_begin, right_end));

    while (left_begin != left_end && right_begin != right_end)
    {
        if (*left_begin <= *right_begin)
        {
            result.push_back(*left_begin);
            ++left_begin;
        }
        else
        {
            result.push_back(*right_begin);
            ++right_begin;
        }
    }

    result.insert(result.end(), left_begin, left_end);
    result.insert(result.end(), right_begin, right_end);

    return result;
}

void merge_sort(Iterator begin, Iterator end)
{
    auto n = std::distance(begin, end);
    if (n < 2)
        return;

    Iterator mid = begin + n / 2;

    merge_sort(begin, mid);
    merge_sort(mid, end);

    auto merged = merge(begin, mid, mid, end);
    std::copy(merged.begin(), merged.end(), begin);
}