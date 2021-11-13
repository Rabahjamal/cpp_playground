#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <vector>
#include <algorithm>
#include <iostream>

template <typename T>
int partition(std::vector<T>& array, int start, int end)
{
    int pivot_index = end;
    int pivot = array[pivot_index];
    int partition_index = start;

    for(int i = start; i <= end; i++)
    {
        if(i == pivot_index)
            continue;

        if(array[i] <= pivot)
        {
            std::swap(array[i], array[partition_index]);
            partition_index++;
        }
    }

    std::swap(array[partition_index], array[pivot_index]);

    return partition_index;

}

template <typename T>
void quick_sort(std::vector<T>& array, int start, int end)
{
    if(start >= end)
    {
        return;
    }

    int p = partition(array, start, end);

    quick_sort(array, start, p - 1);
    quick_sort(array, p+1, end);
}


#endif // QUICK_SORT_H
