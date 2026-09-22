/*
 * Course: CIS-25 - Programming Using C++
 * Student: H Cheng
 * Module: Module 4 - Datasets, Arrays, and Pointers
 * Dataset Source: Kaggle - Top Spotify Songs 2023 (nelgiriyewithana/top-spotify-songs-2023)
 *
 * Description:
 * This program reads records from the Kaggle dataset file data/spotify-2023.csv
 * (pulled with ./download_dataset.sh) into parallel C++ arrays. Nothing is hardcoded:
 * the song titles, artists, release years and stream counts all come from the CSV.
 * It then displays the records in a formatted table and demonstrates accessing data
 * elements through pointers (dereferencing and pointer arithmetic).
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdint>

#include "dataset_loader.h"   // parseCsvLine(), loadSpotifyRecords(), DATASET_PATH

using namespace std;

// Number of records to load from the Kaggle dataset (assignment asks for 5 to 10)
const int NUM_RECORDS = 10;

// Function declarations
void displayBanner(const string &path, int loaded);
void displayRecords(const string titles[], const string artists[], const int years[], const long long streams[], int size);
void demonstratePointerAccess(const string titles[], const string artists[], const int years[], const long long streams[], int size);

int main() {
    // Parallel arrays: 4 fields per record, filled from the Kaggle CSV at runtime
    string songTitles[NUM_RECORDS];
    string artists[NUM_RECORDS];
    int releaseYears[NUM_RECORDS];
    long long streams[NUM_RECORDS];

    // 1. Pull the records out of the Kaggle dataset file
    int loaded = loadSpotifyRecords(DATASET_PATH, songTitles, artists, releaseYears, streams, NUM_RECORDS);
    if (loaded < 0) {
        cerr << "ERROR: could not open \"" << DATASET_PATH << "\".\n"
             << "Run ./download_dataset.sh first to pull the dataset from Kaggle,\n"
             << "then run this program from the Module04-Functions-Headers folder.\n";
        return 1;
    }
    if (loaded == 0) {
        cerr << "ERROR: no records were read from \"" << DATASET_PATH << "\".\n";
        return 1;
    }

    // 2. Display banner and dataset overview
    displayBanner(DATASET_PATH, loaded);

    // 3. Display all loaded records in a formatted table
    displayRecords(songTitles, artists, releaseYears, streams, loaded);

    // 4. Demonstrate accessing values through pointers (assignment requirement)
    demonstratePointerAccess(songTitles, artists, releaseYears, streams, loaded);

    return 0;
}

void displayBanner(const string &path, int loaded) {
    cout << "==========================================================================================\n";
    cout << "           CIS-25 C++ Application Design - Module 4 Homework Assignment                   \n";
    cout << "           Dataset: Top Spotify Songs 2023 (Source: Kaggle.com)                           \n";
    cout << "==========================================================================================\n";
    cout << "Data file: " << path << "\n";
    cout << "Records loaded into arrays: " << loaded << "\n\n";
}

void displayRecords(const string titles[], const string artists[], const int years[], const long long streams[], int size) {
    cout << "------------------------------------------------------------------------------------------\n";
    cout << left
         << setw(4)  << "#"
         << setw(38) << "Song Title"
         << setw(28) << "Artist(s)"
         << setw(6)  << "Year"
         << right << setw(14) << "Streams" << "\n";
    cout << "------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < size; i++) {
        cout << left
             << setw(4)  << (i + 1)
             << setw(38) << titles[i]
             << setw(28) << artists[i]
             << setw(6)  << years[i]
             << right << setw(14) << streams[i] << "\n";
    }
    cout << "------------------------------------------------------------------------------------------\n\n";
}

void demonstratePointerAccess(const string titles[], const string artists[], const int years[], const long long streams[], int size) {
    cout << "==========================================================================================\n";
    cout << "                       POINTER DEMONSTRATION & ACCESS VERIFICATION                        \n";
    cout << "==========================================================================================\n";

    // Pointers pointing to the first element of each array
    const string *titlePtr = &titles[0];
    const string *artistPtr = &artists[0];
    const int *yearPtr = &years[0];
    const long long *streamPtr = &streams[0];

    // [1] Accessing first record via pointer dereferencing (*ptr) - same idea as *scorePtr in the starter code
    cout << "\n[1] Accessing first record via pointer dereferencing (*ptr):\n";
    cout << "    - Memory address of streams[0] (&streams[0]): " << streamPtr << "\n";
    cout << "    - Value of first song title (*titlePtr):       \"" << *titlePtr << "\"\n";
    cout << "    - Value of first artist (*artistPtr):         \"" << *artistPtr << "\"\n";
    cout << "    - Value of first release year (*yearPtr):     " << *yearPtr << "\n";
    cout << "    - Value of first stream count (*streamPtr):   " << *streamPtr << " streams\n";

    // [2] Demonstrating pointer arithmetic to access another record
    cout << "\n[2] Demonstrating Pointer Arithmetic to access another record:\n";
    int targetIndex = (size > 3) ? 3 : size - 1;   // 4th record when available
    const string *targetTitlePtr = titlePtr + targetIndex;
    const string *targetArtistPtr = artistPtr + targetIndex;
    const int *targetYearPtr = yearPtr + targetIndex;
    const long long *targetStreamPtr = streamPtr + targetIndex;

    cout << "    - Pointing to index " << targetIndex << " via (ptr + " << targetIndex << "):\n";
    cout << "      Song Title:   \"" << *targetTitlePtr << "\"\n";
    cout << "      Artist(s):    \"" << *targetArtistPtr << "\"\n";
    cout << "      Release Year: " << *targetYearPtr << "\n";
    cout << "      Streams:      " << *targetStreamPtr << "\n";
    cout << "      Element offset: " << (targetStreamPtr - streamPtr) << " elements ("
         << (reinterpret_cast<uintptr_t>(targetStreamPtr) - reinterpret_cast<uintptr_t>(streamPtr)) << " bytes)\n";

    // [3] Traversing the streams array via pointer offset
    cout << "\n[3] Traversing entire streams array via pointer arithmetic *(streams + i):\n";
    const long long *curr = streams;
    for (int i = 0; i < size; i++) {
        cout << "    Record " << setw(2) << (i + 1) << " streams via *(streams + " << i << "): " << *(curr + i) << "\n";
    }

    // [4] Using a pointer to find the most-streamed record in the loaded data
    cout << "\n[4] Finding the most-streamed record by walking a pointer across the array:\n";
    const long long *maxPtr = streams;
    for (const long long *p = streams; p < streams + size; p++) {
        if (*p > *maxPtr) {
            maxPtr = p;
        }
    }
    int maxIndex = static_cast<int>(maxPtr - streams);
    cout << "    Highest stream count " << *maxPtr << " found at index " << maxIndex
         << " -> \"" << *(titlePtr + maxIndex) << "\" by " << *(artistPtr + maxIndex) << "\n";
    cout << "==========================================================================================\n";
}
