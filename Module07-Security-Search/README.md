# Module 07 - Security, Roles & Binary Search

**Course:** CIS-25 - Programming Using C++ (L1-41736)  
**Student:** H Cheng  
**Repository:** [hdeic/CPlusPlus-Application-Design](https://github.com/hdeic/CPlusPlus-Application-Design)  
**Module 7 URL:** [Module07-Security-Search](https://github.com/hdeic/CPlusPlus-Application-Design/tree/main/Module07-Security-Search)

---

## 1. Overview & What I Learned

In [Module 06 - Creating Classes & Objects](../Module06-Records-Storage/README.md), I built a `Product` class with private data and public member functions. In **Module 07**, I added **rules about who can do what**. An **Admin** can add, view, search, and delete product records. A **Regular User** can only view and search them. The records are kept in sorted order, so a **binary search** can find any product by its ID quickly.

Key takeaways:
- **Access Modifiers:** `private` members are visible only inside the class. `protected` members are also visible to derived classes, which is why `username` is `protected` in `User`. `public` members are the interface everyone can call.
- **Inheritance:** `Admin` and `RegularUser` both inherit from `User`, so they share the username and the view and search features without repeating code.
- **Role-Based Permissions:** The base `User` class denies `addRecord` and `deleteRecord` by default. Only `Admin` overrides them to actually change the inventory.
- **Virtual Functions & Polymorphism:** Because those functions are `virtual`, the same call `user->addRecord(...)` runs the Admin version or the denied version depending on the real role of the object.
- **Sorted Storage:** New records are inserted at their sorted position instead of being appended, so the list is always ordered by product ID.
- **Binary Search:** On sorted data, each comparison discards half of the remaining records, so the search takes about log2(n) steps instead of n.

---

## 2. Study Resources & Review

### Videos
- **Module 7 Video Search:** [C++ binary search access modifiers classes tutorial](https://www.youtube.com/results?search_query=C%2B%2B+binary+search+access+modifiers+classes+tutorial)  
  *Takeaway:* The module page links a YouTube search instead of a single video so each student can pick an explanation that fits their learning style. The core ideas across these videos are `public`, `protected`, and `private` access, deriving classes from a base class, and the halving strategy of binary search on a sorted array.

### Concepts Reviewed
- **Why Binary Search Needs Sorted Data:** Binary search decides which half to throw away by comparing the target with the middle element. That only works if everything left of the middle is smaller and everything right of it is larger.
- **Overflow-Safe Midpoint:** `mid = left + (right - left) / 2` gives the same result as `(left + right) / 2` without the risk of `left + right` overflowing on very large arrays.
- **Protected vs Private:** Making `username` `protected` lets `Admin` print its own name in messages, while code outside the class hierarchy still cannot read or change it directly.

---

## 3. Homework Assignment Instructions

> **Assignment:**  
> Create Admin and Regular User roles. Restrict actions based on the user's role. Store records in sorted order and implement a binary search to find a record by ID or another unique field.

### How Each Requirement Is Met

| Requirement | Where It Lives |
|---|---|
| Admin and Regular User roles | `class Admin : public User` and `class RegularUser : public User` in [`User.h`](User.h) |
| Restrict actions based on role | `User::addRecord` and `User::deleteRecord` print **ACCESS DENIED**. Only `Admin` overrides them. Both roles inherit `viewRecords` and `searchRecord`. |
| Store records in sorted order | `Inventory::addSorted` in [`Inventory.cpp`](Inventory.cpp) inserts each product at its correct position by product ID |
| Binary search to find a record by ID | `binarySearch(...)` in [`Inventory.cpp`](Inventory.cpp), used for searching, for deleting, and for rejecting duplicate IDs |

### Role Permissions

| Role | View | Search | Add | Delete |
|---|---|---|---|---|
| Admin | yes | yes | yes | yes |
| Regular User | yes | yes | no | no |

### Our Customized Application
- **Domain:** eCommerce Product & Inventory Management System (continued from Modules 5 and 6).
- **Unique Search Field:** `productId`, an integer that is unique for every product. Adding a product with an ID that already exists is rejected.

---

## 4. Starter Code

The assignment provided a `User` base class, an `Admin` class, and an integer `binarySearch` function. It is kept in [`starter.cpp`](starter.cpp), with a small `main()` added so it compiles and runs on its own:

```cpp
class User {
protected:
    string username;
public:
    User(string name) : username(name) {}
};

class Admin : public User {
public:
    Admin(string name) : User(name) {}
    void addRecord() { /* add record */ }
    void deleteRecord() { /* delete record */ }
};

int binarySearch(int data[], int size, int target) {
    int left = 0, right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (data[mid] == target) return mid;
        if (data[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}
```

### How I Customized It
1. Added a `RegularUser` role next to `Admin`, both inheriting from `User`.
2. Moved `addRecord` and `deleteRecord` into `User` as `virtual` functions that deny access by default, so a Regular User is blocked at run time and gets a clear message.
3. Had `Admin` override both functions to really add to and delete from the inventory.
4. Put the shared `viewRecords` and `searchRecord` features in `User` so both roles get them.
5. Changed `binarySearch` to search an array of `Product` objects by `getProductId()`, count its comparisons, and optionally print each step.
6. Built an `Inventory` class that keeps records sorted and uses the binary search for find, delete, and duplicate checks.

---

## 5. Files in this Module

| File | Description |
|---|---|
| [`Product.h`](Product.h) / [`Product.cpp`](Product.cpp) | The `Product` class from Module 6, extended with a unique `productId` used as the search key. |
| [`Inventory.h`](Inventory.h) / [`Inventory.cpp`](Inventory.cpp) | The `Inventory` class that stores products in sorted order, plus the `binarySearch` function. |
| [`User.h`](User.h) / [`User.cpp`](User.cpp) | The `User` base class and the `Admin` and `RegularUser` roles with their permissions. |
| [`main.cpp`](main.cpp) | Driver program that shows the permission table and then walks through each role trying to add, view, search, and delete records. |
| [`starter.cpp`](starter.cpp) | The original starter code from the assignment, with a small `main()` to run it. |

---

## 6. How to Compile and Run

### Compiling the Multi-File Project
```bash
clang++ -Wall -Wextra -std=c++17 main.cpp Product.cpp Inventory.cpp User.cpp -o main
./main
```
*(Or with `g++`: `g++ -Wall -Wextra -std=c++17 main.cpp Product.cpp Inventory.cpp User.cpp -o main && ./main`)*

### Compiling Starter Code
```bash
clang++ -std=c++17 starter.cpp -o starter
./starter
```

---

## 7. Verified Console Output

```text
================================================================================
  Product Inventory System - Roles, Permissions & Binary Search
================================================================================
  ROLE          USERNAME          VIEW   SEARCH   ADD   DELETE
  Regular User  shopper_01        yes    yes      no    no
  Admin         store_admin       yes    yes      yes   yes

================================================================================
  1. Admin adds records in random ID order; the list stays sorted
================================================================================
  [Admin store_admin] add ID 276 (RED WOOLLY HOTTIE WHITE HEART.) -> inserted at sorted position 0
  [Admin store_admin] add ID 105 (WHITE METAL LANTERN) -> inserted at sorted position 0
  [Admin store_admin] add ID 342 (CREAM CUPID HEARTS COAT HANGER) -> inserted at sorted position 2
  [Admin store_admin] add ID 150 (SET 7 BABUSHKA NESTING BOXES) -> inserted at sorted position 1
  [Admin store_admin] add ID 201 (WHITE HANGING HEART T-LIGHT HOLDER) -> inserted at sorted position 2
  [Admin store_admin] add ID 118 (KNITTED UNION FLAG HOT WATER BOTTLE) -> inserted at sorted position 1
  [Admin store_admin] add ID 389 (ASSORTED COLOUR BIRD ORNAMENT) -> inserted at sorted position 6
  [Admin store_admin] view records -> allowed
    -------------------------------------------------------------------------------
    ID    STOCK    DESCRIPTION                             QTY  UNIT ($)  VALUE ($)
    -------------------------------------------------------------------------------
    105   71053    WHITE METAL LANTERN                       6      3.39      20.34
    118   84029G   KNITTED UNION FLAG HOT WATER BOTTLE       6      3.39      20.34
    150   22752    SET 7 BABUSHKA NESTING BOXES              2      7.65      15.30
    201   85123A   WHITE HANGING HEART T-LIGHT HOLDER        6      2.55      15.30
    276   84029E   RED WOOLLY HOTTIE WHITE HEART.            6      3.39      20.34
    342   84406B   CREAM CUPID HEARTS COAT HANGER            8      2.75      22.00
    389   84879    ASSORTED COLOUR BIRD ORNAMENT            32      1.69      54.08
    -------------------------------------------------------------------------------
    7 records, sorted by product ID

================================================================================
  2. Same add request from each role (restricted by role)
================================================================================
  [Regular User shopper_01] add -> ACCESS DENIED (only an Admin can add records)
  [Admin store_admin] add ID 233 (HAND WARMER UNION JACK) -> inserted at sorted position 4

================================================================================
  3. Regular User views records
================================================================================
  [Regular User shopper_01] view records -> allowed
    -------------------------------------------------------------------------------
    ID    STOCK    DESCRIPTION                             QTY  UNIT ($)  VALUE ($)
    -------------------------------------------------------------------------------
    105   71053    WHITE METAL LANTERN                       6      3.39      20.34
    118   84029G   KNITTED UNION FLAG HOT WATER BOTTLE       6      3.39      20.34
    150   22752    SET 7 BABUSHKA NESTING BOXES              2      7.65      15.30
    201   85123A   WHITE HANGING HEART T-LIGHT HOLDER        6      2.55      15.30
    233   22633    HAND WARMER UNION JACK                    6      1.85      11.10
    276   84029E   RED WOOLLY HOTTIE WHITE HEART.            6      3.39      20.34
    342   84406B   CREAM CUPID HEARTS COAT HANGER            8      2.75      22.00
    389   84879    ASSORTED COLOUR BIRD ORNAMENT            32      1.69      54.08
    -------------------------------------------------------------------------------
    8 records, sorted by product ID

================================================================================
  4. Regular User runs a binary search by product ID
================================================================================
  [Regular User shopper_01] binary search for product ID 276 -> allowed
      step 1: left=0 right=7 mid=3 (ID 201) -> 201 < 276, search right half
      step 2: left=4 right=7 mid=5 (ID 276) -> match
    FOUND in 2 comparison(s) out of 8 records:
    Product ID:   276
    Stock Code:   84029E
    Description:  RED WOOLLY HOTTIE WHITE HEART.
    Quantity:     6
    Unit Price:   $3.39
    Stock Value:  $20.34

  [Regular User shopper_01] binary search for product ID 999 -> allowed
      step 1: left=0 right=7 mid=3 (ID 201) -> 201 < 999, search right half
      step 2: left=4 right=7 mid=5 (ID 276) -> 276 < 999, search right half
      step 3: left=6 right=7 mid=6 (ID 342) -> 342 < 999, search right half
      step 4: left=7 right=7 mid=7 (ID 389) -> 389 < 999, search right half
    NOT FOUND after 4 comparison(s).

================================================================================
  5. Same delete request from each role (restricted by role)
================================================================================
  [Regular User shopper_01] delete -> ACCESS DENIED (only an Admin can delete records)
  [Admin store_admin] delete ID 150 -> deleted
  [Admin store_admin] delete ID 150 -> rejected, product ID not found

================================================================================
  6. Admin confirms the delete with a binary search
================================================================================
  [Admin store_admin] binary search for product ID 150 -> allowed
      step 1: left=0 right=6 mid=3 (ID 233) -> 233 > 150, search left half
      step 2: left=0 right=2 mid=1 (ID 118) -> 118 < 150, search right half
      step 3: left=2 right=2 mid=2 (ID 201) -> 201 > 150, search left half
    NOT FOUND after 3 comparison(s).

  [Admin store_admin] add ID 105 (WHITE METAL LANTERN) -> rejected, product ID already exists

================================================================================
  7. Final inventory
================================================================================
  [Admin store_admin] view records -> allowed
    -------------------------------------------------------------------------------
    ID    STOCK    DESCRIPTION                             QTY  UNIT ($)  VALUE ($)
    -------------------------------------------------------------------------------
    105   71053    WHITE METAL LANTERN                       6      3.39      20.34
    118   84029G   KNITTED UNION FLAG HOT WATER BOTTLE       6      3.39      20.34
    201   85123A   WHITE HANGING HEART T-LIGHT HOLDER        6      2.55      15.30
    233   22633    HAND WARMER UNION JACK                    6      1.85      11.10
    276   84029E   RED WOOLLY HOTTIE WHITE HEART.            6      3.39      20.34
    342   84406B   CREAM CUPID HEARTS COAT HANGER            8      2.75      22.00
    389   84879    ASSORTED COLOUR BIRD ORNAMENT            32      1.69      54.08
    -------------------------------------------------------------------------------
    7 records, sorted by product ID

  Total inventory value: $163.50
```

---

## 8. Key Concepts & Architecture Summary

```
                        +-----------------------------+
                        |            User             |
                        +-----------------------------+
                        | protected: username         |
                        | viewRecords()     everyone  |
                        | searchRecord()    everyone  |
                        | virtual addRecord()   DENY  |
                        | virtual deleteRecord() DENY |
                        +--------------+--------------+
                                       |
                   +-------------------+-------------------+
                   |                                       |
                   v                                       v
      +--------------------------+           +--------------------------+
      |          Admin           |           |       RegularUser        |
      +--------------------------+           +--------------------------+
      | addRecord()    override  |           | (no overrides, so add    |
      | deleteRecord() override  |           |  and delete stay denied) |
      +------------+-------------+           +--------------------------+
                   |
                   | changes
                   v
      +-----------------------------------------------------------+
      |                       Inventory                           |
      |  records sorted by ID:  105  118  201  233  276  342  389 |
      |  addSorted()   removeById()   findById() -> binarySearch  |
      +-----------------------------------------------------------+
```

1. **Security Through Design:** A Regular User has no code path that changes the inventory. Every add or delete request goes through a function that the `RegularUser` class never overrides.
2. **One Call, Different Behavior:** In `main.cpp`, the loop `for (User *user : users) user->addRecord(...)` sends the same request to both roles. The virtual function picks the right behavior for each role.
3. **Sorted Insert Keeps Search Valid:** Because `addSorted` never breaks the order, the binary search is always correct, even after adds and deletes.
4. **Binary Search Is Fast:** In the output, finding ID 276 among 8 records took 2 comparisons, and proving that ID 999 does not exist took 4. A linear search would need up to 8 comparisons for each.

---

## 9. Canvas Submission Information

- **GitHub Repository:** [https://github.com/hdeic/CPlusPlus-Application-Design](https://github.com/hdeic/CPlusPlus-Application-Design)
- **Module 7 Folder URL:** [https://github.com/hdeic/CPlusPlus-Application-Design/tree/main/Module07-Security-Search](https://github.com/hdeic/CPlusPlus-Application-Design/tree/main/Module07-Security-Search)
