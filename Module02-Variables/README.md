# Module 02 - Application Menu & Control Structures

## Overview & What I Learned

In [Module 01 - Setup](../Module01-Setup/README.md), I established my development workflow and learned the fundamentals of version control: how **Repositories** store project containers, **Folders** organize distinct modules, **Files** hold code and documentation, **Commits** capture progress snapshots, and **Push** syncs local commits to GitHub.

Building on that foundation in **Module 02**, I learned how to structure an interactive console program:

> **A menu is the front door of many applications.** In this module, I built a user-friendly command-line menu and learned how `switch/case` statements, loops, strings, and functions work together to control an application. I also began thinking about how an application's menu connects users to core features such as adding, viewing, searching, updating, and deleting records.

---

## Key Concepts & Skills Mastered

### 1. Application Menu Architecture (At Least Five Options)
I learned that a command-line menu serves as the primary navigation hub and dispatcher for an application:
- Rather than running a one-off script that exits immediately, a menu keeps the application active and responsive.
- It provides a clean interface connecting user choices to features:
  - **1. Add Record**: Routes to `addRecord()` to create new records.
  - **2. View Records**: Routes to `viewRecords()` to display records.
  - **3. Search**: Routes to `searchRecords()` to find records.
  - **4. Update Record**: Routes to `updateRecord()` to edit records.
  - **5. Delete Record**: Routes to `deleteRecord()` to remove records.
  - **6. Exit**: Terminates the application loop with a farewell message.

### 2. If Statements and Nested If Statements
I explored how conditional statements direct program execution based on boolean logic:
- **Simple `if`**: Executes code only when a condition evaluates to true.
- **`if / else`**: Selects between two alternative execution paths.
- **`if / else if / else`**: Evaluates a series of multiple conditions sequentially.
- **Nested `if` statements**: Placing an `if` statement inside another `if` block for multi-tier decision logic.

### 3. Switch/Case Statements
I learned how to use `switch` statements to manage multi-way branching when selecting between discrete values (such as numeric menu choices `1` through `6`):
- **`switch (choice)`**: Evaluates the integer variable cleanly without long chains of `if / else if`.
- **`case value:`**: Executes the function corresponding to the matching value (`case 1: addRecord(); break;`, etc.).
- **`break;`**: Immediately exits the switch block, preventing unintended **fall-through**.
- **`default:`**: Catches any numeric choice outside the valid range (`"Invalid choice. Try again."`).

### 4. Loops & Application Continuance
To keep the application running until the user chooses to exit:
- I used a **`while (choice != 6)`** loop so the menu continues displaying after each action until the user chooses option `6` (Exit).

### 5. Input Validation (Preventing Crashes & Infinite Loops)
One of the most important concepts I mastered was input validation:
- If a user inputs non-numeric characters (e.g., `"abc"`), `cin` enters a fail state (`cin.fail() == true`).
- Without validation, bad characters remain stuck in the input buffer, causing an infinite loop.
- I implemented stream recovery:
  ```cpp
  if (cin.fail()) {
      cin.clear();                                         // 1. Clear the error state
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 2. Discard bad characters
      cout << "Invalid input. Please enter a number." << endl;
      continue;                                            // 3. Re-prompt user
  }
  ```

### 6. Functions & Modular Decomposition
I decoupled user interface routing from application logic by creating dedicated functions (`addRecord()`, `viewRecords()`, `searchRecords()`, `updateRecord()`, `deleteRecord()`).

---

## Source Code

```cpp
#include <iostream>
#include <string>
#include <limits>

using namespace std;

void addRecord() {
    cout << "Add Record selected." << endl;
}

void viewRecords() {
    cout << "View Records selected." << endl;
}

void searchRecords() {
    cout << "Search selected." << endl;
}

void updateRecord() {
    cout << "Update Record selected." << endl;
}

void deleteRecord() {
    cout << "Delete Record selected." << endl;
}

int main() {
    int choice = 0;

    while (choice != 6) {
        cout << "\n=== MY APPLICATION ===" << endl;
        cout << "1. Add Record" << endl;
        cout << "2. View Records" << endl;
        cout << "3. Search" << endl;
        cout << "4. Update Record" << endl;
        cout << "5. Delete Record" << endl;
        cout << "6. Exit" << endl;
        cout << "Choose an option: ";

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                addRecord();
                break;
            case 2:
                viewRecords();
                break;
            case 3:
                searchRecords();
                break;
            case 4:
                updateRecord();
                break;
            case 5:
                deleteRecord();
                break;
            case 6:
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}
```

### Compilation & Execution
```bash
clang++ -Wall -Wextra -std=c++17 menu.cpp -o menu
./menu
```

---

## References & Video Tutorials

1. **If Statements**  
   [https://youtu.be/N42EzLQ4gDE?si=kSbNz40G6P1T_AbU](https://youtu.be/N42EzLQ4gDE?si=kSbNz40G6P1T_AbU)

2. **Nested if statement**  
   [https://youtu.be/YQdpZYRmzmk?si=mxjfqlYouVt5gAhU](https://youtu.be/YQdpZYRmzmk?si=mxjfqlYouVt5gAhU)

3. **Syntax vs Logical Errors**  
   [https://youtu.be/7kt03IZODAI?si=UdTm4x3AKo-1oWEb](https://youtu.be/7kt03IZODAI?si=UdTm4x3AKo-1oWEb)

4. **Switch Statements**  
   [https://youtu.be/ftlbkWiDQCE?si=ReYfOuo1Y8G-NVth](https://youtu.be/ftlbkWiDQCE?si=ReYfOuo1Y8G-NVth)

5. **Loops**  
   [https://youtu.be/qGKCnTq8CqQ?si=Xnu9F3d4sNaPakYr](https://youtu.be/qGKCnTq8CqQ?si=Xnu9F3d4sNaPakYr)

6. **Infinite Loops**  
   [https://youtu.be/qGKCnTq8CqQ?si=It4CpYCU6w6Tlgiq](https://youtu.be/qGKCnTq8CqQ?si=It4CpYCU6w6Tlgiq)
