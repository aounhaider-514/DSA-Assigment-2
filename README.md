# DSA Assignment 2 – Sorting Algorithm Integration with Logging and Analysis

This project implements the **Quick Sort** algorithm to sort multiple randomly generated datasets.  
For each dataset (sample), detailed performance and memory metrics are logged into a single file (`log.txt`).  
The unsorted data is saved in separate files inside a `samples/` folder.  
A Python script is provided to visualise the sorting times across the samples.

## Features

- **Quick Sort** (in‑place, recursive implementation)
- Generates **10 samples** (configurable) each containing **100 random integers**
- For every sample:
  - Saves unsorted data to `samples/sample_<N>.txt`
  - Records:
    - Start and end time (microsecond precision)
    - Sorting duration
    - Data before and after sorting
    - Number of variables (interpreted as the array size)
    - Estimated memory usage before/after
    - Number of pointers used (the array pointer)
    - Number of `new`/`delete` operations
  - Appends all information to `log.txt`
- Python plotting script to visualise sorting durations

## Requirements

- **C++17** compatible compiler (e.g., `g++`, `clang++`)
- (Optional) **Python 3** with `matplotlib` for plotting

## Compilation and Execution

1. **Clone** the repository or download the source files.

2. Open a terminal in the directory containing `assignment_2.cpp`.

3. **Compile** the C++ program:
   ```bash
   g++ -std=c++17 assignment_2.cpp -o assignment_2
