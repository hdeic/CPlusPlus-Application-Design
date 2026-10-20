#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

// ===========================================================================
// Class 1 of 3: Product
// ---------------------------------------------------------------------------
// Represents a single item in the store's inventory. All data members are
// private (encapsulation), so the only way to read or change them is through
// the public member functions below. The setters validate their input, which
// means a Product object can never hold a negative quantity or price.
// ===========================================================================
class Product {
private:
    int productId;             // unique key, also the binary-search key
    std::string stockCode;     // short warehouse code, e.g. "71053"
    std::string description;   // product name (a std::string, may contain spaces)
    int quantity;              // units in stock
    double unitPrice;          // price per unit in dollars

public:
    // Default constructor. Needed because Inventory allocates an array of
    // Product objects with "new Product[capacity]", which default-constructs
    // every slot before any real data is copied in.
    Product();

    // Main constructor. Rejects a negative quantity or price by storing 0.
    Product(int id, const std::string &code, const std::string &desc,
            int qty, double price);

    // --- Getters (const: they promise not to modify the object) ---
    int getProductId() const;
    std::string getStockCode() const;
    std::string getDescription() const;
    int getQuantity() const;
    double getUnitPrice() const;

    // --- Setters (return false when the new value is invalid) ---
    bool setQuantity(int newQuantity);
    bool setUnitPrice(double newPrice);

    // --- Other member functions ---
    double calculateStockValue() const;   // quantity * unitPrice
    void displayRow() const;              // one aligned line for a table
    void displayDetails() const;          // multi-line detail view

    // --- File I/O helpers ---
    // Converts this object into one pipe-delimited line for inventory.txt.
    std::string toFileLine() const;

    // Parses one line of inventory.txt back into a Product.
    // Returns false if the line is blank, a comment, or malformed.
    static bool fromFileLine(const std::string &line, Product &result);
};

#endif
