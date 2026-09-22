# Module 06 - Creating Classes & Objects

**Course:** CIS-25 - Programming Using C++ (L1-41736)  
**Student:** H Cheng  
**Repository:** [hdeic/CPlusPlus-Application-Design](https://github.com/hdeic/CPlusPlus-Application-Design)  
**Module 6 URL:** [Module06-Records-Storage](https://github.com/hdeic/CPlusPlus-Application-Design/tree/main/Module06-Records-Storage)

---

## 1. Overview & What I Learned

In [Module 05 - Records, Headers & Functions](../Module05-Classes-Objects/README.md), I stored product records in a `struct` and wrote separate functions that operated on them. In **Module 06**, I moved to **object-oriented programming** by bundling the data and the functions that act on it into a single `Product` **class**.

Key takeaways:
- **Class vs Object:** A class is the blueprint (`Product`). An object is one real instance built from that blueprint (`lantern`, `handWarmer`, `birdOrnament`).
- **Encapsulation:** Data members are `private`, so code outside the class cannot change them directly. All access goes through `public` member functions.
- **Constructor:** A special function with the same name as the class that runs automatically when an object is created and puts it in a valid starting state.
- **Member Functions:** Functions that belong to the class and work on that object's own data (`displayProduct`, `calculateStockValue`, `restock`, `sell`).
- **Getters & Setters:** Getters read private data. Setters change private data, and can reject bad values, which a public variable never could.
- **`const` Member Functions:** Marking read-only functions `const` promises they never modify the object.

---

## 2. Study Resources & Review

### Videos
- **Module 6 Video Search:** [C++ classes objects constructors encapsulation beginner](https://www.youtube.com/results?search_query=C%2B%2B+classes+objects+constructors+encapsulation+beginner)  
  *Takeaway:* The module page links a YouTube search instead of a single video so each student can pick an explanation that fits their learning style. The core ideas across these videos are the class/object distinction, constructors, and using `private` plus getters and setters to protect data.

### Concepts Reviewed
- **Struct (Module 5) vs Class (Module 6):** In Module 5, any function could write directly to `records[i].unitPrice`. In Module 6, `unitPrice` is private, so the only way to change it is `setUnitPrice()`, which refuses zero or negative prices.
- **Member Initializer List:** The constructor uses `: stockCode(code), description(desc), ...` to initialize members before the constructor body runs.

---

## 3. Homework Assignment Instructions

> **Assignment:**  
> Create a class that represents something in your application. Examples include Student, Customer, Product, GameCharacter, Appointment, Book, or Employee. Your class must contain private data members, a constructor, at least two member functions, and at least one getter or setter. Create at least two objects from your class and display their information.

### How Each Requirement Is Met

| Requirement | Where It Lives |
|---|---|
| A class that represents something in my application | `class Product` in [`Product.h`](Product.h), continuing the eCommerce inventory application from Module 5 |
| Private data members | `stockCode`, `description`, `quantity`, `unitPrice` under `private:` |
| A constructor | `Product(code, desc, qty, price)` in [`Product.cpp`](Product.cpp), which also guards against negative quantity or price |
| At least two member functions | `displayProduct()`, `calculateStockValue()`, `restock()`, `sell()` |
| At least one getter or setter | Getters: `getStockCode()`, `getDescription()`, `getQuantity()`, `getUnitPrice()`. Setter: `setUnitPrice()` |
| At least two objects, with their information displayed | Three objects in [`main.cpp`](main.cpp): `lantern`, `handWarmer`, `birdOrnament` |

### Our Customized Application
- **Domain:** eCommerce Product & Inventory Management System (continued from Module 5).
- **`Product` Class Design:**

| Member | Access | Purpose |
|---|---|---|
| `std::string stockCode` | private | Unique product/stock identifier |
| `std::string description` | private | Product title |
| `int quantity` | private | Units currently in stock |
| `double unitPrice` | private | Price per unit |
| `Product(...)` | public | Constructor, sets all four members and rejects negative values |
| `displayProduct()` | public | Prints the object's information and its stock value |
| `calculateStockValue()` | public | Returns quantity x unit price |
| `restock(int)` | public | Adds units, rejects zero or negative amounts |
| `sell(int)` | public | Removes units, rejects selling more than is in stock |
| `getStockCode()`, `getDescription()`, `getQuantity()`, `getUnitPrice()` | public | Getters for the private data |
| `setUnitPrice(double)` | public | Setter that only accepts a positive price |

---

## 4. Starter Code

The assignment instructions provided a `Student` class as the starting point. It is kept in [`starter.cpp`](starter.cpp) and compiles on its own:

```cpp
class Student {
private:
    string name;
    int id;
    double score;

public:
    Student(string studentName, int studentId, double studentScore) {
        name = studentName;
        id = studentId;
        score = studentScore;
    }

    void displayStudent() { ... }
    string getName() { return name; }
    void setScore(double newScore) { score = newScore; }
};
```

### How I Customized It
1. Replaced `Student` with a `Product` class that fits my eCommerce application.
2. Split the class into a header ([`Product.h`](Product.h)) and an implementation file ([`Product.cpp`](Product.cpp)), applying what I learned in Module 5.
3. Used a member initializer list in the constructor and added validation so an object can never start with a negative quantity or price.
4. Added two behavior functions, `restock()` and `sell()`, that change the object's state safely.
5. Made the setter validate its input and return `true` or `false`, so the caller knows whether the change was accepted.
6. Marked every read-only function `const`.

---

## 5. Files in this Module

| File | Description |
|---|---|
| [`Product.h`](Product.h) | Class declaration with private data members and public member function prototypes, protected by header guards. |
| [`Product.cpp`](Product.cpp) | Implementation of the constructor, member functions, getters, and setter. |
| [`main.cpp`](main.cpp) | Driver program that creates three `Product` objects, displays them, changes them through member functions and the setter, and displays them again. |
| [`starter.cpp`](starter.cpp) | The original `Student` starter code from the assignment. |

---

## 6. How to Compile and Run

### Compiling the Multi-File Project (`main.cpp` + `Product.cpp`)
```bash
clang++ -Wall -Wextra -std=c++17 main.cpp Product.cpp -o main
./main
```
*(Or with `g++`: `g++ -Wall -Wextra -std=c++17 main.cpp Product.cpp -o main && ./main`)*

### Compiling Starter Code
```bash
clang++ -std=c++17 starter.cpp -o starter
./starter
```

---

## 7. Verified Console Output

```text
============================================================
        Product Inventory System - Classes & Objects
============================================================

[1] Three Product objects created with the constructor:
------------------------------------------------------------
  Stock Code:   71053
  Description:  WHITE METAL LANTERN
  Quantity:     6
  Unit Price:   $3.39
  Stock Value:  $20.34
------------------------------------------------------------
  Stock Code:   22633
  Description:  HAND WARMER UNION JACK
  Quantity:     6
  Unit Price:   $1.85
  Stock Value:  $11.10
------------------------------------------------------------
  Stock Code:   84879
  Description:  ASSORTED COLOUR BIRD ORNAMENT
  Quantity:     32
  Unit Price:   $1.69
  Stock Value:  $54.08
------------------------------------------------------------

[2] Using member functions to change object state:
  restock("WHITE METAL LANTERN", 10): OK
  sell("HAND WARMER UNION JACK", 4):  OK
  sell("HAND WARMER UNION JACK", 50): rejected (not enough stock)

[3] Using the setter to update a private data member:
  Old price of ASSORTED COLOUR BIRD ORNAMENT: $1.69
  setUnitPrice(1.49): OK
  setUnitPrice(-5.00): rejected (price must be positive)
  New price of ASSORTED COLOUR BIRD ORNAMENT: $1.49

[4] Updated object information:
------------------------------------------------------------
  Stock Code:   71053
  Description:  WHITE METAL LANTERN
  Quantity:     16
  Unit Price:   $3.39
  Stock Value:  $54.24
------------------------------------------------------------
  Stock Code:   22633
  Description:  HAND WARMER UNION JACK
  Quantity:     2
  Unit Price:   $1.85
  Stock Value:  $3.70
------------------------------------------------------------
  Stock Code:   84879
  Description:  ASSORTED COLOUR BIRD ORNAMENT
  Quantity:     32
  Unit Price:   $1.49
  Stock Value:  $47.68
------------------------------------------------------------

============================================================
  Total Units In Stock:     50
  Total Inventory Value:    $105.62
============================================================
```

---

## 8. Key Concepts & Architecture Summary

```
                 +------------------------------------+
                 |           class Product            |
                 +------------------------------------+
                 | private:                           |
                 |   stockCode, description,          |
                 |   quantity, unitPrice              |
                 +------------------------------------+
                 | public:                            |
                 |   Product(...)       constructor   |
                 |   displayProduct()   member fn     |
                 |   calculateStockValue()            |
                 |   restock() / sell() member fns    |
                 |   get...()           getters       |
                 |   setUnitPrice()     setter        |
                 +-----------------+------------------+
                                   |
                     instantiated as three objects
                                   |
          +------------------------+------------------------+
          |                        |                        |
          v                        v                        v
   +-------------+          +-------------+          +---------------+
   |   lantern   |          | handWarmer  |          | birdOrnament  |
   | 71053       |          | 22633       |          | 84879         |
   +-------------+          +-------------+          +---------------+
```

1. **Encapsulation:** `main.cpp` never touches `quantity` or `unitPrice` directly. Trying `lantern.unitPrice = 0;` would not compile, because the member is private.
2. **Each Object Has Its Own Data:** `restock(10)` on `lantern` changes only the lantern's quantity. The other two objects are unaffected.
3. **Validation Lives In The Class:** Because all changes go through `sell()`, `restock()`, and `setUnitPrice()`, invalid states such as negative stock or a negative price are impossible, as the rejected calls in the output show.
4. **From Struct To Class:** Module 5 kept data and functions apart. Module 6 puts them together, which is the foundation for inheritance and polymorphism later in the course.

---

## 9. Canvas Submission Information

- **GitHub Repository:** [https://github.com/hdeic/CPlusPlus-Application-Design](https://github.com/hdeic/CPlusPlus-Application-Design)
- **Module 6 Folder URL:** [https://github.com/hdeic/CPlusPlus-Application-Design/tree/main/Module06-Records-Storage](https://github.com/hdeic/CPlusPlus-Application-Design/tree/main/Module06-Records-Storage)
