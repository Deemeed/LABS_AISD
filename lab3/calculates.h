#include <fstream>
#include <random>
#include <chrono>

#include "algorithms.h"

#pragma once

// √енераци€ случайного массива
std::vector<int> generateRandomArray(size_t size, int seed) {
    std::vector<int> arr(size);
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dis(1, 1000000);
    for (size_t i = 0; i < size; ++i) {
        arr[i] = dis(gen);
    }
    return arr;
}

// √енераци€ полностью отсортированного массива
std::vector<int> generateSortedArray(size_t size) {
    std::vector<int> arr(size);
    for (size_t i = 0; i < size; ++i) {
        arr[i] = i + 1;
    }
    return arr;
}

// √енераци€ обратно отсортированного массива
std::vector<int> generateReverseSortedArray(size_t size) {
    std::vector<int> arr(size);
    for (size_t i = 0; i < size; ++i) {
        arr[i] = size - i;
    }
    return arr;
}

void saveToCSV(const std::string& filename, const std::vector<std::vector<std::string>>& data) {
    std::ofstream file(filename);
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) file << ",";
        }
        file << "\n";
    }
    file.close();
}

void print_calculates() {
    std::vector<size_t> sizes = { 1000, 2000, 3000, 4000, 5000, 10000, 25000, 50000, 100000 };
    const int num_trials = 3;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::vector<std::vector<std::string>> csv_data = {
        {"Size", "BubbleSort_Comparisons_Random", "BubbleSort_Copies_Random", "CombSort_Comparisons_Random", "CombSort_Copies_Random", "HeapSort_Comparisons_Random", "HeapSort_Copies_Random",
         "BubbleSort_Comparisons_Sorted", "BubbleSort_Copies_Sorted", "CombSort_Comparisons_Sorted", "CombSort_Copies_Sorted", "HeapSort_Comparisons_Sorted", "HeapSort_Copies_Sorted",
         "BubbleSort_Comparisons_Reverse", "BubbleSort_Copies_Reverse", "CombSort_Comparisons_Reverse", "CombSort_Copies_Reverse", "HeapSort_Comparisons_Reverse", "HeapSort_Copies_Reverse"}
    };

    for (size_t size : sizes) {
        // —реднее значение дл€ случайных массивов
        stats avg_bubble_sort = { 0, 0 };
        stats avg_comb_sort = { 0, 0 };
        stats avg_heap_sort = { 0, 0 };

        for (int i = 0; i < num_trials; ++i) {
            std::vector<int> arr = generateRandomArray(size, seed + i);
            std::vector<int> arr1 = arr;
            std::vector<int> arr2 = arr;
            std::vector<int> arr3 = arr;

            stats s1 = bubbleSort(arr1);
            stats s2 = combSort(arr2);
            stats s3 = heapSort(arr3);

            avg_bubble_sort.comparison_count += s1.comparison_count;
            avg_bubble_sort.copy_count += s1.copy_count;

            avg_comb_sort.comparison_count += s2.comparison_count;
            avg_comb_sort.copy_count += s2.copy_count;

            avg_heap_sort.comparison_count += s3.comparison_count;
            avg_heap_sort.copy_count += s3.copy_count;
        }

        avg_bubble_sort.comparison_count /= num_trials;
        avg_bubble_sort.copy_count /= num_trials;

        avg_comb_sort.comparison_count /= num_trials;
        avg_comb_sort.copy_count /= num_trials;

        avg_heap_sort.comparison_count /= num_trials;
        avg_heap_sort.copy_count /= num_trials;

        std::cout << "Size: " << size << std::endl;
        std::cout << "Bubble Sort (Average): Comparisons = " << avg_bubble_sort.comparison_count << ", Copies = " << avg_bubble_sort.copy_count << std::endl;
        std::cout << "Comb Sort (Average): Comparisons = " << avg_comb_sort.comparison_count << ", Copies = " << avg_comb_sort.copy_count << std::endl;
        std::cout << "Heap Sort (Average): Comparisons = " << avg_heap_sort.comparison_count << ", Copies = " << avg_heap_sort.copy_count << std::endl;

        // ѕолностью отсортированный массив
        std::vector<int> sorted_arr = generateSortedArray(size);
        std::vector<int> sorted_arr1 = sorted_arr;
        std::vector<int> sorted_arr2 = sorted_arr;
        std::vector<int> sorted_arr3 = sorted_arr;

        stats s1 = bubbleSort(sorted_arr1);
        stats s2 = combSort(sorted_arr2);
        stats s3 = heapSort(sorted_arr3);

        std::cout << "Bubble Sort (Sorted): Comparisons = " << s1.comparison_count << ", Copies = " << s1.copy_count << std::endl;
        std::cout << "Comb Sort (Sorted): Comparisons = " << s2.comparison_count << ", Copies = " << s2.copy_count << std::endl;
        std::cout << "Heap Sort (Sorted): Comparisons = " << s3.comparison_count << ", Copies = " << s3.copy_count << std::endl;

        // ќбратно отсортированный массив
        std::vector<int> reverse_sorted_arr = generateReverseSortedArray(size);
        std::vector<int> reverse_sorted_arr1 = reverse_sorted_arr;
        std::vector<int> reverse_sorted_arr2 = reverse_sorted_arr;
        std::vector<int> reverse_sorted_arr3 = reverse_sorted_arr;

        s1 = bubbleSort(reverse_sorted_arr1);
        s2 = combSort(reverse_sorted_arr2);
        s3 = heapSort(reverse_sorted_arr3);

        std::cout << "Bubble Sort (Reverse Sorted): Comparisons = " << s1.comparison_count << ", Copies = " << s1.copy_count << std::endl;
        std::cout << "Comb Sort (Reverse Sorted): Comparisons = " << s2.comparison_count << ", Copies = " << s2.copy_count << std::endl;
        std::cout << "Heap Sort (Reverse Sorted): Comparisons = " << s3.comparison_count << ", Copies = " << s3.copy_count << std::endl;

        std::cout << std::endl;

        csv_data.push_back({
            std::to_string(size),
            std::to_string(avg_bubble_sort.comparison_count), std::to_string(avg_bubble_sort.copy_count),
            std::to_string(avg_comb_sort.comparison_count), std::to_string(avg_comb_sort.copy_count),
            std::to_string(avg_heap_sort.comparison_count), std::to_string(avg_heap_sort.copy_count),
            std::to_string(s1.comparison_count), std::to_string(s1.copy_count),
            std::to_string(s2.comparison_count), std::to_string(s2.copy_count),
            std::to_string(s3.comparison_count), std::to_string(s3.copy_count),
            std::to_string(s1.comparison_count), std::to_string(s1.copy_count),
            std::to_string(s2.comparison_count), std::to_string(s2.copy_count),
            std::to_string(s3.comparison_count), std::to_string(s3.copy_count)
            });
    }

    saveToCSV("C:/Users/user/labsaisd/lab3/results/sorting_results.csv", csv_data);
}