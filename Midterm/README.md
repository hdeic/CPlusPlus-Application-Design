# C++ Midway Project - Store Inventory Management System

**Course:** CIS-25 - Programming Using C++ (L1-41736)
**Student:** H Cheng
**Repository:** [hdeic/CPlusPlus-Application-Design](https://github.com/hdeic/CPlusPlus-Application-Design)
**Report:** [`output.pdf`](output.pdf)

---

## 1. What This Program Does

A menu-driven inventory manager for a small online store. It is the same application built up
across the course modules, brought together into one program.

At start-up it reads its records from `inventory.txt` into an array it allocates on the heap,
then asks who is signing in. An **Admin** may add, delete and update records. A **Regular User**
may only view and search. A menu of ten options then runs in a loop until Exit is chosen.

Records are always kept sorted by product ID, which is what makes the **binary search** valid.
On exit the records are written back to `inventory.txt`, so the next run starts where this one
ended.

---

## 2. Required Concepts and Where Each One Is Used

| Required Concept | How This Program Uses It | Where |
|---|---|---|
| Data types and data sizes | `bool`, `char`, `short`, `int`, `long`, `long long`, `float`, `double` and `std::string` measured with `sizeof`, plus the range of `int` and the precision of `float` against `double` | [`main.cpp`](main.cpp) `showDataTypes()` |
| File types (`.txt`) | `inventory.txt` holds the records, `inventory_report.txt` holds a formatted report | [`inventory.txt`](inventory.txt), [`inventory_report.txt`](inventory_report.txt) |
| Use of pointers | `Product *items` reaches the array, the binary search returns a pointer, the price update writes through it, deletion subtracts pointers to get an index, and option 9 walks the array with pointer arithmetic | [`Inventory.cpp`](Inventory.cpp) |
| Arrays and dynamic memory | `new Product[capacity]`, `resize()` doubles the array, `delete[]` in the destructor | [`Inventory.cpp`](Inventory.cpp) |
| Binary search algorithm | `binarySearchById()` halves the range each step and reports its comparison count | [`Inventory.cpp`](Inventory.cpp) |
| Use of strings | `std::string` fields, splitting file lines on `|`, trimming input, upper-casing for a case-insensitive match, `find()` for substrings | [`Product.cpp`](Product.cpp), [`Inventory.cpp`](Inventory.cpp) |
| File I/O | `ifstream` reads the data file line by line, `ofstream` writes the data file and the report | [`Inventory.cpp`](Inventory.cpp) |
| At least two classes | Three: `Product`, `Inventory`, and `User` with `Admin` and `RegularUser` derived from it | [`Product.h`](Product.h), [`Inventory.h`](Inventory.h), [`User.h`](User.h) |

Also carried over from earlier modules: a menu loop driven by `switch`, input validation on every
prompt, encapsulation with private data and validating setters, inheritance with virtual
functions, and separate compilation across four translation units.

---

## 3. Files

| File | Description |
|---|---|
| [`main.cpp`](main.cpp) | Menu loop, `switch` routing, validated input helpers, data-type screen |
| [`Product.h`](Product.h) / [`Product.cpp`](Product.cpp) | Class 1: one inventory record, with file-line conversion both ways |
| [`Inventory.h`](Inventory.h) / [`Inventory.cpp`](Inventory.cpp) | Class 2: the dynamic array, binary search, linear search, file I/O |
| [`User.h`](User.h) / [`User.cpp`](User.cpp) | Class 3: `User` base class with `Admin` and `RegularUser` |
| [`inventory.txt`](inventory.txt) | The data file the program reads at start-up and rewrites on exit |
| [`inventory_report.txt`](inventory_report.txt) | The formatted report the program writes on menu option 7 |
| [`output.pdf`](output.pdf) | The submitted report: explanation, concept list, and screenshots |

---

## 4. How to Compile and Run

```bash
clang++ -Wall -Wextra -std=c++17 main.cpp Product.cpp Inventory.cpp User.cpp -o main
./main
```

*(Or with `g++`: `g++ -Wall -Wextra -std=c++17 main.cpp Product.cpp Inventory.cpp User.cpp -o main && ./main`)*

> Run `./main` from inside the `Midterm` folder so the relative path to `inventory.txt` resolves.

Compiles with no warnings under both `clang++` and `g++`.

---

## 5. Menu Options

| Option | Action | Role |
|---|---|---|
| 1 | Display all products | Everyone |
| 2 | Search by product ID (binary search, prints each step) | Everyone |
| 3 | Search by description (linear search over strings) | Everyone |
| 4 | Add a new product | Admin only |
| 5 | Delete a product | Admin only |
| 6 | Update a product price | Admin only |
| 7 | Save data and write the report to file | Everyone |
| 8 | Show data types and memory sizes | Everyone |
| 9 | Pointer demonstration | Everyone |
| 0 | Exit (saves the data file) | Everyone |

---

## 6. Data File Format

`inventory.txt` is pipe-delimited so descriptions may contain spaces and commas. Blank lines and
lines starting with `#` are ignored, and malformed or duplicate records are skipped with a count
reported at start-up.

```
# productId|stockCode|description|quantity|unitPrice
105|71053|WHITE METAL LANTERN|6|3.39
```
