# Module 05 - Records, Headers & Functions

**Course:** CIS-25 - Programming Using C++ (L1-41736)  
**Student:** H Cheng  
**Repository:** [hdeic/CPlusPlus-Application-Design](https://github.com/hdeic/CPlusPlus-Application-Design)  
**Module 5 URL:** [Module05-Classes-Objects](https://github.com/hdeic/CPlusPlus-Application-Design/tree/main/Module05-Classes-Objects)

---

## 1. Overview & What I Learned

In [Module 04 - Datasets, Arrays & Pointers](../Module04-Functions-Headers/README.md), I learned how to represent data in arrays and directly navigate memory using pointers. In **Module 05**, I advanced to professional **modular application architecture** by separating code into functions, header files (`.h`), and implementation files (`.cpp`), and by importing records from a `.csv` file with the **`fstream`** class instead of hardcoding them.

Key architectural takeaways:
- **`main()` Function:** The official entry point of any C++ program. Keeping `main()` clean and focused on high-level orchestration is an industry standard.
- **Functions:** Modular, single-responsibility blocks of code that accept parameters, execute operations, and optionally return results.
- **Function Declarations (Prototypes) vs Definitions:** Moving declarations into header files (`.h`) allows different translation units to know a function's signature before linking.
- **Header Guards:** Using `#ifndef`, `#define`, and `#endif` guarantees that declarations are never included more than once in a single compilation unit, preventing duplicate definition errors.
- **Multi-File Compilation:** Compiling multiple `.cpp` files into independent object files and linking them into a single binary (`clang++ main.cpp RecordTools.cpp -o main`).
- **File I/O with `fstream`:** Opening a `.csv` file, checking `is_open()`, measuring the file with `seekg()` / `tellg()`, reading rows with `getline()`, and releasing the handle with `close()`.

---

## 2. Study Resources & Review

### Videos Watched
1. **What is the main in C++?:** [https://youtu.be/5TufmSZW3-k?si=i9zC1AQ2Ut5m1RFz](https://youtu.be/5TufmSZW3-k?si=i9zC1AQ2Ut5m1RFz)  
   *Takeaway:* Examines the execution lifecycle starting at `main()`, exit codes (`return 0;`), and how the runtime system interacts with the OS.
2. **Functions:** [https://youtu.be/BGmDRQzY4CA?si=imy3bP7zocwt4WIo](https://youtu.be/BGmDRQzY4CA?si=imy3bP7zocwt4WIo)  
   *Takeaway:* Explains function declarations, definitions, return types, pass-by-value vs pass-by-reference (`&`), and scope.
3. **Header Files:** [https://youtu.be/qaGzc56Rekg?si=QVZpMNxuiAfa_fdy](https://youtu.be/qaGzc56Rekg?si=QVZpMNxuiAfa_fdy)  
   *Takeaway:* Covers why large C++ projects separate header interfaces (`.h`) from implementations (`.cpp`), and how the preprocessor `#include` directive works.

### Reference Reviewed
- **C++ fstream Class:** [https://www.w3schools.com/cpp/ref_fstream_fstream.asp](https://www.w3schools.com/cpp/ref_fstream_fstream.asp)  
  *Takeaway:* The `fstream` class from the `<fstream>` header reads and writes files through one shared file pointer. This module uses its file handling functions (`is_open()`, `close()`), its file pointer functions (`seekg()`, `tellg()`), and the `getline(stream, destination)` reading function.

### GitHub Code Search & Real-World Application Review
- **Search Queries Explored:** `c++ eCommerce application`, `c++ banking application`, `c++ inventory record management system`.
- **Architectural Insights Gained:**
  - Production C++ systems encapsulate record structures (such as `ProductRecord` or `AccountRecord`) in dedicated header files.
  - CRUD operations (such as `addRecord`, `displayRecords`, `calculateTotal`) are organized in utility modules rather than lumped inside `main.cpp`.
  - Pass-by-reference (`&`) is used for arrays and structures to avoid unnecessary copying of large objects, while `const` references preserve data safety.

---

## 3. Homework Assignment Instructions

> **Assignment:**  
> Create functions to add a record, display records, and calculate a simple result. Move at least one function declaration into your own `.h` header file and implement it in a `.cpp` file.

### Our Customized Application
- **Domain:** eCommerce Product & Inventory Management System.
- **Record Data File:** [`data/online-retail-10.csv`](data/online-retail-10.csv) holds a header row plus 10 online retail transaction records, and is imported at runtime with `fstream` rather than hardcoded into the program. The sample rows come from the public UCI Online Retail transaction data.
- **Record Structure (`ProductRecord`) - one field per `.csv` column:**

| Field | CSV Column | Description |
|---|---|---|
| `std::string invoiceNo` | `InvoiceNo` | Transaction invoice number |
| `std::string stockCode` | `StockCode` | Unique product/stock identifier |
| `std::string description` | `Description` | Product title |
| `int quantity` | `Quantity` | Units sold on that line |
| `std::string invoiceDate` | `InvoiceDate` | Timestamp of the transaction |
| `double unitPrice` | `UnitPrice` | Price per unit |
| `std::string customerId` | `CustomerID` | Purchasing customer identifier |
| `std::string country` | `Country` | Customer country |

- **Functions Implemented Across Files:**
  1. `showMessage()`: System readiness banner (starter code).
  2. `reportFileSize(...)`: Opens the data file with `fstream`, then measures it with `seekg(0, fstream::end)` and `tellg()`.
  3. `loadRecordsFromFile(...)`: Imports the `.csv` with `fstream` and `getline()`, parses each row, and feeds it to `addRecord`.
  4. `addRecord(...)`: Inserts a new product record into the inventory array with capacity checking.
  5. `displayRecords(...)`: Renders an aligned tabular view of all catalog items with individual line totals.
  6. `calculateTotalValue(...)`: Calculates total inventory valuation (sum of price x quantity).
  7. `calculateAveragePrice(...)`: Computes the average unit price per product item.

---

## 4. Starter Code

The assignment instructions provided the following starter code as a foundation:

```cpp
// RecordTools.h
#ifndef RECORDTOOLS_H
#define RECORDTOOLS_H

void showMessage();

#endif

// RecordTools.cpp
#include <iostream>
#include "RecordTools.h"
using namespace std;

void showMessage() {
    cout << "Record system ready!" << endl;
}
```

`showMessage()` is kept as the declaration that lives in my own header file, and it is still verified directly by [`starter.cpp`](starter.cpp) and [`starter_code.cpp`](starter_code.cpp).

---

## 5. How the `fstream` Import Works

`RecordTools.cpp` opens the record data file through the `fstream` class:

```cpp
fstream dataFile(path, fstream::in);
if (!dataFile.is_open()) {
    return -1;
}

string line;
getline(dataFile, line);

while (currentCount < maxCapacity && getline(dataFile, line)) {
    vector<string> fields = splitCsvLine(line);
    addRecord(records, currentCount, maxCapacity,
              fields[0], fields[1], fields[2],
              stoi(fields[3]), fields[4], stod(fields[5]),
              fields[6], fields[7]);
}

dataFile.close();
```

| `fstream` Member Used | Purpose In This Program |
|---|---|
| `fstream(path, fstream::in)` | Opens `data/online-retail-10.csv` for reading. |
| `is_open()` | Confirms the file opened before any parsing is attempted. |
| `seekg(0, fstream::end)` / `seekg(0, fstream::beg)` | Moves the file pointer to measure the file and rewind it. |
| `tellg()` | Reports the byte size of the data file. |
| `getline(stream, destination)` | Reads the header row, then each record row, discarding the line break. |
| `close()` | Releases the file handle when reading is finished. |

---

## 6. Files in this Module

| File | Description |
|---|---|
| [`RecordTools.h`](RecordTools.h) | Custom header file declaring the `ProductRecord` struct and function prototypes with header guards. |
| [`RecordTools.cpp`](RecordTools.cpp) | Implementation file defining `showMessage`, `reportFileSize`, `loadRecordsFromFile`, `addRecord`, `displayRecords`, `calculateTotalValue`, and `calculateAveragePrice`. |
| [`main.cpp`](main.cpp) | Driver program containing `main()`, importing the records, displaying formatted tables, and presenting calculated metrics. |
| [`data/online-retail-10.csv`](data/online-retail-10.csv) | The 10 product records imported at runtime by `fstream`. |
| [`starter.cpp`](starter.cpp) / [`starter_code.cpp`](starter_code.cpp) | Direct verification of the original starter code interface. |

---

## 7. How to Compile and Run

### Compiling the Multi-File Project (`main.cpp` + `RecordTools.cpp`)
```bash
clang++ -Wall -Wextra -std=c++17 main.cpp RecordTools.cpp -o main
./main
```
*(Or with `g++`: `g++ -Wall -Wextra -std=c++17 main.cpp RecordTools.cpp -o main && ./main`)*

> Run `./main` from inside the `Module05-Classes-Objects` folder so the relative path `data/online-retail-10.csv` resolves correctly.

### Compiling Starter Code
```bash
clang++ -std=c++17 starter.cpp RecordTools.cpp -o starter
./starter
```

---

## 8. Verified Console Output

```text
==========================================================================================================
                        Record Management System Ready! (Module 5)                                         
==========================================================================================================

[Source] Record data file: data/online-retail-10.csv
[Source] Size measured with fstream seekg/tellg: 942 bytes

[Action] Importing product records with the fstream class...
[Status] Successfully imported 10 product records.

[Display] Current Product Inventory Records:
----------------------------------------------------------------------------------------------------------
INVOICE   STOCK     DESCRIPTION                              QTY   UNIT ($)      LINE ($)  COUNTRY         
----------------------------------------------------------------------------------------------------------
536365    85123A    WHITE HANGING HEART T-LIGHT HOLDER         6       2.55         15.30  United Kingdom  
536365    71053     WHITE METAL LANTERN                        6       3.39         20.34  United Kingdom  
536365    84406B    CREAM CUPID HEARTS COAT HANGER             8       2.75         22.00  United Kingdom  
536365    84029G    KNITTED UNION FLAG HOT WATER BOTTLE        6       3.39         20.34  United Kingdom  
536365    84029E    RED WOOLLY HOTTIE WHITE HEART.             6       3.39         20.34  United Kingdom  
536365    22752     SET 7 BABUSHKA NESTING BOXES               2       7.65         15.30  United Kingdom  
536365    21730     GLASS STAR FROSTED T-LIGHT HOLDER          6       4.25         25.50  United Kingdom  
536366    22633     HAND WARMER UNION JACK                     6       1.85         11.10  United Kingdom  
536366    22632     HAND WARMER RED POLKA DOT                  6       1.85         11.10  United Kingdom  
536367    84879     ASSORTED COLOUR BIRD ORNAMENT             32       1.69         54.08  United Kingdom  
----------------------------------------------------------------------------------------------------------

====================================================================================
                             INVENTORY METRICS SUMMARY                              
====================================================================================
  - Total Catalog Items:        10 products
  - Average Unit Price:         $      3.28
  - Total Inventory Valuation:  $    215.40
====================================================================================
```

---

## 9. Key Concepts & Architecture Summary

```
              +--------------------------------+
              | data/online-retail-10.csv      |
              | (10 product records)           |
              +---------------+----------------+
                              | fstream (read)
                              v
                      +-------------------+
                      |   RecordTools.h   |
                      | (Interface/Types) |
                      +---------+---------+
                                |
               +----------------+----------------+
               |                                 |
        #include "RecordTools.h"          #include "RecordTools.h"
               |                                 |
               v                                 v
      +-------------------+             +-------------------+
      |  RecordTools.cpp  |             |     main.cpp      |
      | (Implementations) |             | (Application Core)|
      +---------+---------+             +---------+---------+
                |                                 |
                +----------------+----------------+
                                 | (clang++ link)
                                 v
                        +-----------------+
                        |   Executable    |
                        |     (main)      |
                        +-----------------+
```

1. **Header Guards (`#ifndef RECORDTOOLS_H ... #endif`):** Ensures `RecordTools.h` is evaluated only once by the preprocessor even if included across multiple translation units.
2. **Modular Functions:** By separating interface from implementation, functions can be developed and maintained independently without recompiling unneeded parts.
3. **Pass-by-Reference for Record Updates:** `addRecord` takes `int &currentCount` by reference so changes directly update the caller's inventory counter.
4. **File-Driven Records:** Every record shown by the program is read at runtime from the `.csv` through the `fstream` class, so the data can change without recompiling.

---

## 10. Canvas Submission Information

- **GitHub Repository:** [https://github.com/hdeic/CPlusPlus-Application-Design](https://github.com/hdeic/CPlusPlus-Application-Design)
- **Module 5 Folder URL:** [https://github.com/hdeic/CPlusPlus-Application-Design/tree/main/Module05-Classes-Objects](https://github.com/hdeic/CPlusPlus-Application-Design/tree/main/Module05-Classes-Objects)
