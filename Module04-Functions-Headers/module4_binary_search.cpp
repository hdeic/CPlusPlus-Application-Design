/*
 * Course: CIS-25 - Programming Using C++
 * Student: H Cheng
 * Module: Module 4 - Functions, Arrays, and Pointers
 * Reference: GitHub Binary Search Example (gist.github.com/christophewang/da7e308c627dcc816831)
 *
 * Description:
 * Implements an iterative binary search algorithm in C++ using functions and pointers.
 * The release years are read from the Kaggle dataset (data/spotify-2023.csv), sorted,
 * and then searched with both array indexing and pointer dereferencing.
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>

#include "dataset_loader.h"

using namespace std;

const int NUM_RECORDS = 10;

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
    string titles[NUM_RECORDS];
    string artists[NUM_RECORDS];
    int years[NUM_RECORDS];
    long long streams[NUM_RECORDS];

    // Load release years from the Kaggle dataset file
    int size = loadSpotifyRecords(DATASET_PATH, titles, artists, years, streams, NUM_RECORDS);
    if (size <= 0) {
        cerr << "ERROR: could not read \"" << DATASET_PATH
             << "\". Run ./download_dataset.sh first.\n";
        return 1;
    }

    // Binary search requires sorted input
    sort(years, years + size);

    cout << "========================================================\n";
    cout << "        Module 4 - Binary Search Demonstration          \n";
    cout << "========================================================\n";
    cout << "Release years loaded from Kaggle CSV: " << size << "\n";
    cout << "Sorted Years Array: ";
    for (int i = 0; i < size; i++) {
        cout << years[i] << " ";
    }
    cout << "\n--------------------------------------------------------\n";

    // Test cases: first and last year in the sorted data, plus one that cannot exist
    int searchTargets[] = {years[0], years[size - 1], 2025};

    for (int target : searchTargets) {
        int index = binarySearch(years, size, target);
        int indexPtr = binarySearchWithPointer(years, size, target);

        cout << "Searching for year: " << target << "\n";
        if (index != -1) {
            cout << "  -> Found at index: " << index << " (via array indexing)\n";
            cout << "  -> Found at index: " << indexPtr << " (via pointer dereferencing)\n";
            cout << "  -> Value at pointer *(years + " << index << "): "
                 << *(years + index) << "\n";
        } else {
            cout << "  -> Year " << target << " was NOT found in the dataset.\n";
        }
        cout << "--------------------------------------------------------\n";
    }

    return 0;
}
