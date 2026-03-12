

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <random>
#include <filesystem>  // C++17 for directory creation
namespace fs = std::filesystem;

// ------------------------------------------------------------
// Quicksort implementation (in‑place, using indices)

 // Partitions the subarray arr[low..high] using the last element as pivot.
 // Returns the index of the pivot after partitioning.
 
int partition(int arr[], int low, int high) {
    int pivot = arr[high];      // pivot value
    int i = low - 1;            // index of smaller element

    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}


 // Recursive quicksort on arr[low..high].
 
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);   // partitioning index
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Helper: convert an integer array to a string

std::string arrayToString(const int arr[], int size) {
    std::ostringstream oss;
    for (int i = 0; i < size; ++i) {
        if (i > 0) oss << " ";
        oss << arr[i];
    }
    return oss.str();
}

// Main program

int main() {
    // Configuration
    const int m = 10;               // number of samples
    const int n = 100;              // elements per sample
    const std::string sampleDir = "samples";
    const std::string logFile = "log.txt";

    // Creating samples directory if it does not exist
    fs::create_directory(sampleDir);

    // Random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 999);   // numbers in [0,999]

    // Opening log file (truncate previous content)
    std::ofstream log(logFile);
    if (!log.is_open()) {
        std::cerr << "Failed to create log.txt\n";
        return 1;
    }

    // Write log header
    log << "Sorting Algorithm Integration Log\n";
    log << "==================================\n\n";

    // Process each sample
    for (int test = 1; test <= m; ++test) {
        log << "Test #" << test << "\n";

        // 1. Generate random sample
        int* arr = new int[n];
        for (int i = 0; i < n; ++i) {
            arr[i] = dist(gen);
        }

        // 2. Save unsorted sample to a file in samples/
        std::string sampleFileName = sampleDir + "/sample_" + std::to_string(test) + ".txt";
        std::ofstream sampleFile(sampleFileName);
        if (sampleFile.is_open()) {
            for (int i = 0; i < n; ++i) {
                sampleFile << arr[i] << "\n";
            }
            sampleFile.close();
        } else {
            std::cerr << "Warning: could not write " << sampleFileName << "\n";
        }

        // 3. Capture data BEFORE sorting
        std::string beforeStr = arrayToString(arr, n);

        // 4. Measure sorting time
        auto start = std::chrono::high_resolution_clock::now();
        quickSort(arr, 0, n - 1);
        auto end = std::chrono::high_resolution_clock::now();

        // 5. Capture data AFTER sorting
        std::string afterStr = arrayToString(arr, n);

        // 6. Compute duration in microseconds
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        // 7. Compute metrics
        //    - Number of variables: we treat each array element as a variable (n)
        //    - Memory acquired: n * sizeof(int) before and after (same)
        //    - Pointers used: we count the array pointer (1) – see note in comments
        //    - new/delete operations: 1 new for the array, 1 delete (to be done later)
        size_t varCount = n;
        size_t memoryBytes = n * sizeof(int);
        int ptrCount = 1;                // the array pointer `arr`
        int newCount = 1;                 // one new[] for the array
        // deleteCount will be logged after we actually delete

        // 8. Write all information to log.txt
        log << "  Start time (μs)   : " << std::chrono::time_point_cast<std::chrono::microseconds>(start).time_since_epoch().count() << "\n";
        log << "  End time (μs)     : " << std::chrono::time_point_cast<std::chrono::microseconds>(end).time_since_epoch().count() << "\n";
        log << "  Duration (μs)     : " << duration << "\n";
        log << "  Data before       : " << beforeStr << "\n";
        log << "  Data after        : " << afterStr << "\n";
        log << "  Variables created : " << varCount << "\n";
        log << "  Memory before (bytes) : " << memoryBytes << "\n";
        log << "  Memory after (bytes)  : " << memoryBytes << "\n";
        log << "  Pointers used     : " << ptrCount << "\n";
        log << "  new operations    : " << newCount << "\n";
        log << "  delete operations : " << "1 (will be called after logging)\n";
        log << "----------------------------------\n\n";

        // 9. Free the allocated memory (the delete operation)
        delete[] arr;
    }

    log.close();
    std::cout << "Done. Check " << logFile << " and the " << sampleDir << " folder.\n";
    return 0;
}