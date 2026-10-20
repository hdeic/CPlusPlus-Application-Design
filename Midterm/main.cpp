// ===========================================================================
// C++ Midway Project - Store Inventory Management System
// Course:  CIS-25 - Programming Using C++ (L1-41736)
// Student: H Cheng
//
// A menu-driven inventory manager. It loads its records from a .txt file,
// keeps them in a dynamically allocated array that stays sorted by product ID,
// finds records with a binary search, and writes its data and reports back out
// to .txt files. Admin and Regular User roles decide who may change anything.
//
// Build:  clang++ -Wall -Wextra -std=c++17 main.cpp Product.cpp Inventory.cpp User.cpp -o main
// Run:    ./main
// ===========================================================================

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include "Product.h"
#include "Inventory.h"
#include "User.h"

using namespace std;

// Names of the two .txt files this program reads and writes.
const string DATA_FILE = "inventory.txt";
const string REPORT_FILE = "inventory_report.txt";

// ---------------------------------------------------------------------------
// Validated input helpers.
//
// Every one of these keeps asking until the user supplies something usable, so
// a typo can never put the program into a bad state. They return false only
// when the input stream ends (which happens when input is piped in from a
// file), and then main() shuts down cleanly.
// ---------------------------------------------------------------------------

// Throws away the rest of the current input line.
void clearInputLine() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Reads a whole integer between low and high.
bool readInt(const string &prompt, int low, int high, int &result) {
    while (true) {
        cout << prompt;
        if (!(cin >> result)) {
            if (cin.eof()) return false;             // no more input
            cout << "    [Invalid] That is not a whole number. Try again.\n";
            clearInputLine();
            continue;
        }
        clearInputLine();
        if (result < low || result > high) {
            cout << "    [Invalid] Enter a number from " << low
                 << " to " << high << ".\n";
            continue;
        }
        return true;
    }
}

// Reads a price. Prices must be greater than zero.
bool readPositiveDouble(const string &prompt, double &result) {
    while (true) {
        cout << prompt;
        if (!(cin >> result)) {
            if (cin.eof()) return false;
            cout << "    [Invalid] That is not a number. Try again.\n";
            clearInputLine();
            continue;
        }
        clearInputLine();
        if (result <= 0.0) {
            cout << "    [Invalid] The price must be greater than 0.00.\n";
            continue;
        }
        return true;
    }
}

// Reads a line of text that is not allowed to be blank.
bool readNonEmptyLine(const string &prompt, string &result) {
    while (true) {
        cout << prompt;
        if (!getline(cin, result)) return false;

        // Trim the spaces off both ends before deciding if it is empty.
        size_t first = result.find_first_not_of(" \t");
        if (first == string::npos) {
            cout << "    [Invalid] This cannot be left blank.\n";
            continue;
        }
        size_t last = result.find_last_not_of(" \t");
        result = result.substr(first, last - first + 1);

        if (result.find('|') != string::npos) {
            cout << "    [Invalid] The | character is reserved for the data file.\n";
            continue;
        }
        return true;
    }
}

// ---------------------------------------------------------------------------
// Screen helpers
// ---------------------------------------------------------------------------

void printBanner() {
    cout << "\n";
    cout << "================================================================================\n";
    cout << "            STORE INVENTORY MANAGEMENT SYSTEM  -  C++ Midway Project            \n";
    cout << "                     CIS-25 Programming Using C++ | H Cheng                     \n";
    cout << "================================================================================\n";
}

void printHeading(const string &title) {
    cout << "\n--------------------------------------------------------------------------------\n";
    cout << "  " << title << "\n";
    cout << "--------------------------------------------------------------------------------\n";
}

void printMenu(const User &user) {
    string adminTag = user.canModifyRecords() ? "" : "  [Admin only]";
    cout << "\n=============== MAIN MENU  (" << user.getRole()
         << ": " << user.getUsername() << ") ===============\n";
    cout << "  1. Display all products\n";
    cout << "  2. Search by product ID   (binary search)\n";
    cout << "  3. Search by description  (linear search, strings)\n";
    cout << "  4. Add a new product" << adminTag << "\n";
    cout << "  5. Delete a product" << adminTag << "\n";
    cout << "  6. Update a product price" << adminTag << "\n";
    cout << "  7. Save data and write report to file\n";
    cout << "  8. Show data types and memory sizes\n";
    cout << "  9. Pointer demonstration\n";
    cout << "  0. Exit\n";
    cout << "================================================================\n";
}

// Menu option 8: data types and the number of bytes each one occupies.
void showDataTypes() {
    printHeading("DATA TYPES AND DATA SIZES (measured with sizeof)");

    cout << "  " << left << setw(22) << "TYPE" << setw(8) << "BYTES"
         << setw(8) << "BITS" << "WHAT THIS PROGRAM USES IT FOR\n";
    cout << "  ----------------------------------------------------------------------------\n";

    cout << "  " << left << setw(22) << "bool" << setw(8) << sizeof(bool)
         << setw(8) << sizeof(bool) * 8 << "true/false results from setters\n";
    cout << "  " << left << setw(22) << "char" << setw(8) << sizeof(char)
         << setw(8) << sizeof(char) * 8 << "single characters, the | separator\n";
    cout << "  " << left << setw(22) << "short" << setw(8) << sizeof(short)
         << setw(8) << sizeof(short) * 8 << "(not used, shown for comparison)\n";
    cout << "  " << left << setw(22) << "int" << setw(8) << sizeof(int)
         << setw(8) << sizeof(int) * 8 << "productId, quantity, array indexes\n";
    cout << "  " << left << setw(22) << "long" << setw(8) << sizeof(long)
         << setw(8) << sizeof(long) * 8 << "(not used, shown for comparison)\n";
    cout << "  " << left << setw(22) << "long long" << setw(8) << sizeof(long long)
         << setw(8) << sizeof(long long) * 8 << "(not used, shown for comparison)\n";
    cout << "  " << left << setw(22) << "float" << setw(8) << sizeof(float)
         << setw(8) << sizeof(float) * 8 << "(not used: too few digits for money)\n";
    cout << "  " << left << setw(22) << "double" << setw(8) << sizeof(double)
         << setw(8) << sizeof(double) * 8 << "unitPrice, stock values, totals\n";
    cout << "  " << left << setw(22) << "std::string" << setw(8) << sizeof(string)
         << setw(8) << sizeof(string) * 8 << "stockCode, description, usernames\n";
    cout << "  " << left << setw(22) << "Product *" << setw(8) << sizeof(Product *)
         << setw(8) << sizeof(Product *) * 8 << "pointer to the dynamic array\n";
    cout << "  " << left << setw(22) << "Product" << setw(8) << sizeof(Product)
         << setw(8) << sizeof(Product) * 8 << "one inventory record\n";
    cout << "  " << left << setw(22) << "Inventory" << setw(8) << sizeof(Inventory)
         << setw(8) << sizeof(Inventory) * 8 << "pointer + count + capacity\n";

    cout << "\n  Ranges of the whole-number and decimal types:\n";
    cout << "    int      " << numeric_limits<int>::min()
         << " to " << numeric_limits<int>::max() << "\n";
    cout << "    double   about " << numeric_limits<double>::digits10
         << " reliable decimal digits\n";
    cout << "    float    about " << numeric_limits<float>::digits10
         << " reliable decimal digits  <- why money uses double, not float\n";

    cout << "\n  Note: sizeof(std::string) is the size of the object itself. The\n";
    cout << "  characters of a long string live separately on the heap, which is\n";
    cout << "  why every description costs the same " << sizeof(string)
         << " bytes inside a Product.\n";
}

int main() {
    printBanner();

    // --- FILE INPUT: build the inventory from the .txt file ---------------
    Inventory store;                 // its constructor allocates the array
    string message;
    cout << "\n[Startup] Reading the data file...\n";
    if (store.loadFromFile(DATA_FILE, message)) {
        cout << "  OK: " << message << "\n";
    } else {
        cout << "  WARNING: " << message << "\n";
        cout << "  Starting with an empty inventory instead.\n";
    }

    // --- Role selection ---------------------------------------------------
    printHeading("SELECT A ROLE");
    cout << "  1. Admin        (view, search, add, delete, update)\n";
    cout << "  2. Regular User (view and search only)\n";
    int roleChoice = 0;
    if (!readInt("  Choose a role (1-2): ", 1, 2, roleChoice)) return 0;

    string name;
    if (!readNonEmptyLine("  Enter your username: ", name)) return 0;

    // A base-class pointer holds whichever role was chosen. The virtual
    // functions then give the right answer for that role.
    User *currentUser = nullptr;
    if (roleChoice == 1) {
        currentUser = new Admin(name);              // dynamic memory
    } else {
        currentUser = new RegularUser(name);
    }
    cout << "\n  Signed in as " << currentUser->getUsername()
         << " with the role: " << currentUser->getRole() << "\n";

    // --- Menu loop --------------------------------------------------------
    bool running = true;
    while (running) {
        printMenu(*currentUser);

        int choice = 0;
        if (!readInt("  Enter your choice (0-9): ", 0, 9, choice)) break;

        // Block the three admin-only options before doing any work.
        if ((choice == 4 || choice == 5 || choice == 6) &&
            !currentUser->canModifyRecords()) {
            printHeading("ACCESS DENIED");
            cout << "  A " << currentUser->getRole()
                 << " may only view and search records.\n";
            cout << "  Option " << choice << " needs the Admin role.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                printHeading("ALL PRODUCTS (array kept sorted by product ID)");
                store.displayAll();
                cout << fixed << setprecision(2);
                cout << "\n  Total units: " << store.totalUnits()
                     << "    Total value: $" << store.totalStockValue() << "\n";
                break;
            }

            case 2: {
                printHeading("BINARY SEARCH BY PRODUCT ID");
                int targetId = 0;
                if (!readInt("  Product ID to find: ", 1, 999999, targetId)) {
                    running = false;
                    break;
                }
                cout << "\n  Searching " << store.getCount()
                     << " sorted records:\n";

                int comparisons = 0;
                // findById hands back a POINTER to the record, or nullptr.
                Product *found = store.findById(targetId, comparisons, true);

                if (found != nullptr) {
                    cout << "\n  FOUND after " << comparisons
                         << " comparison(s):\n";
                    found->displayDetails();        // read through the pointer
                } else {
                    cout << "\n  NOT FOUND after " << comparisons
                         << " comparison(s).\n";
                }
                cout << "\n  A linear search would need up to "
                     << store.getCount() << " comparisons.\n";
                break;
            }

            case 3: {
                printHeading("LINEAR SEARCH BY DESCRIPTION (string matching)");
                string text;
                if (!readNonEmptyLine("  Text to look for: ", text)) {
                    running = false;
                    break;
                }

                int comparisons = 0;
                const Product *found = store.findByDescription(text, comparisons);
                if (found != nullptr) {
                    cout << "\n  FOUND after " << comparisons
                         << " comparison(s) (capitalisation ignored):\n";
                    found->displayDetails();
                } else {
                    cout << "\n  No description contains \"" << text
                         << "\" (checked " << comparisons << " records).\n";
                }
                break;
            }

            case 4: {
                printHeading("ADD A NEW PRODUCT");
                int newId = 0;
                if (!readInt("  Product ID (1-999999): ", 1, 999999, newId)) {
                    running = false;
                    break;
                }
                string code;
                if (!readNonEmptyLine("  Stock code:       ", code)) {
                    running = false;
                    break;
                }
                string desc;
                if (!readNonEmptyLine("  Description:      ", desc)) {
                    running = false;
                    break;
                }
                int qty = 0;
                if (!readInt("  Quantity (0-100000): ", 0, 100000, qty)) {
                    running = false;
                    break;
                }
                double price = 0.0;
                if (!readPositiveDouble("  Unit price:       $", price)) {
                    running = false;
                    break;
                }

                int insertedAt = -1;
                Product newProduct(newId, code, desc, qty, price);
                if (store.addSorted(newProduct, insertedAt)) {
                    cout << "\n  Added and placed at sorted position "
                         << insertedAt << " of " << store.getCount() << ".\n";
                    newProduct.displayDetails();
                } else {
                    cout << "\n  [Rejected] Product ID " << newId
                         << " is already in the inventory.\n";
                    cout << "  Product IDs must be unique, because the ID is\n";
                    cout << "  the key the binary search relies on.\n";
                }
                break;
            }

            case 5: {
                printHeading("DELETE A PRODUCT");
                int targetId = 0;
                if (!readInt("  Product ID to delete: ", 1, 999999, targetId)) {
                    running = false;
                    break;
                }
                if (store.removeById(targetId)) {
                    cout << "\n  Deleted product ID " << targetId << ". "
                         << store.getCount() << " records remain.\n";
                } else {
                    cout << "\n  [Rejected] No product has ID " << targetId << ".\n";
                }
                break;
            }

            case 6: {
                printHeading("UPDATE A PRODUCT PRICE");
                int targetId = 0;
                if (!readInt("  Product ID to update: ", 1, 999999, targetId)) {
                    running = false;
                    break;
                }

                int comparisons = 0;
                Product *found = store.findById(targetId, comparisons, false);
                if (found == nullptr) {
                    cout << "\n  [Rejected] No product has ID " << targetId << ".\n";
                    break;
                }

                cout << fixed << setprecision(2);
                cout << "\n  Current price of " << found->getDescription()
                     << ": $" << found->getUnitPrice() << "\n";

                double newPrice = 0.0;
                if (!readPositiveDouble("  New unit price:   $", newPrice)) {
                    running = false;
                    break;
                }

                // The change goes through the setter, which validates it.
                if (found->setUnitPrice(newPrice)) {
                    cout << "\n  Updated through the pointer returned by the search:\n";
                    found->displayDetails();
                } else {
                    cout << "\n  [Rejected] The setter refused that price.\n";
                }
                break;
            }

            case 7: {
                printHeading("WRITE BOTH .TXT FILES");
                if (store.saveToFile(DATA_FILE, message)) {
                    cout << "  OK: " << message << "\n";
                } else {
                    cout << "  FAILED: " << message << "\n";
                }
                if (store.writeReport(REPORT_FILE, message)) {
                    cout << "  OK: " << message << "\n";
                } else {
                    cout << "  FAILED: " << message << "\n";
                }
                cout << "\n  " << DATA_FILE
                     << "   holds the raw records for the next run.\n";
                cout << "  " << REPORT_FILE
                     << "   holds a formatted report for a person to read.\n";
                break;
            }

            case 8: {
                showDataTypes();
                break;
            }

            case 9: {
                printHeading("POINTER DEMONSTRATION");
                store.pointerWalk();
                break;
            }

            case 0: {
                running = false;
                break;
            }

            default: {
                // readInt already limits the range, so this should never run.
                cout << "  [Invalid] Unknown option.\n";
                break;
            }
        }
    }

    // --- Shutdown ---------------------------------------------------------
    printHeading("EXIT");
    if (store.saveToFile(DATA_FILE, message)) {
        cout << "  " << message << "\n";
    }
    cout << "  Goodbye, " << currentUser->getUsername() << ".\n";

    // Every "new" needs a matching "delete". The Inventory destructor frees
    // the product array by itself when store goes out of scope.
    delete currentUser;
    currentUser = nullptr;

    cout << "\n";
    return 0;
}
