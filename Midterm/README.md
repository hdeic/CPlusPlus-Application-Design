# C++ Midway Project: Store Inventory Management System

**Course:** CIS-25 Programming Using C++ (L1-41736)
**Student:** H Cheng
**Repository:** [hdeic/CPlusPlus-Application-Design](https://github.com/hdeic/CPlusPlus-Application-Design)
**PDF version of this report:** [`output.pdf`](output.pdf)

---

## 1. What my program does

I wrote a program that keeps track of the products in a small online store. It is the same store
app I have been building through the modules this semester, so for this project I pulled those
pieces together into one program instead of starting something new.

When you run it, the first thing it does is open `inventory.txt` and read the products into an
array that it creates while the program is running. Then it asks who is logging in. If you choose
Admin you can add, delete and update products. If you choose Regular User you can only look at
them and search. After that a menu with ten options keeps coming back until you choose Exit.

The products are always kept in order of their product ID. I did it that way on purpose, because
a binary search only works if the data is sorted. When you search for an ID on option 2, the
program checks the middle product and then throws away the half that cannot possibly contain what
you are looking for. With 8 products that means 4 comparisons at the very worst instead of 8. I
print every step so you can see it happening. I also reuse the same search when deleting a product
and when checking that a new product ID is not already taken.

Option 3 is a second search that works on the descriptions instead. Those are not sorted, so that
one has to check every product one at a time. Having both of them in the same program makes it
easy to see why sorting the data first is worth the trouble.

Every prompt checks what you typed. Letters where a number belongs, an empty description, a
negative quantity and a price of zero all get refused with a message explaining the problem, and
then it asks again. When you exit, the program writes everything back to `inventory.txt`, so the
next time you run it your changes are still there.

---

## 2. How I put it together

I split the program into four pairs of files so that each class has its own header and its own
implementation, the same way we did it in Module 5.

| File | What is in it |
|---|---|
| [`main.cpp`](main.cpp) | The menu, the switch, the input checking, the data type screen |
| [`Product.h`](Product.h) / [`Product.cpp`](Product.cpp) | Class 1, one product |
| [`Inventory.h`](Inventory.h) / [`Inventory.cpp`](Inventory.cpp) | Class 2, the array, the searches, the file reading and writing |
| [`User.h`](User.h) / [`User.cpp`](User.cpp) | Class 3, `User` with `Admin` and `RegularUser` under it |
| [`inventory.txt`](inventory.txt) | The data file |
| [`inventory_report.txt`](inventory_report.txt) | The report the program writes on option 7 |
| [`output.pdf`](output.pdf) | The PDF version of this report |

### How to build and run it

```bash
clang++ -Wall -Wextra -std=c++17 main.cpp Product.cpp Inventory.cpp User.cpp -o main
./main
```

It builds with no warnings on both `clang++` and `g++`. You have to run it from inside the
`Midterm` folder, otherwise it cannot find `inventory.txt`.

---

## 3. The concepts I had to use, and where they are

| Concept | How I used it | Where it is |
|---|---|---|
| Data types and data sizes | Option 8 measures `bool`, `char`, `short`, `int`, `long`, `long long`, `float`, `double` and `std::string` with `sizeof` while the program runs. It also prints the range of an `int` and how many digits `float` and `double` can hold. | `main.cpp`, `showDataTypes()` |
| File types (.txt) | Two text files. `inventory.txt` holds the products and gets read at the start and written at the end. `inventory_report.txt` is a formatted report the program writes on option 7. | `inventory.txt`, `inventory_report.txt` |
| Use of pointers | The array is only reachable through the pointer `Product *items`. My binary search gives back a pointer to the product it found, the price update writes through that same pointer, deleting works out an index by subtracting two pointers, and option 9 walks the whole array with pointer arithmetic. | `Inventory.cpp`, `pointerWalk()` |
| Arrays and dynamic memory | The products live in an array I create with `new Product[capacity]`. When it runs out of room `resize()` makes a bigger one, copies everything over and frees the old one. The destructor calls `delete[]` so nothing is left behind. | `Inventory.cpp`, constructor and `resize()` |
| A search algorithm | `binarySearchById()` cuts the range in half every step and counts its comparisons. I reuse it for deleting a product and for checking that a new ID is not already taken. There is also a linear search over the descriptions so the two can be compared. | `Inventory.cpp`, `binarySearchById()` |
| Use of strings | `std::string` holds the stock codes, descriptions and usernames. I split the file lines on the `|` character, trim spaces off what the user types, convert text to upper case so searching ignores capitals, and use `find()` to check for a substring. | `Product.cpp` and `Inventory.cpp` |
| File I/O | `ifstream` reads the file one line at a time when the program starts and skips blank lines, comments and anything broken. `ofstream` writes the data file and the report. Both get closed when I am done with them. | `Inventory.cpp`, `loadFromFile()` and `saveToFile()` |
| At least two classes | I ended up with three. `Product` is one item, `Inventory` owns the array and does the searching and file work, and `User` is the base class that `Admin` and `RegularUser` inherit from. | `Product.h`, `Inventory.h`, `User.h` |

Other things from earlier modules that ended up in here:

- **Menu and switch.** Ten options inside a loop, sent to the right code by a `switch`, repeating until you choose Exit. This came from Module 2.
- **Input validation.** Every prompt checks what you typed, explains the problem and asks again, so a typo cannot get into the data.
- **Encapsulation.** All the data members are private. Nothing outside the class can change them except through a setter that checks the value first.
- **Inheritance.** `Admin` and `RegularUser` both come from `User`. The menu asks the user object what it is allowed to do and the virtual function answers for whichever role it really is.
- **Header files.** Four pairs of `.h` and `.cpp` files with include guards, compiled separately and linked together.

---

## 4. What I found hard

The dynamic array gave me the most trouble. My first version just appended every new product to
the end, which was fine until I tried to search and realised the binary search was giving me wrong
answers because the list was not actually sorted any more. I fixed it by finding the right slot
first, shifting everything after it along by one, and only then putting the new product in.
Deleting had the same problem in reverse, so I shift the other way to close the gap.

The other thing I had to be careful about was memory. Every `new[]` needs a matching `delete[]`,
and when the array grows I have to copy the products across and free the old block, not just point
at the new one. I also turned off copying for the `Inventory` class on purpose, because the default
copy would have copied the pointer rather than the array and then two objects would try to free the
same memory.

Picking `double` rather than `float` for the prices was a small decision that the data type screen
ended up explaining for me. A `float` only holds about 6 reliable digits, which is not really
enough once you are adding up a lot of money.

---

## 5. The menu

| Option | What it does | Who can use it |
|---|---|---|
| 1 | Display all products | Everyone |
| 2 | Search by product ID, using the binary search | Everyone |
| 3 | Search by description, using a linear search | Everyone |
| 4 | Add a new product | Admin only |
| 5 | Delete a product | Admin only |
| 6 | Update a product price | Admin only |
| 7 | Save the data and write the report to file | Everyone |
| 8 | Show the data types and memory sizes | Everyone |
| 9 | Pointer demonstration | Everyone |
| 0 | Exit, which saves the data file | Everyone |

---

## 6. Screenshots of it running

These are from real runs of the program. What I typed shows up after each prompt.

### 6.1 Loading the file, logging in, and the product table

This is what you see when you run the program. It opens `inventory.txt`, reads 8 products into the
array and says how many it got. Then it asks for a role and a username. I picked Admin here. The
last line under the table shows the array capacity, which is bigger than the number of products
because my array doubles itself when it fills up.

![Loading the file and showing the table](screenshots/01-startup-p1.png)
![Loading the file and showing the table, part 2](screenshots/01-startup-p2.png)

### 6.2 Binary search by product ID

Looking for ID 276 only takes 2 comparisons, and proving that ID 999 is not there takes 4, out of 8
products. I made it print every step with the left, right and mid positions so you can actually
watch it throw away half the list each time. It also prints how many comparisons a normal search
would have needed, which is up to 8.

![Binary search](screenshots/02-binary-p1.png)
![Binary search, part 2](screenshots/02-binary-p2.png)

### 6.3 Input validation, then adding a product

I typed the word `abc` where a number should go, left the description blank, put in a negative
quantity and then a price of zero. The program refused all four, said what was wrong each time, and
asked again instead of crashing or saving bad data. Once everything was valid it added the product
in the right spot to keep the list sorted.

![Input validation](screenshots/03-validate-p1.png)
![Input validation, part 2](screenshots/03-validate-p2.png)

### 6.4 Searching the descriptions as text

This is my second search and it works on words instead of numbers. The descriptions are not in
alphabetical order so this one has to check them one by one. I typed `babushka` in lower case and
it still matched `SET 7 BABUSHKA NESTING BOXES` because I convert both sides to upper case first.
The second search shows what happens when nothing matches.

![String search](screenshots/04-strings-p1.png)
![String search, part 2](screenshots/04-strings-p2.png)

### 6.5 Regular User blocked from the admin options

Here I logged in as a Regular User instead. Options 4 and 5 get refused straight away and the
program says which role you would need. Viewing and searching still work fine, so the block is only
on changing things, not on looking at them.

![Role restrictions](screenshots/05-roles-p1.png)
![Role restrictions, part 2](screenshots/05-roles-p2.png)

### 6.6 Updating, deleting, and writing both text files

I changed a price, deleted a product, and then used option 7 to write both files. `inventory.txt`
is the one the program reads next time it runs, and `inventory_report.txt` is a tidy version for a
person to read. The table at the end shows that both changes actually stuck.

![File writing](screenshots/06-files-p1.png)
![File writing, part 2](screenshots/06-files-p2.png)
![File writing, part 3](screenshots/06-files-p3.png)

### 6.7 Data types and how many bytes each one takes

This screen measures every type I use with `sizeof` while the program is running, in bytes and in
bits. It also prints the range of an `int` and compares how many digits `float` and `double` can
hold. That last bit is the reason I used `double` for prices instead of `float`.

![Data types](screenshots/07-types-p1.png)
![Data types, part 2](screenshots/07-types-p2.png)

### 6.8 Walking the array with a pointer

A pointer starts at the first product and moves forward one product at a time. The addresses go up
by exactly 72 bytes every step, which is the size of one `Product`. Then I show the same
description being read three different ways that all mean the same thing, and I subtract two
pointers to get back an index.

![Pointer walk](screenshots/08-pointers-p1.png)
![Pointer walk, part 2](screenshots/08-pointers-p2.png)

---

## 7. The data file format

`inventory.txt` uses a `|` between the fields instead of a comma, because the descriptions have
spaces in them and could have commas too. Blank lines and lines starting with `#` get skipped, and
so does anything broken or duplicated, with a count reported when the program starts.

```
# productId|stockCode|description|quantity|unitPrice
105|71053|WHITE METAL LANTERN|6|3.39
```
