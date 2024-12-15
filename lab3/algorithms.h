#include <iostream>
#include <vector>

#pragma once

struct stats {
    size_t comparison_count = 0;
    size_t copy_count = 0;
};


stats bubbleSort(std::vector<int>& arr) {
    stats s;
    size_t n = arr.size();
    bool swapped;
    for (size_t i = 0; i < n - 1; ++i) {
        swapped = false;
        for (size_t j = 0; j < n - i - 1; ++j) {
            s.comparison_count++;
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                s.copy_count += 3;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    return s;
}


stats combSort(std::vector<int>& arr) {
    stats s;
    size_t n = arr.size();
    double gap = n;
    bool swapped = true;

    while (gap > 1 || swapped) {
        gap = gap / 1.3;
        if (gap < 1) gap = 1;
        swapped = false;

        for (size_t i = 0; i < n - gap; ++i) {
            s.comparison_count++;
            if (arr[i] > arr[i + gap]) {
                std::swap(arr[i], arr[i + gap]);
                s.copy_count += 3;
                swapped = true;
            }
        }
    }
    return s;
}


void heapify(std::vector<int>& arr, size_t n, size_t i, stats& s) {
    size_t largest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    s.comparison_count++;
    if (left < n && arr[left] > arr[largest])
        largest = left;

    s.comparison_count++;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        s.copy_count += 3;
        heapify(arr, n, largest, s);
    }
}

stats heapSort(std::vector<int>& arr) {
    stats s;
    size_t n = arr.size();

    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(arr, n, i, s);

    for (int i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        s.copy_count += 3;
        heapify(arr, i, 0, s);
    }

    return s;
}