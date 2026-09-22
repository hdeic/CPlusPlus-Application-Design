#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>

#include "dataset_loader.h"

using namespace std;

const int NUM_RECORDS = 10;

int binarySearch(const int arr[], int size, int target) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int binarySearchWithPointer(const int *basePtr, int size, int target) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int midVal = *(basePtr + mid);

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

    int size = loadSpotifyRecords(DATASET_PATH, titles, artists, years, streams, NUM_RECORDS);
    if (size <= 0) {
        cerr << "ERROR: could not read \"" << DATASET_PATH
             << "\". Run ./download_dataset.sh first.\n";
        return 1;
    }

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
