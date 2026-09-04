# Module 03 - Variables & Data Types

## Overview & What I Learned

In [Module 01 - Setup](../Module01-Setup/README.md), I learned foundational Git and GitHub skills to manage code repositories and record commits. In [Module 02 - Application Menu & Control Structures](../Module02-Variables/README.md), I learned how to build interactive menus using loops, switch/case statements, and robust input validation.

In **Module 03**, I explored how applications store, manage, and display data:

> **Variables hold data.** There are different types of variables depending on the data, such as integers (numbers), floating-point decimals, characters, booleans, and strings (letters and text).

---

## Assignment: "Welcome to My Application"

Build a personalized **“Welcome to My Application”** program. Store the user's name, application name, and version number in variables. Display them in a clean welcome screen and push the project to GitHub.

### Starter Code
I began with the provided starter code demonstrating the core C++ variable types:

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    // Main C++ variable types

    int age = 15;                    // whole number
    double price = 19.99;            // decimal number
    float temperature = 72.5f;       // decimal number
    char grade = 'A';                // single character
    bool enrolled = true;            // true or false
    string name = "Alex";            // text

    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Price: $" << price << endl;
    cout << "Temperature: " << temperature << endl;
    cout << "Grade: " << grade << endl;
    cout << "Enrolled: " << enrolled << endl;

    return 0;
}
```

---

## Step-by-Step Concepts & Skills Mastered

### Step 1 — Understanding `cout` and `cin`
- **`cout`** displays output on the screen.
- **`cin`** receives input from the user.

```cpp
cout << "Welcome to my application!" << endl;

int choice;
cin >> choice;
```

For this module, the focus is on `cout` to display the menu and output. We are introducing `cin`, which will be used more extensively in later modules when learning user input, input validation, and how to prevent bad data from entering the application.

### Step 2 — Build the Console Interface
Using `cout` to display the application's menu, instructions, messages, and results. Later, `cin` will capture the user's choices and data:

```cpp
cout << "=== MY APPLICATION ===" << endl;
cout << "1. Add Record" << endl;
cout << "2. View Records" << endl;
cout << "3. Search" << endl;
cout << "4. Exit" << endl;
```

### Step 3 — Understand What a Variable Is
A variable is a named location in memory used to store a value. The variable has a **data type**, a **name**, and a **value**:

```cpp
int age = 15;
```
- `int` = data type
- `age` = variable name
- `15` = value

### Step 4 — Learn the Main C++ Variable Types

| Type | Example | Used For |
| :--- | :--- | :--- |
| `int` | `int age = 15;` | Whole numbers |
| `double` | `double price = 19.99;` | Decimal numbers requiring good precision |
| `float` | `float temp = 72.5f;` | Decimal numbers using less memory than double |
| `char` | `char grade = 'A';` | One character |
| `bool` | `bool active = true;` | True/false conditions |
| `string` | `string name = "Alex";` | Text sequence (requires `<string>`) |

### Step 5 — Choose the Right Variable for Your Application
I learned how to select the proper data type for different application attributes:
- **Student name**: `string`
- **Student ID**: `int`
- **Student GPA**: `double`
- **Letter grade**: `char`
- **Account active**: `bool`
- **Product price**: `double`
- **Number of items**: `int`

### Step 6 — Create Your Own Variables
I created at least six variables related to my application across at least four different C++ data types and printed every variable to the screen:
- `string userName = "Alex";` (text)
- `string appName = "Student Record Management System";` (text)
- `double versionNumber = 1.0;` (decimal)
- `int studentID = 1001;` (whole number)
- `double studentGPA = 3.85;` (decimal)
- `char letterGrade = 'A';` (character)
- `bool accountActive = true;` (boolean)
- `int totalRecords = 250;` (whole number)

### Step 7 — Connect Variables to Application Design
Variables serve as the information an application needs to remember in memory:

$$\text{Variable} \longrightarrow \text{Data} \longrightarrow \text{Object / Record} \longrightarrow \text{File or Database} \longrightarrow \text{Application Feature}$$

Later in the course, these variables will become part of classes and objects, records, arrays, and long-term storage.

---

## Personalized Welcome Application

The complete customized application is implemented in [`welcome.cpp`](welcome.cpp) (and mirrored in [`main.cpp`](main.cpp)):

```cpp
#include <iostream>
#include <string>

using namespace std;

int main() {
    // Step 1: Understanding cout and cin
    cout << "Welcome to my application!" << endl;

    // Assignment & Step 6: Create at least six variables related to your application
    // Using at least four different C++ data types (string, double, int, char, bool)
    string userName = "Alex";                               // User's name (string)
    string appName = "Student Record Management System";    // Application name (string)
    double versionNumber = 1.0;                             // Version number (double)
    int studentID = 1001;                                   // Student ID (int)
    double studentGPA = 3.85;                               // Student GPA (double)
    char letterGrade = 'A';                                 // Letter grade (char)
    bool accountActive = true;                              // Account active condition (bool)
    int totalRecords = 250;                                 // Total records count (int)

    // Optional cin: allow user to customize their name
    cout << "\nPlease enter your name (press enter for default): ";
    string inputName;
    getline(cin, inputName);
    if (!inputName.empty()) {
        userName = inputName;
    }

    // Clean Welcome Screen displaying all variables
    cout << "\n==========================================" << endl;
    cout << "      WELCOME TO " << appName << endl;
    cout << "==========================================" << endl;
    cout << "User Name:        " << userName << endl;
    cout << "Application Name: " << appName << endl;
    cout << "Version Number:   " << versionNumber << endl;
    cout << "Student ID:       " << studentID << endl;
    cout << "Student GPA:      " << studentGPA << endl;
    cout << "Letter Grade:     " << letterGrade << endl;
    cout << "Account Active:   " << (accountActive ? "true" : "false") << endl;
    cout << "Total Records:    " << totalRecords << endl;
    cout << "==========================================" << endl;
    cout << "Hello, " << userName << "! Your workspace is ready." << endl;

    // Step 2: Build the Console Interface with cout
    cout << "\n=== MY APPLICATION ===" << endl;
    cout << "1. Add Record" << endl;
    cout << "2. View Records" << endl;
    cout << "3. Search" << endl;
    cout << "4. Exit" << endl;

    // Step 1: Introducing cin
    int choice = 0;
    cout << "Choose an option: ";
    cin >> choice;
    cout << "You selected option: " << choice << endl;

    return 0;
}
```

---

## Files in this Module
- [`welcome.cpp`](welcome.cpp) / [`main.cpp`](main.cpp): The personalized welcome application.
- [`starter_code.cpp`](starter_code.cpp) / [`variables_demo.cpp`](variables_demo.cpp): The unmodified starter code demonstrating main variable types.

### Compilation & Execution
```bash
# Compile and run the Personalized Welcome Application
clang++ -Wall -Wextra -std=c++17 welcome.cpp -o welcome
./welcome

# Compile and run the Starter Code
clang++ -Wall -Wextra -std=c++17 starter_code.cpp -o starter
./starter
```

---

## Canvas Submission Information

- **GitHub Repository**: [https://github.com/hdeic/CPlusPlus-Application-Design](https://github.com/hdeic/CPlusPlus-Application-Design)
- **Module 3 Folder URL**: [https://github.com/hdeic/CPlusPlus-Application-Design/tree/main/Module03-Datasets-Arrays-Pointers](https://github.com/hdeic/CPlusPlus-Application-Design/tree/main/Module03-Datasets-Arrays-Pointers)
