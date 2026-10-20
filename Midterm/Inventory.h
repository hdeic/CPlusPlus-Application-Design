#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include "Product.h"

// ---------------------------------------------------------------------------
// Binary search, written as a free function so the array and the pointer work
// are both visible. "data" is a pointer to the first element of an array of
// Product objects that is already sorted by product ID.
//
// Returns a pointer to the matching Product, or nullptr when there is no
// match. "comparisons" reports how many elements were examined, which is what
// makes the speed of binary search visible to the user.
// ---------------------------------------------------------------------------
Product *binarySearchById(Product *data, int size, int targetId,
                          int &comparisons, bool showSteps);

// ===========================================================================
// Class 2 of 3: Inventory
// ---------------------------------------------------------------------------
// Owns a DYNAMIC ARRAY of Product objects on the heap. The array is reached
// through the pointer "items", grows itself when it runs out of room, and is
// released in the destructor so no memory leaks.
//
// Records are always kept sorted by product ID. That ordering is what makes
// the binary search above valid.
// ===========================================================================
class Inventory {
private:
    Product *items;     // pointer to a dynamically allocated array of Product
    int count;          // how many slots are actually used
    int capacity;       // how many slots were allocated

    // Allocates a bigger array, copies the old elements across, and frees the
    // old block. Called automatically by addSorted when the array is full.
    void resize(int newCapacity);

public:
    Inventory(int initialCapacity = 4);   // constructor: allocates the array
    ~Inventory();                         // destructor: frees the array

    // This class owns raw memory, so copying it with the compiler's default
    // (which would copy the pointer, not the array) would lead to a double
    // delete. Copying is therefore switched off on purpose.
    Inventory(const Inventory &other) = delete;
    Inventory &operator=(const Inventory &other) = delete;

    int getCount() const;
    int getCapacity() const;
    Product *getItems();                  // raw pointer to the array

    // --- Record management (keeps the array sorted by ID) ---
    bool addSorted(const Product &product, int &insertedAt);
    bool removeById(int productId);

    // --- Searching ---
    Product *findById(int productId, int &comparisons, bool showSteps);
    const Product *findByDescription(const std::string &text,
                                     int &comparisons) const;

    // --- Reporting ---
    void displayAll() const;
    double totalStockValue() const;
    int totalUnits() const;

    // --- File I/O (.txt files) ---
    bool loadFromFile(const std::string &path, std::string &message);
    bool saveToFile(const std::string &path, std::string &message) const;
    bool writeReport(const std::string &path, std::string &message) const;

    // --- Teaching aid: walks the array using pointer arithmetic ---
    void pointerWalk() const;
};

#endif
