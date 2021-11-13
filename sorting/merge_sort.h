#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <vector>

template <typename T>
std::vector<T>
merge(const std::vector<T>& left, const std::vector<T>& right)
{
    int i = 0, j = 0;

    std::vector<T> output;

    while(i < left.size() && j < right.size())
    {
        if(left[i] <= right[j])
        {
            output.push_back(left[i++]);
        }
        else
        {
            output.push_back(right[j++]);
        }
    }

    if(i != left.size())
    {
        while(i < left.size())
        {
            output.push_back(left[i++]);
        }
    }

    if(j != right.size())
    {
        while(j < right.size())
        {
            output.push_back(right[j++]);
        }
    }

    return output;
}

template <typename T>
std::vector<T>
merge_sort(const std::vector<T>& numbers)
{
    if(numbers.size() == 1)
    {
        return {numbers[0]};
    }

    int mid = numbers.size() / 2;

    std::vector<T> left(numbers.begin(), numbers.begin() + mid);
    std::vector<T> right(numbers.begin() + mid, numbers.end());

    auto left_merged = merge_sort(left);
    auto right_merged = merge_sort(right);

    return merge(left_merged, right_merged);
}

#endif // MERGE_SORT_H
