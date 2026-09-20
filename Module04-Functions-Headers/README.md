# Module 04 - Datasets, Arrays & Pointers

**Course:** CIS-25 - Programming Using C++ (L1-41736)  
**Student:** H Cheng  
**Repository:** [hdeic/CPlusPlus-Application-Design](https://github.com/hdeic/CPlusPlus-Application-Design)  
**Module 4 URL:** [Module04-Functions-Headers](https://github.com/hdeic/CPlusPlus-Application-Design/tree/main/Module04-Functions-Headers)

---

## 1. Overview & What I Learned

In [Module 01 - Setup](../Module01-Setup/README.md), I established foundational Git and development environment workflows. In [Module 02 - Variables & Menus](../Module02-Variables/README.md), I implemented interactive menu-driven control flow. In [Module 03 - Variables & Data Types](../Module03-Datasets-Arrays-Pointers/README.md), I practiced fundamental data types and personalizing console output.

In **Module 04**, I advanced to working with structured collections of data using **arrays** and directly managing memory addresses using **pointers**:
- An **array** stores multiple elements of the same data type in a contiguous block of memory.
- A **pointer** is a variable whose value is the memory address of another variable.
- The **address-of operator (`&`)** fetches the location in memory where data resides.
- The **dereference operator (`*`)** accesses or modifies the value stored at that specific address.
- **Pointer arithmetic** enables efficient sequential memory navigation across arrays.

---

## 2. Study Resources & Review

### Videos Watched
1. **Binary Search:** [https://youtu.be/vohuRrwbTT4?si=vBU7PLBoNa_6cU_J](https://youtu.be/vohuRrwbTT4?si=vBU7PLBoNa_6cU_J)  
   *Takeaway:* Explains the divide-and-conquer strategy on sorted arrays, reducing search complexity from $O(n)$ to $O(\log n)$.
2. **Arrays:** [https://youtu.be/ZLk7qV9wEDw?si=9upMBUMJWRNYChkK](https://youtu.be/ZLk7qV9wEDw?si=9upMBUMJWRNYChkK)  
   *Takeaway:* Covers zero-indexed contiguous memory allocation and using parallel arrays to represent records with multiple attributes.
3. **Pointers:** [https://youtu.be/eNofmKYzje4?si=u1jBz36PKC2dXHHB](https://youtu.be/eNofmKYzje4?si=u1jBz36PKC2dXHHB)  
   *Takeaway:* Demystifies how memory addresses work, how pointer variables store memory addresses, and how dereferencing accesses the underlying data.

### Read Articles & Code Reviewed
- **fStream Examples:** [W3Schools C++ fStream Reference](https://www.w3schools.com/cpp/ref_fstream_fstream.asp)  
   *Takeaway:* Illustrates file streams (`ifstream`, `ofstream`) for reading and writing persistent dataset files on disk.
- **GitHub Binary Search Example:** [Christopher Wang Gist da7e308c627dcc816831](https://gist.github.com/christophewang/da7e308c627dcc816831)  
   *Takeaway:* A clean, production-style iterative binary search implementation in C++.

---

## 3. Homework Assignment Instructions

> **Assignment:**  
> Choose a small Kaggle dataset. Select 5–10 records and at least 2–3 fields. Represent the data in C++ arrays. Display the records and demonstrate accessing one value through a pointer.

### Selected Kaggle Dataset
- **Dataset Title:** [Top Spotify Songs 2023](https://www.kaggle.com/datasets/nelgiriyewithana/top-spotify-songs-2023) by Nidula Elgiriyewithana on Kaggle.com.
- **Number of Records:** 8 records selected (exceeds the 5–10 record requirement).
- **Fields Represented (4 fields):**
  1. `songTitles` (`std::string`): Track name
  2. `artists` (`std::string`): Performing artist(s)
  3. `releaseYears` (`int`): Year of commercial release
  4. `streams` (`long long`): Total Spotify streams

---

## 4. Starter Code

The assignment instructions provided the following starter code as a foundation:

```cpp
#include <iostream>
using namespace std;

int main() {
    string names[3] = {"Ada", "Sam", "Jordan"};
    int scores[3] = {91, 84, 97};

    int *scorePtr = &scores[0];

    for (int i = 0; i < 3; i++) {
        cout << names[i] << ": " << scores[i] << endl;
    }

    cout << "First score through pointer: " << *scorePtr << endl;
    return 0;
}
```

---

## 5. Implementation Details

Our application expands the starter code into a complete dataset exploration tool:
1. **Parallel Arrays:** 4 arrays store 8 records of Spotify music data.
2. **Tabular Formatting:** Utilizes `<iomanip>` (`setw`, `left`, `right`) to print an aligned, readable table of all records.
3. **Pointer Access Demonstrations:**
   - **Pointer Initialization:** `const long long *streamPtr = &streams[0];`
   - **Dereferencing (`*streamPtr`):** Directly retrieves the first stream value (`3703895074`), identical to the `*scorePtr` concept in the starter code.
   - **Pointer Arithmetic (`*(streamPtr + 3)`):** Demonstrates advancing the pointer to access the 4th record ("Sunflower" by Post Malone & Swae Lee) without array brackets.
   - **Pointer Traversal:** Loops through the array by incrementing the pointer offset `*(streams + i)`.
   - **Memory Inspection:** Prints the physical memory address (e.g., `0x16f...`) alongside the dereferenced value.

---

## 6. Files in this Module

| File | Description |
|---|---|
| [`main.cpp`](main.cpp) / [`module4_assignment.cpp`](module4_assignment.cpp) | Primary assignment program featuring the Kaggle dataset, formatted tabular display, and comprehensive pointer access demonstrations. |
| [`starter_code.cpp`](starter_code.cpp) / [`starter.cpp`](starter.cpp) | Base starter code from the assignment instructions. |
| [`module4_binary_search.cpp`](module4_binary_search.cpp) | Bonus binary search implementation demonstrating array searching and pointer dereferencing based on the assigned Christopher Wang gist and video. |
| [`spotify_top_songs_sample.csv`](spotify_top_songs_sample.csv) | Raw CSV data extract from the Kaggle dataset. |

---

## 7. How to Compile and Run

### Main Assignment (`main.cpp` / `module4_assignment.cpp`)
```bash
clang++ -Wall -Wextra -std=c++17 main.cpp -o main
./main
```

### Starter Code (`starter.cpp`)
```bash
clang++ -Wall -Wextra -std=c++17 starter.cpp -o starter
./starter
```

### Binary Search Demonstration (`module4_binary_search.cpp`)
```bash
clang++ -Wall -Wextra -std=c++17 module4_binary_search.cpp -o binary_search
./binary_search
```

---

## 8. Verified Console Output

```text
========================================================================================
           CIS-25 C++ Application Design - Module 4 Homework Assignment                 
           Dataset: Most Streamed Spotify Songs (Source: Kaggle.com)                    
========================================================================================

----------------------------------------------------------------------------------------
#   Song Title              Artist(s)                     Year         Total Streams
----------------------------------------------------------------------------------------
1   Blinding Lights         The Weeknd                    2019            3703895074
2   Shape of You            Ed Sheeran                    2017            3562543890
3   Someone You Loved       Lewis Capaldi                 2018            2887241814
4   Sunflower               Post Malone, Swae Lee         2018            2808096550
5   As It Was               Harry Styles                  2022            2513188493
6   Starboy                 The Weeknd, Daft Punk         2016            2506579610
7   One Dance               Drake                         2016            2497746430
8   Stay                    The Kid LAROI, Justin Bieber  2021            2372430000
----------------------------------------------------------------------------------------

========================================================================================
                       POINTER DEMONSTRATION & ACCESS VERIFICATION                      
========================================================================================

[1] Accessing first record via pointer dereferencing (*ptr):
    - Memory address of streams[0] (&streams[0]): 0x16f88a700
    - Value of first song title (*titlePtr):       "Blinding Lights"
    - Value of first artist (*artistPtr):         "The Weeknd"
    - Value of first release year (*yearPtr):     2019
    - Value of first stream count (*streamPtr):   3703895074 streams

[2] Demonstrating Pointer Arithmetic to access another record:
    - Pointing to index 3 via (ptr + 3):
      Song Title:   "Sunflower"
      Artist(s):    "Post Malone, Swae Lee"
      Release Year: 2018
      Streams:      2808096550
      Element offset: 3 elements (24 bytes)

[3] Traversing entire streams array via pointer arithmetic *(streams + i):
    Record 1 streams via *(streams + 0): 3703895074
    Record 2 streams via *(streams + 1): 3562543890
    Record 3 streams via *(streams + 2): 2887241814
    Record 4 streams via *(streams + 3): 2808096550
    Record 5 streams via *(streams + 4): 2513188493
    Record 6 streams via *(streams + 5): 2506579610
    Record 7 streams via *(streams + 6): 2497746430
    Record 8 streams via *(streams + 7): 2372430000
========================================================================================
```

---

## 9. Canvas Submission Information

- **GitHub Repository:** [https://github.com/hdeic/CPlusPlus-Application-Design](https://github.com/hdeic/CPlusPlus-Application-Design)
- **Module 4 Folder URL:** [https://github.com/hdeic/CPlusPlus-Application-Design/tree/main/Module04-Functions-Headers](https://github.com/hdeic/CPlusPlus-Application-Design/tree/main/Module04-Functions-Headers)
