#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <iomanip>

// Insertion Sort Implementation
// Attribution:https://www.geeksforgeeks.org/dsa/insertion-sort-algorithm/
void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Merge function for Merge Sort
// Attribution: https://www.geeksforgeeks.org/dsa/merge-sort/
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge Sort Implementation
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void mergeSort(std::vector<int>& arr) {
    mergeSort(arr, 0, arr.size() - 1);
}

// Generate random values for an array
std::vector<int> generateRandomArray(int n) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000; // Limit the element to be between 0 and 9999 to create larger variation in the arrays being sorted
    }
    return arr;
}

// Verify that the array is sorted
bool isSorted(const std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[i-1]) return false;
    }
    return true;
}

// Time a sorting algorithm with multiple iterations
double timeSortingAlgorithm(void (*sortFunc)(std::vector<int>&), int n, int iterations) {
    std::clock_t total_time = 0;

    for (int iter = 0; iter < iterations; iter++) {
        // Generate fresh array for each iteration
        std::vector<int> arr = generateRandomArray(n);

        // Time the sorting
        std::clock_t start_time = std::clock();
        sortFunc(arr);
        std::clock_t end_time = std::clock();

        total_time += (end_time - start_time);

        // Check if the array is sorted
        if (iter == 0 && !isSorted(arr)) {
            std::cerr << "Error: Array not sorted correctly!" << std::endl;
            return -1;
        }
    }

    return ((double)total_time) / (double)CLOCKS_PER_SEC;
}

int main() {
    // Set seed for random number generator
    srand(time(0));

    // Test correctness
    std::cout << "Testing correctness..." << std::endl;
    std::vector<int> test1 = {64, 34, 25, 12, 22, 11, 90};
    std::vector<int> test2 = test1; // Since the first array is already sorted, we need to create a new array for the second test

    insertionSort(test1);
    mergeSort(test2);

    std::cout << "Insertion Sort result: ";
    if (isSorted(test1)) {
        std::cout << "PASS" << std::endl;
    } else {
        std::cout << "FAIL" << std::endl;
        return 1;
    }

    std::cout << "Merge Sort result: ";
    if (isSorted(test2)) {
        std::cout << "PASS" << std::endl;
    } else {
        std::cout << "FAIL" << std::endl;
        return 1;
    }

    std::cout << "Running Experiments" << std::endl;

    // Generate array sizes to test
    std::vector<int> sizes;

    // Test every size from 1 to 1000
    for (int n = 1; n <= 1000; n++) {
        sizes.push_back(n);
    }

    // Large sizes beyond 1000: increment by 500
    for (int n = 1500; n <= 10000; n += 500) {
        sizes.push_back(n);
    }

    // Very large sizes beyond 10000: increment by 10000
    for (int n = 20000; n <= 100000; n += 20000) {
        sizes.push_back(n);
    }

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "n,insertion_sort_ms,merge_sort_ms" << std::endl;

    for (int n : sizes) {
        // Use more iterations for smaller inputs to get accurate measurements
        int iterations = std::max(1, 100000 / n);

        double insertion_time = timeSortingAlgorithm(insertionSort, n, iterations);
        double merge_time = timeSortingAlgorithm(mergeSort, n, iterations);

        double avg_insertion_ms = (insertion_time * 1000.0) / iterations;
        double avg_merge_ms = (merge_time * 1000.0) / iterations;

        std::cout << n << "," << avg_insertion_ms << "," << avg_merge_ms << std::endl;
    }

    return 0;
}
