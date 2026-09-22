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
- **Kaggle dataset slug:** `nelgiriyewithana/top-spotify-songs-2023`
- **File pulled from Kaggle:** `spotify-2023.csv` (953 records, 24 columns) &rarr; stored at [`data/spotify-2023.csv`](data/spotify-2023.csv)
- **Number of Records used by the program:** the first 10 records of the CSV are loaded into the arrays (within the 5-10 record requirement).
- **Fields Represented (4 fields, all read from the CSV at runtime):**
  1. `songTitles` (`std::string`): CSV column `track_name`
  2. `artists` (`std::string`): CSV column `artist(s)_name`
  3. `releaseYears` (`int`): CSV column `released_year`
  4. `streams` (`long long`): CSV column `streams`

### How the Dataset Was Pulled from Kaggle
No record is hardcoded in the C++ source. The data is pulled from Kaggle with [`download_dataset.sh`](download_dataset.sh), which uses the Kaggle API in one of two ways:

1. **Kaggle CLI** (when `kaggle` is installed and `~/.kaggle/kaggle.json` is configured):
   ```bash
   kaggle datasets download -d nelgiriyewithana/top-spotify-songs-2023 -p data --unzip --force
   ```
2. **Kaggle REST API via `curl`** (fallback when the CLI is not installed):
   ```bash
   curl -L --fail -o data/top-spotify-songs-2023.zip \
        https://www.kaggle.com/api/v1/datasets/download/nelgiriyewithana/top-spotify-songs-2023
   unzip -o data/top-spotify-songs-2023.zip -d data
   ```

Output of the pull on my machine:

```text
$ ./download_dataset.sh
[curl] Kaggle CLI not found; using the Kaggle REST API...

Downloaded files:
-rw-r--r--  1 ttp  staff  106270 Aug 26  2023 spotify-2023.csv

Record count (excluding header): 953
```

The C++ program then opens `data/spotify-2023.csv` with `std::ifstream`, parses each CSV line (including quoted fields such as `"Latto, Jung Kook"`), and fills the parallel arrays.

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

The application expands the starter code into a dataset exploration tool that is driven entirely by the Kaggle file:
1. **Dataset loading (`dataset_loader.h`):**
   - `parseCsvLine()` splits one CSV line into fields and correctly handles commas inside quoted fields and doubled quotes.
   - `loadSpotifyRecords()` opens the CSV with `std::ifstream`, skips the header row, converts `released_year` with `std::stoi` and `streams` with `std::stoll`, and fills four parallel arrays. It returns the number of records loaded (or `-1` if the file is missing) and skips malformed rows.
2. **Parallel Arrays:** 4 arrays (`songTitles`, `artists`, `releaseYears`, `streams`) sized for `NUM_RECORDS = 10` and populated at runtime.
3. **Error handling:** if `data/spotify-2023.csv` has not been downloaded yet, the program prints instructions to run `./download_dataset.sh` and exits with code 1.
4. **Tabular Formatting:** Utilizes `<iomanip>` (`setw`, `left`, `right`) to print an aligned, readable table of all loaded records.
5. **Pointer Access Demonstrations:**
   - **Pointer Initialization:** `const long long *streamPtr = &streams[0];`
   - **Dereferencing (`*streamPtr`):** Directly retrieves the first stream value, identical to the `*scorePtr` concept in the starter code.
   - **Pointer Arithmetic (`*(streamPtr + 3)`):** Advances the pointer to access the 4th record ("Cruel Summer" by Taylor Swift) without array brackets.
   - **Pointer Traversal:** Loops through the array by incrementing the pointer offset `*(streams + i)`.
   - **Pointer Walk:** Finds the most-streamed record by moving a pointer `p` from `streams` to `streams + size` and comparing `*p`.
   - **Memory Inspection:** Prints the physical memory address (e.g., `0x16d...`) alongside the dereferenced value.

---

## 6. Files in this Module

| File | Description |
|---|---|
| [`download_dataset.sh`](download_dataset.sh) | Pulls the dataset from Kaggle (Kaggle CLI or Kaggle REST API) and unpacks `data/spotify-2023.csv`. |
| [`data/spotify-2023.csv`](data/spotify-2023.csv) | The raw CSV file exactly as downloaded from Kaggle (953 records, 24 columns). |
| [`dataset_loader.h`](dataset_loader.h) | Header with the CSV parsing and array-loading functions shared by both programs. |
| [`main.cpp`](main.cpp) / [`module4_assignment.cpp`](module4_assignment.cpp) | Primary assignment program: loads the Kaggle CSV into parallel arrays, prints a formatted table, and demonstrates pointer access. |
| [`starter_code.cpp`](starter_code.cpp) / [`starter.cpp`](starter.cpp) | Base starter code from the assignment instructions. |
| [`module4_binary_search.cpp`](module4_binary_search.cpp) | Bonus binary search over the release years read from the Kaggle CSV, based on the assigned Christopher Wang gist and video. |

---

## 7. How to Compile and Run

All commands are run from inside the `Module04-Functions-Headers` folder.

### Step 1 - Pull the dataset from Kaggle
```bash
./download_dataset.sh
```

### Step 2 - Main Assignment (`main.cpp` / `module4_assignment.cpp`)
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

### `./main`
```text
==========================================================================================
           CIS-25 C++ Application Design - Module 4 Homework Assignment                   
           Dataset: Top Spotify Songs 2023 (Source: Kaggle.com)                           
==========================================================================================
Data file: data/spotify-2023.csv
Records loaded into arrays: 10

------------------------------------------------------------------------------------------
#   Song Title                            Artist(s)                   Year         Streams
------------------------------------------------------------------------------------------
1   Seven (feat. Latto) (Explicit Ver.)   Latto, Jung Kook            2023       141381703
2   LALA                                  Myke Towers                 2023       133716286
3   vampire                               Olivia Rodrigo              2023       140003974
4   Cruel Summer                          Taylor Swift                2019       800840817
5   WHERE SHE GOES                        Bad Bunny                   2023       303236322
6   Sprinter                              Dave, Central Cee           2023       183706234
7   Ella Baila Sola                       Eslabon Armado, Peso Pluma  2023       725980112
8   Columbia                              Quevedo                     2023        58149378
9   fukumean                              Gunna                       2023        95217315
10  La Bebe - Remix                       Peso Pluma, Yng Lvcas       2023       553634067
------------------------------------------------------------------------------------------

==========================================================================================
                       POINTER DEMONSTRATION & ACCESS VERIFICATION                        
==========================================================================================

[1] Accessing first record via pointer dereferencing (*ptr):
    - Memory address of streams[0] (&streams[0]): 0x16d9fa730
    - Value of first song title (*titlePtr):       "Seven (feat. Latto) (Explicit Ver.)"
    - Value of first artist (*artistPtr):         "Latto, Jung Kook"
    - Value of first release year (*yearPtr):     2023
    - Value of first stream count (*streamPtr):   141381703 streams

[2] Demonstrating Pointer Arithmetic to access another record:
    - Pointing to index 3 via (ptr + 3):
      Song Title:   "Cruel Summer"
      Artist(s):    "Taylor Swift"
      Release Year: 2019
      Streams:      800840817
      Element offset: 3 elements (24 bytes)

[3] Traversing entire streams array via pointer arithmetic *(streams + i):
    Record  1 streams via *(streams + 0): 141381703
    Record  2 streams via *(streams + 1): 133716286
    Record  3 streams via *(streams + 2): 140003974
    Record  4 streams via *(streams + 3): 800840817
    Record  5 streams via *(streams + 4): 303236322
    Record  6 streams via *(streams + 5): 183706234
    Record  7 streams via *(streams + 6): 725980112
    Record  8 streams via *(streams + 7): 58149378
    Record  9 streams via *(streams + 8): 95217315
    Record 10 streams via *(streams + 9): 553634067

[4] Finding the most-streamed record by walking a pointer across the array:
    Highest stream count 800840817 found at index 3 -> "Cruel Summer" by Taylor Swift
==========================================================================================
```

### `./binary_search`
```text
========================================================
        Module 4 - Binary Search Demonstration          
========================================================
Release years loaded from Kaggle CSV: 10
Sorted Years Array: 2019 2023 2023 2023 2023 2023 2023 2023 2023 2023 
--------------------------------------------------------
Searching for year: 2019
  -> Found at index: 0 (via array indexing)
  -> Found at index: 0 (via pointer dereferencing)
  -> Value at pointer *(years + 0): 2019
--------------------------------------------------------
Searching for year: 2023
  -> Found at index: 4 (via array indexing)
  -> Found at index: 4 (via pointer dereferencing)
  -> Value at pointer *(years + 4): 2023
--------------------------------------------------------
Searching for year: 2025
  -> Year 2025 was NOT found in the dataset.
--------------------------------------------------------
```

### `./main` before the dataset is downloaded
```text
ERROR: could not open "data/spotify-2023.csv".
Run ./download_dataset.sh first to pull the dataset from Kaggle,
then run this program from the Module04-Functions-Headers folder.
```

---

## 9. Canvas Submission Information

- **GitHub Repository:** [https://github.com/hdeic/CPlusPlus-Application-Design](https://github.com/hdeic/CPlusPlus-Application-Design)
- **Module 4 Folder URL:** [https://github.com/hdeic/CPlusPlus-Application-Design/tree/main/Module04-Functions-Headers](https://github.com/hdeic/CPlusPlus-Application-Design/tree/main/Module04-Functions-Headers)
