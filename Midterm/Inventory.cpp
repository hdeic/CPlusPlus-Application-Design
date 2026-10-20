#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include "Inventory.h"

using namespace std;

// ---------------------------------------------------------------------------
// Binary search on a sorted array, reached through a pointer.
//
// Each pass looks at the middle element and throws away the half that cannot
// contain the target. That is why it needs about log2(n) comparisons instead
// of n: 8 records take at most 3 comparisons, 1000 take at most 10.
// ---------------------------------------------------------------------------
Product *binarySearchById(Product *data, int size, int targetId,
                          int &comparisons, bool showSteps) {
    int left = 0;
    int right = size - 1;
    comparisons = 0;

    while (left <= right) {
        // Written this way instead of (left + right) / 2 so the addition can
        // never overflow on a very large array.
        int mid = left + (right - left) / 2;

        // (data + mid) is pointer arithmetic: step "mid" Product objects
        // forward from the start of the array. It means the same thing as
        // &data[mid].
        Product *middleProduct = data + mid;
        int middleId = middleProduct->getProductId();
        comparisons++;

        if (showSteps) {
            cout << "      step " << comparisons
                 << ": left=" << left << " right=" << right
                 << " mid=" << mid << " (ID " << middleId << ")";
        }

        if (middleId == targetId) {
            if (showSteps) cout << "  -> MATCH\n";
            return middleProduct;            // return a pointer to the match
        }

        if (middleId < targetId) {
            if (showSteps) {
                cout << "  -> " << middleId << " < " << targetId
                     << ", discard left half\n";
            }
            left = mid + 1;
        } else {
            if (showSteps) {
                cout << "  -> " << middleId << " > " << targetId
                     << ", discard right half\n";
            }
            right = mid - 1;
        }
    }

    return nullptr;                          // not found
}

// Constructor: allocate the dynamic array on the heap.
Inventory::Inventory(int initialCapacity)
    : items(nullptr), count(0), capacity(initialCapacity) {
    if (capacity < 1) capacity = 1;
    items = new Product[capacity];           // dynamic memory allocation
}

// Destructor: give the memory back. Every "new[]" needs a matching "delete[]".
Inventory::~Inventory() {
    delete[] items;
    items = nullptr;
}

// Grow the array: allocate a bigger block, copy, free the old block.
void Inventory::resize(int newCapacity) {
    Product *bigger = new Product[newCapacity];
    for (int i = 0; i < count; i++) {
        bigger[i] = items[i];
    }
    delete[] items;                          // release the old array
    items = bigger;                          // point at the new one
    capacity = newCapacity;
}

int Inventory::getCount() const {
    return count;
}

int Inventory::getCapacity() const {
    return capacity;
}

Product *Inventory::getItems() {
    return items;
}

// Insert a product at the position that keeps the array sorted by ID.
// Duplicate IDs are refused, because the ID is the unique search key.
bool Inventory::addSorted(const Product &product, int &insertedAt) {
    insertedAt = -1;

    int comparisons = 0;
    if (binarySearchById(items, count, product.getProductId(),
                         comparisons, false) != nullptr) {
        return false;                        // that ID already exists
    }

    if (count == capacity) {
        resize(capacity * 2);                // array is full, so make it bigger
    }

    // Find the slot where this ID belongs.
    int position = 0;
    while (position < count &&
           items[position].getProductId() < product.getProductId()) {
        position++;
    }

    // Shift everything from that slot one place to the right.
    for (int i = count; i > position; i--) {
        items[i] = items[i - 1];
    }

    items[position] = product;
    count++;
    insertedAt = position;
    return true;
}

// Delete a record, then close the gap it left behind.
bool Inventory::removeById(int productId) {
    int comparisons = 0;
    Product *found = binarySearchById(items, count, productId,
                                      comparisons, false);
    if (found == nullptr) return false;

    // Pointer subtraction gives the index of the element the pointer refers to.
    int index = static_cast<int>(found - items);
    for (int i = index; i < count - 1; i++) {
        items[i] = items[i + 1];
    }
    count--;
    return true;
}

Product *Inventory::findById(int productId, int &comparisons, bool showSteps) {
    return binarySearchById(items, count, productId, comparisons, showSteps);
}

// A second search, this one over strings. Descriptions are not sorted, so this
// has to be a linear search: it checks every record until it finds a match.
// Comparing the two comparison counts shows why sorting plus binary search is
// worth the effort.
const Product *Inventory::findByDescription(const string &text,
                                            int &comparisons) const {
    comparisons = 0;

    // Upper-case the search text so the match ignores capitalisation.
    string needle;
    for (size_t i = 0; i < text.size(); i++) {
        needle += static_cast<char>(toupper(static_cast<unsigned char>(text[i])));
    }

    for (int i = 0; i < count; i++) {
        comparisons++;
        string haystack = items[i].getDescription();
        for (size_t j = 0; j < haystack.size(); j++) {
            haystack[j] = static_cast<char>(toupper(static_cast<unsigned char>(haystack[j])));
        }
        // std::string::find returns npos when the text is not present.
        if (haystack.find(needle) != string::npos) {
            return &items[i];                // address of the matching element
        }
    }
    return nullptr;
}

void Inventory::displayAll() const {
    if (count == 0) {
        cout << "    (the inventory is empty)\n";
        return;
    }

    cout << "    --------------------------------------------------------------------------------\n";
    cout << "    " << left
         << setw(7)  << "ID"
         << setw(10) << "STOCK"
         << setw(38) << "DESCRIPTION"
         << right
         << setw(6)  << "QTY"
         << setw(11) << "UNIT ($)"
         << setw(12) << "VALUE ($)" << "\n";
    cout << "    --------------------------------------------------------------------------------\n";
    for (int i = 0; i < count; i++) {
        cout << "    ";
        items[i].displayRow();
    }
    cout << "    --------------------------------------------------------------------------------\n";
    cout << "    " << count << " records, sorted by product ID (array capacity "
         << capacity << ")\n";
}

double Inventory::totalStockValue() const {
    double total = 0.0;
    for (int i = 0; i < count; i++) {
        total += items[i].calculateStockValue();
    }
    return total;
}

int Inventory::totalUnits() const {
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += items[i].getQuantity();
    }
    return total;
}

// --- FILE INPUT: read records from a .txt file -----------------------------
bool Inventory::loadFromFile(const string &path, string &message) {
    ifstream inputFile(path);                // open the file for reading
    if (!inputFile.is_open()) {
        message = "could not open \"" + path + "\" for reading";
        return false;
    }

    int loaded = 0;
    int skipped = 0;
    string line;
    while (getline(inputFile, line)) {       // read one line at a time
        Product product;
        if (!Product::fromFileLine(line, product)) {
            if (!line.empty() && line[0] != '#') skipped++;
            continue;
        }
        int position = 0;
        if (addSorted(product, position)) {
            loaded++;
        } else {
            skipped++;                       // duplicate ID in the file
        }
    }
    inputFile.close();                       // always close the file

    message = "loaded " + to_string(loaded) + " records from \"" + path + "\"";
    if (skipped > 0) {
        message += ", skipped " + to_string(skipped) + " invalid/duplicate line(s)";
    }
    return true;
}

// --- FILE OUTPUT: write the records back to the same .txt format -----------
bool Inventory::saveToFile(const string &path, string &message) const {
    ofstream outputFile(path);               // open the file for writing
    if (!outputFile.is_open()) {
        message = "could not open \"" + path + "\" for writing";
        return false;
    }

    outputFile << "# Store inventory data file\n";
    outputFile << "# Format: productId|stockCode|description|quantity|unitPrice\n";
    for (int i = 0; i < count; i++) {
        outputFile << items[i].toFileLine() << "\n";
    }
    outputFile.close();

    message = "saved " + to_string(count) + " records to \"" + path + "\"";
    return true;
}

// --- FILE OUTPUT: write a formatted, human-readable report ----------------
bool Inventory::writeReport(const string &path, string &message) const {
    ofstream reportFile(path);
    if (!reportFile.is_open()) {
        message = "could not open \"" + path + "\" for writing";
        return false;
    }

    reportFile << "========================================================\n";
    reportFile << "            STORE INVENTORY REPORT\n";
    reportFile << "========================================================\n\n";
    reportFile << left << setw(7) << "ID" << setw(10) << "STOCK"
               << setw(38) << "DESCRIPTION"
               << right << setw(6) << "QTY" << setw(11) << "VALUE ($)" << "\n";
    reportFile << "--------------------------------------------------------\n";

    reportFile << fixed << setprecision(2);
    for (int i = 0; i < count; i++) {
        reportFile << left
                   << setw(7)  << items[i].getProductId()
                   << setw(10) << items[i].getStockCode()
                   << setw(38) << items[i].getDescription()
                   << right
                   << setw(6)  << items[i].getQuantity()
                   << setw(11) << items[i].calculateStockValue() << "\n";
    }

    reportFile << "--------------------------------------------------------\n";
    reportFile << "Total records:          " << count << "\n";
    reportFile << "Total units in stock:   " << totalUnits() << "\n";
    reportFile << "Total inventory value:  $" << totalStockValue() << "\n";
    reportFile.close();

    message = "wrote report to \"" + path + "\"";
    return true;
}

// --- Pointer demonstration -------------------------------------------------
// Walks the same array three different ways to show that array indexing and
// pointer arithmetic are two ways of saying the same thing.
void Inventory::pointerWalk() const {
    if (count == 0) {
        cout << "    (the inventory is empty, so there is nothing to walk)\n";
        return;
    }

    cout << "    The array lives on the heap. 'items' holds its first address.\n";
    cout << "    sizeof(Product) = " << sizeof(Product) << " bytes, so each step\n";
    cout << "    of the pointer moves that many bytes forward.\n\n";

    cout << "    " << left << setw(8) << "INDEX" << setw(18) << "ADDRESS"
         << setw(10) << "OFFSET" << setw(8) << "ID" << "DESCRIPTION\n";
    cout << "    ------------------------------------------------------------------\n";

    // ptr starts at the first element and moves forward one Product per step.
    const Product *ptr = items;
    for (int i = 0; i < count; i++) {
        cout << "    " << left << setw(8) << i
             << setw(18) << static_cast<const void *>(ptr)
             << setw(10) << (i * static_cast<int>(sizeof(Product)))
             << setw(8) << ptr->getProductId()      // -> reads through a pointer
             << ptr->getDescription() << "\n";
        ptr++;                                      // pointer arithmetic
    }

    cout << "\n    Three ways to read the SAME first description:\n";
    cout << "      items[0].getDescription()    -> " << items[0].getDescription() << "\n";
    cout << "      (*(items + 0)).getDescription() -> " << (*(items + 0)).getDescription() << "\n";
    cout << "      (items + 0)->getDescription()   -> " << (items + 0)->getDescription() << "\n";

    cout << "\n    Reading one single value through a pointer:\n";
    const Product *last = items + (count - 1);
    cout << "      pointer to last record: " << static_cast<const void *>(last) << "\n";
    cout << "      last->getQuantity()     = " << last->getQuantity() << " units\n";
    cout << "      pointer minus base      = index " << (last - items) << "\n";
}
