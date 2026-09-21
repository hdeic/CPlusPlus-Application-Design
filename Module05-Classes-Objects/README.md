# Module 05 - Records, Headers & Functions

**Course:** CIS-25 - Programming Using C++ (L1-41736)  
**Student:** H Cheng  
**Repository:** [hdeic/CPlusPlus-Application-Design](https://github.com/hdeic/CPlusPlus-Application-Design)  
**Module 5 URL:** [Module05-Classes-Objects](https://github.com/hdeic/CPlusPlus-Application-Design/tree/main/Module05-Classes-Objects)

---

## 1. Overview & What I Learned

In [Module 04 - Datasets, Arrays & Pointers](../Module04-Functions-Headers/README.md), I learned how to represent data in arrays and directly navigate memory using pointers. In **Module 05**, I advanced to professional **modular application architecture** by separating code into functions, header files (`.h`), and implementation files (`.cpp`).

Key architectural takeaways:
- **`main()` Function:** The official entry point of any C++ program. Keeping `main()` clean and focused on high-level orchestration is an industry standard.
- **Functions:** Modular, single-responsibility blocks of code that accept parameters, execute operations, and optionally return results.
- **Function Declarations (Prototypes) vs Definitions:** Moving declarations into header files (`.h`) allows different translation units to know a function's signature before linking.
- **Header Guards:** Using `#ifndef`, `#define`, and `#endif` guarantees that declarations are never included more than once in a single compilation unit, preventing duplicate definition errors.
- **Multi-File Compilation:** Compiling multiple `.cpp` files into independent object files and linking them into a single binary (`clang++ main.cpp RecordTools.cpp -o main`).

---

## 2. Study Resources & Review

### Videos Watched
1. **What is the main in C++?:** [https://youtu.be/5TufmSZW3-k?si=i9zC1AQ2Ut5m1RFz](https://youtu.be/5TufmSZW3-k?si=i9zC1AQ2Ut5m1RFz)  
   *Takeaway:* Examines the execution lifecycle starting at `main()`, exit codes (`return 0;`), and how the runtime system interacts with the OS.
2. **Functions:** [https://youtu.be/BGmDRQzY4CA?si=imy3bP7zocwt4WIo](https://youtu.be/BGmDRQzY4CA?si=imy3bP7zocwt4WIo)  
   *Takeaway:* Explains function declarations, definitions, return types, pass-by-value vs pass-by-reference (`&`), and scope.
3. **Header Files:** [https://youtu.be/qaGzc56Rekg?si=QVZpMNxuiAfa_fdy](https://youtu.be/qaGzc56Rekg?si=QVZpMNxuiAfa_fdy)  
   *Takeaway:* Covers why large C++ projects separate header interfaces (`.h`) from implementations (`.cpp`), and how the preprocessor `#include` directive works.

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
- **Record Structure (`ProductRecord`):**
  - `int id`: Unique item identifier
  - `string name`: Product title
  - `string category`: Product division/department
  - `double price`: Unit cost
  - `int quantity`: Units currently in stock
- **Functions Implemented Across Files:**
  1. `showMessage()`: System readiness banner (starter code).
  2. `addRecord(...)`: Inserts a new product record into the inventory array.
  3. `displayRecords(...)`: Renders an aligned tabular view of all catalog items with individual subtotals.
  4. `calculateTotalValue(...)`: Calculates total inventory valuation ($\sum \text{price} \times \text{quantity}$).
  5. `calculateAveragePrice(...)`: Computes the average price per product item.

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

---

## 5. Files in this Module

| File | Description |
|---|---|
| [`RecordTools.h`](RecordTools.h) | Custom header file declaring the `ProductRecord` struct and function prototypes with header guards. |
| [`RecordTools.cpp`](RecordTools.cpp) | Implementation file defining `showMessage`, `addRecord`, `displayRecords`, `calculateTotalValue`, and `calculateAveragePrice`. |
| [`main.cpp`](main.cpp) | Driver program containing `main()`, populating inventory records, displaying formatted tables, and presenting calculated metrics. |
| [`starter.cpp`](starter.cpp) / [`starter_code.cpp`](starter_code.cpp) | Direct verification of the original starter code interface. |

---

## 6. How to Compile and Run

### Compiling Multi-File Project (`main.cpp` + `RecordTools.cpp`)
```bash
clang++ -Wall -Wextra -std=c++17 main.cpp RecordTools.cpp -o main
./main
```
*(Or with `g++`: `g++ -Wall -Wextra -std=c++17 main.cpp RecordTools.cpp -o main && ./main`)*

### Compiling Starter Code
```bash
clang++ -std=c++17 starter.cpp RecordTools.cpp -o starter
./starter
```

---

## 7. Verified Console Output

```text
========================================================================================
                     Record Management System Ready! (Module 5)                         
========================================================================================

[Action] Inserting product records into the inventory system...
[Status] Successfully loaded 6 product records.

[Display] Current Product Inventory Records:
----------------------------------------------------------------------------------------
ID    Product Name                       Category           Price ($)     Qty   Subtotal ($)
----------------------------------------------------------------------------------------
101   Wireless Mechanical Keyboard       Peripherals            89.99      15        1349.85
102   Ergonomic Optical Mouse            Peripherals            49.50      25        1237.50
103   UltraWide 34-inch Monitor          Displays              459.00       8        3672.00
104   USB-C Multiport Docking Station    Accessories            65.00      18        1170.00
105   Noise-Cancelling Headphones        Audio                 179.99      12        2159.88
106   Adjustable Aluminum Laptop Stand   Accessories            39.99      30        1199.70
----------------------------------------------------------------------------------------

====================================================================================
                             INVENTORY METRICS SUMMARY                              
====================================================================================
  - Total Catalog Items:        6 products
  - Average Unit Price:         $    147.25
  - Total Inventory Valuation:  $  10788.93
====================================================================================
```

---

## 8. Key Concepts & Architecture Summary

```
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

---

## 9. Canvas Submission Information

- **GitHub Repository:** [https://github.com/hdeic/CPlusPlus-Application-Design](https://github.com/hdeic/CPlusPlus-Application-Design)
- **Module 5 Folder URL:** [https://github.com/hdeic/CPlusPlus-Application-Design/tree/main/Module05-Classes-Objects](https://github.com/hdeic/CPlusPlus-Application-Design/tree/main/Module05-Classes-Objects)
