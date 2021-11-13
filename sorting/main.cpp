#include "merge_sort.h"
#include "quick_sort.h"
#include "heap_sort.h"

#include <iostream>
#include <algorithm>
#include <chrono>

using namespace std;

int main()
{
    vector<int> arr;
    for(size_t i = 0; i < 100; i++)
    {
        arr.push_back(std::rand() % 100);
    }

    auto start = chrono::high_resolution_clock::now();
    vector<int> sorted = merge_sort(arr);
    auto end = chrono::high_resolution_clock::now();

    for(auto num : sorted)
    {
        cout << num << " ";
    }
    cout << endl;
    cout << "Elapsed Time = " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;

    start = chrono::high_resolution_clock::now();
    vector<int> tmp = arr;
    quick_sort(tmp, 0, tmp.size() - 1);
    end = chrono::high_resolution_clock::now();

    for(auto num : tmp)
    {
        cout << num << " ";
    }
    cout << endl;
    cout << "Elapsed Time = " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;

    start = chrono::high_resolution_clock::now();
    arr = {2, 8, 5, 3, 9, 1};
    heap_sort(arr);
    end = chrono::high_resolution_clock::now();
    for(auto num : arr)
    {
        cout << num << " ";
    }
    cout << endl;
    cout << "Elapsed Time = " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;


}
