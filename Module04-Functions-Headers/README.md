# Module 04: Functions, Datasets, Arrays, and Pointers

**Course:** CIS-25 - Programming Using C++ (L1-41736)  
**Student:** H Cheng  
**Repository:** [hdeic/CPlusPlus-Application-Design](https://github.com/hdeic/CPlusPlus-Application-Design)

---

## 1. Study Resources & Review

### Videos Watched
1. **Binary Search:** [YouTube Link](https://youtu.be/vohuRrwbTT4?si=vBU7PLBoNa_6cU_J) - Divide-and-conquer search technique on sorted arrays in $O(\log n)$ time.
2. **Arrays:** [YouTube Link](https://youtu.be/ZLk7qV9wEDw?si=9upMBUMJWRNYChkK) - Contiguous memory allocation, indexing, and parallel arrays in C++.
3. **Pointers:** [YouTube Link](https://youtu.be/eNofmKYzje4?si=u1jBz36PKC2dXHHB) - Memory addresses (`&`), pointer declarations (`*`), dereferencing (`*ptr`), and pointer arithmetic.

### Articles & Code Reviewed
- **fStream Examples:** [W3Schools C++ fstream](https://www.w3schools.com/cpp/ref_fstream_fstream.asp) - File input/output streams (`ifstream`, `ofstream`) in C++.
- **Binary Search Implementation:** [GitHub Gist by Christopher Wang](https://gist.github.com/christophewang/da7e308c627dcc816831) - Clean iterative binary search in C++.

---

## 2. Homework Assignment Specifications

> **Prompt:**  
> Choose a small Kaggle dataset. Select 5–10 records and at least 2–3 fields. Represent the data in C++ arrays. Display the records and demonstrate accessing one value through a pointer.

### Selected Kaggle Dataset
- **Dataset:** [Top Spotify Songs 2023](https://www.kaggle.com/datasets/nelgiriyewithana/top-spotify-songs-2023) by Nidula Elgiriyewithana on Kaggle.com
- **Selection:** 8 records (exceeds the 5–10 requirement)
- **Fields Represented (4 fields):**
  1. `songTitles` (`std::string`): Track name
  2. `artists` (`std::string`): Artist(s) name
  3. `releaseYears` (`int`): Year of commercial release
  4. `streams` (`long long`): Total Spotify stream count

---

## 3. Files in this Module

| File | Description |
|---|---|
| `starter.cpp` | Base starter code provided in the assignment instructions. |
| `module4_assignment.cpp` | Main customized assignment program with the Kaggle dataset, formatted tabular display, and pointer access demonstration. |
| `module4_binary_search.cpp` | Additional demonstration applying iterative binary search to sorted dataset arrays using pointers and functions. |
| `spotify_top_songs_sample.csv` | Raw 8-record sample from the Kaggle dataset. |

---

## 4. Starter Code

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

## 5. How to Compile and Run

### Compiling and Running the Main Assignment (`module4_assignment.cpp`)
```bash
g++ -Wall -Wextra -std=c++17 module4_assignment.cpp -o module4_assignment
./module4_assignment
```

### Compiling and Running Starter Code (`starter.cpp`)
```bash
g++ -std=c++17 starter.cpp -o starter
./starter
```

### Compiling and Running Binary Search Demo (`module4_binary_search.cpp`)
```bash
g++ -std=c++17 module4_binary_search.cpp -o module4_binary_search
./module4_binary_search
```

---

## 6. Program Execution Output

### `module4_assignment` Output:
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

## 7. Key Pointer Concepts Demonstrated
1. **Address-of Operator (`&`):** Used to obtain the memory address where an array element is stored (e.g. `&streams[0]`).
2. **Pointer Variable Declaration (`*`):** Declares a pointer of matching type (e.g. `const long long *streamPtr`).
3. **Dereference Operator (`*`):** Retrieves the value stored at the memory location pointed to by the pointer (e.g. `*streamPtr`).
4. **Pointer Arithmetic (`ptr + offset`):** Advances the memory pointer by $k \times \text{sizeof(type)}$ bytes to read subsequent elements (e.g. `*(streamPtr + 3)`).
