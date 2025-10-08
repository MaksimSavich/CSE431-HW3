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

// Attribution:https://www.geeksforgeeks.org/dsa/insertion-sort-algorithm/
void insertionSort(std::vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
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

// Hybrid Sort Implementation
void hybridSort(std::vector<int>& arr, int left, int right, int k) {
    if (left < right) {
        int size = right - left + 1;

        // If partition size <= k, use insertion sort
        if (size <= k) {
            insertionSort(arr, left, right);
        } else {
            // Otherwise, continue with merge sort
            int mid = left + (right - left) / 2;
            hybridSort(arr, left, mid, k);
            hybridSort(arr, mid + 1, right, k);
            merge(arr, left, mid, right);
        }
    }
}

// Hybrid Sort Overload
void hybridSort(std::vector<int>& arr, int k) {
    hybridSort(arr, 0, arr.size() - 1, k);
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

// Time hybrid sorting algorithm with multiple iterations
double timeHybridSort(int n, int k, int iterations) {
    std::clock_t total_time = 0;

    for (int iter = 0; iter < iterations; iter++) {
        // Generate fresh array for each iteration
        std::vector<int> arr = generateRandomArray(n);

        // Time the sorting
        std::clock_t start_time = std::clock();
        hybridSort(arr, k);
        std::clock_t end_time = std::clock();

        total_time += (end_time - start_time);

        // Check if the array is sorted
        if (iter == 0 && !isSorted(arr)) {
            std::cerr << "Error: Hybrid sort array not sorted correctly!" << std::endl;
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
    std::vector<int> test2 = test1;
    std::vector<int> test3 = test1;

    insertionSort(test1);
    mergeSort(test2);
    hybridSort(test3, 10);

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

    std::cout << "Hybrid Sort result: ";
    if (isSorted(test3)) {
        std::cout << "PASS" << std::endl;
    } else {
        std::cout << "FAIL" << std::endl;
        return 1;
    }

    std::cout << "Running Experiments" << std::endl;

    // Test different array sizes
    std::vector<int> test_sizes = { 100, 500, 1000, 2000, 5000, 10000, 25000, 50000, 100000
    };

    // Test different k values
    std::vector<int> k_values;

    // Generate k values
    for (int k = 1; k <= 20; k++) {
        k_values.push_back(k);
    }
    for (int k = 25; k <= 100; k += 5) {
        k_values.push_back(k);
    }
    for (int k = 120; k <= 1000; k += 20) {
        k_values.push_back(k);
    }

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "n,k,insertion_sort_ms,merge_sort_ms,hybrid_sort_ms" << std::endl;

    for (int n : test_sizes) {
        // Use more iterations for smaller inputs to get accurate measurements
        int iterations = std::max(1, 100000 / n);

        // Measure baseline algorithms once per n
        double insertion_time = timeSortingAlgorithm(insertionSort, n, iterations);
        double merge_time = timeSortingAlgorithm(mergeSort, n, iterations);

        double avg_insertion_ms = (insertion_time * 1000.0) / iterations;
        double avg_merge_ms = (merge_time * 1000.0) / iterations;

        // Test each k value
        for (int k : k_values) {
            double hybrid_time = timeHybridSort(n, k, iterations);
            double avg_hybrid_ms = (hybrid_time * 1000.0) / iterations;

            std::cout << n << "," << k << "," << avg_insertion_ms << ","
                     << avg_merge_ms << "," << avg_hybrid_ms << std::endl;
        }
    }

    return 0;
}
