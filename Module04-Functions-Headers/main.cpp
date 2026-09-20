/*
 * Course: CIS-25 - Programming Using C++
 * Student: H Cheng
 * Module: Module 4 - Datasets, Arrays, and Pointers
 * Dataset Source: Kaggle - Top Spotify Songs 2023 (nelgiriyewithana/top-spotify-songs-2023)
 *
 * Description:
 * This program demonstrates representing real-world tabular data from a Kaggle dataset
 * using parallel C++ arrays. It displays the records in a formatted table and demonstrates
 * accessing data elements directly and via pointers (dereferencing and pointer arithmetic).
 */

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Number of records selected from the Kaggle dataset (5 to 10 records requirement)
const int NUM_RECORDS = 8;

// Function declarations
void displayBanner();
void displayRecords(const string titles[], const string artists[], const int years[], const long long streams[], int size);
void demonstratePointerAccess(const string titles[], const string artists[], const int years[], const long long streams[], int size);

int main() {
    // Parallel arrays representing 4 fields from the Kaggle Spotify dataset
    string songTitles[NUM_RECORDS] = {
        "Blinding Lights",
        "Shape of You",
        "Someone You Loved",
        "Sunflower",
        "As It Was",
        "Starboy",
        "One Dance",
        "Stay"
    };

    string artists[NUM_RECORDS] = {
        "The Weeknd",
        "Ed Sheeran",
        "Lewis Capaldi",
        "Post Malone, Swae Lee",
        "Harry Styles",
        "The Weeknd, Daft Punk",
        "Drake",
        "The Kid LAROI, Justin Bieber"
    };

    int releaseYears[NUM_RECORDS] = {
        2019,
        2017,
        2018,
        2018,
        2022,
        2016,
        2016,
        2021
    };

    long long streams[NUM_RECORDS] = {
        3703895074LL,
        3562543890LL,
        2887241814LL,
        2808096550LL,
        2513188493LL,
        2506579610LL,
        2497746430LL,
        2372430000LL
    };

    // 1. Display banner and dataset overview
    displayBanner();

    // 2. Display all records in a formatted table
    displayRecords(songTitles, artists, releaseYears, streams, NUM_RECORDS);

    // 3. Demonstrate accessing values through pointers (assignment requirement)
    demonstratePointerAccess(songTitles, artists, releaseYears, streams, NUM_RECORDS);

    return 0;
}

void displayBanner() {
    cout << "========================================================================================\n";
    cout << "           CIS-25 C++ Application Design - Module 4 Homework Assignment                 \n";
    cout << "           Dataset: Most Streamed Spotify Songs (Source: Kaggle.com)                    \n";
    cout << "========================================================================================\n\n";
}

void displayRecords(const string titles[], const string artists[], const int years[], const long long streams[], int size) {
    cout << "----------------------------------------------------------------------------------------\n";
    cout << left 
         << setw(4)  << "#"
         << setw(24) << "Song Title"
         << setw(30) << "Artist(s)"
         << setw(8)  << "Year"
         << right << setw(18) << "Total Streams" << "\n";
    cout << "----------------------------------------------------------------------------------------\n";

    for (int i = 0; i < size; i++) {
        cout << left 
             << setw(4)  << (i + 1)
             << setw(24) << titles[i]
             << setw(30) << artists[i]
             << setw(8)  << years[i]
             << right << setw(18) << streams[i] << "\n";
    }
    cout << "----------------------------------------------------------------------------------------\n\n";
}

void demonstratePointerAccess(const string titles[], const string artists[], const int years[], const long long streams[], int size) {
    cout << "========================================================================================\n";
    cout << "                       POINTER DEMONSTRATION & ACCESS VERIFICATION                      \n";
    cout << "========================================================================================\n";

    // Pointers pointing to the first element of each array
    const string *titlePtr = &titles[0];
    const string *artistPtr = &artists[0];
    const int *yearPtr = &years[0];
    const long long *streamPtr = &streams[0];

    // [1] Accessing first record via pointer dereferencing (*ptr) - direct match with assignment starter code
    cout << "\n[1] Accessing first record via pointer dereferencing (*ptr):\n";
    cout << "    - Memory address of streams[0] (&streams[0]): " << streamPtr << "\n";
    cout << "    - Value of first song title (*titlePtr):       \"" << *titlePtr << "\"\n";
    cout << "    - Value of first artist (*artistPtr):         \"" << *artistPtr << "\"\n";
    cout << "    - Value of first release year (*yearPtr):     " << *yearPtr << "\n";
    cout << "    - Value of first stream count (*streamPtr):   " << *streamPtr << " streams\n";

    // [2] Demonstrating pointer arithmetic to access subsequent records
    cout << "\n[2] Demonstrating Pointer Arithmetic to access another record:\n";
    int targetIndex = 3; // 4th record: "Sunflower"
    const string *fourthTitlePtr = titlePtr + targetIndex;
    const string *fourthArtistPtr = artistPtr + targetIndex;
    const int *fourthYearPtr = yearPtr + targetIndex;
    const long long *fourthStreamPtr = streamPtr + targetIndex;

    cout << "    - Pointing to index " << targetIndex << " via (ptr + " << targetIndex << "):\n";
    cout << "      Song Title:   \"" << *fourthTitlePtr << "\"\n";
    cout << "      Artist(s):    \"" << *fourthArtistPtr << "\"\n";
    cout << "      Release Year: " << *fourthYearPtr << "\n";
    cout << "      Streams:      " << *fourthStreamPtr << "\n";
    cout << "      Element offset: " << (fourthStreamPtr - streamPtr) << " elements ("
         << (reinterpret_cast<uintptr_t>(fourthStreamPtr) - reinterpret_cast<uintptr_t>(streamPtr)) << " bytes)\n";

    // [3] Demonstrating traversing array via pointer increment
    cout << "\n[3] Traversing entire streams array via pointer arithmetic *(streams + i):\n";
    const long long *curr = streams;
    for (int i = 0; i < size; i++) {
        cout << "    Record " << (i + 1) << " streams via *(streams + " << i << "): " << *(curr + i) << "\n";
    }
    cout << "========================================================================================\n";
}
