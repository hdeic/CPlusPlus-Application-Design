/*
 * Course: CIS-25 - Programming Using C++
 * Student: H Cheng
 * Module: Module 4 - Functions, Arrays, and Pointers
 * Reference: GitHub Binary Search Example (gist.github.com/christophewang/da7e308c627dcc816831)
 *
 * Description:
 * Implements an iterative binary search algorithm in C++ using functions and pointers
 * to search for a target value within a sorted array of release years from the Kaggle dataset.
 */

#include <iostream>
#include <iomanip>

using namespace std;

// Binary search function using array indexing
int binarySearch(const int arr[], int size, int target) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid; // Target found
        } else if (arr[mid] < target) {
            low = mid + 1; // Search right half
        } else {
            high = mid - 1; // Search left half
        }
    }
    return -1; // Target not found
}

// Binary search demonstration using pointer arithmetic
int binarySearchWithPointer(const int *basePtr, int size, int target) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int midVal = *(basePtr + mid); // Pointer dereference with offset

        if (midVal == target) {
            return mid;
        } else if (midVal < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int main() {
    // Sorted array of song release years from the dataset
    const int SIZE = 8;
    int sortedYears[SIZE] = {2016, 2016, 2017, 2018, 2018, 2019, 2021, 2022};

    cout << "========================================================\n";
    cout << "        Module 4 - Binary Search Demonstration          \n";
    cout << "========================================================\n";
    cout << "Sorted Years Array: ";
    for (int i = 0; i < SIZE; i++) {
        cout << sortedYears[i] << " ";
    }
    cout << "\n--------------------------------------------------------\n";

    // Test cases
    int searchTargets[] = {2019, 2021, 2025};

    for (int target : searchTargets) {
        int index = binarySearch(sortedYears, SIZE, target);
        int indexPtr = binarySearchWithPointer(sortedYears, SIZE, target);

        cout << "Searching for year: " << target << "\n";
        if (index != -1) {
            cout << "  -> Found at index: " << index << " (via array indexing)\n";
            cout << "  -> Found at index: " << indexPtr << " (via pointer dereferencing)\n";
            cout << "  -> Value at pointer *(sortedYears + " << index << "): " 
                 << *(sortedYears + index) << "\n";
        } else {
            cout << "  -> Year " << target << " was NOT found in the dataset.\n";
        }
        cout << "--------------------------------------------------------\n";
    }

    return 0;
}
