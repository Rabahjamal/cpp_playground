#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <vector>
#include <cmath>


void heapify(std::vector<int>& array, int i, int end)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    int max_idx = i;
    if(left <= end && array[left] > array[i])
        max_idx = left;

    if(right <= end && array[right] > array[max_idx])
        max_idx = right;

    if(max_idx != i)
    {
        std::swap(array[max_idx], array[i]);
        heapify(array, max_idx, end);
    }
}

void build_max_heap(std::vector<int>& array)
{
    int n = array.size() - 1;

    for(int i = floor(n / 2); i >= 0; i--)
    {
        heapify(array, i, array.size() - 1);
    }
}

void heap_sort(std::vector<int>& array)
{
    build_max_heap(array);

    int end = array.size() - 1;
    for(int i = array.size() - 1; i >= 0; i--)
    {
        std::swap(array[0], array[i]);
        end = end - 1;
        heapify(array, 0, end);
    }
}

#endif // HEAP_SORT_H
