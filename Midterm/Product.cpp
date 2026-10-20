#include <iostream>
#include <iomanip>
#include <sstream>
#include "Product.h"

using namespace std;

// Default constructor: an empty placeholder product.
Product::Product()
    : productId(0), stockCode(""), description(""), quantity(0), unitPrice(0.0) {
}

// Main constructor. The member initializer list runs before the body, so the
// body only has to apply the validation rules.
Product::Product(int id, const string &code, const string &desc,
                 int qty, double price)
    : productId(id), stockCode(code), description(desc),
      quantity(0), unitPrice(0.0) {
    if (qty > 0) quantity = qty;
    if (price > 0.0) unitPrice = price;
}

int Product::getProductId() const {
    return productId;
}

string Product::getStockCode() const {
    return stockCode;
}

string Product::getDescription() const {
    return description;
}

int Product::getQuantity() const {
    return quantity;
}

double Product::getUnitPrice() const {
    return unitPrice;
}

// A setter can refuse bad data. A public data member never could.
bool Product::setQuantity(int newQuantity) {
    if (newQuantity < 0) return false;
    quantity = newQuantity;
    return true;
}

bool Product::setUnitPrice(double newPrice) {
    if (newPrice <= 0.0) return false;
    unitPrice = newPrice;
    return true;
}

double Product::calculateStockValue() const {
    return quantity * unitPrice;
}

void Product::displayRow() const {
    cout << left
         << setw(7)  << productId
         << setw(10) << stockCode
         << setw(38) << description
         << right << fixed << setprecision(2)
         << setw(6)  << quantity
         << setw(11) << unitPrice
         << setw(12) << calculateStockValue() << "\n";
}

void Product::displayDetails() const {
    cout << fixed << setprecision(2);
    cout << "    Product ID:   " << productId << "\n";
    cout << "    Stock Code:   " << stockCode << "\n";
    cout << "    Description:  " << description << "\n";
    cout << "    Quantity:     " << quantity << "\n";
    cout << "    Unit Price:   $" << unitPrice << "\n";
    cout << "    Stock Value:  $" << calculateStockValue() << "\n";
}

// Build one text line: 105|71053|WHITE METAL LANTERN|6|3.39
// A pipe is used instead of a comma because descriptions contain spaces and
// could contain commas.
string Product::toFileLine() const {
    ostringstream line;
    line << productId << "|" << stockCode << "|" << description << "|"
         << quantity << "|" << fixed << setprecision(2) << unitPrice;
    return line.str();
}

// Read one text line back into a Product object.
bool Product::fromFileLine(const string &line, Product &result) {
    if (line.empty() || line[0] == '#') return false;   // skip blanks/comments

    string field[5];
    int fieldCount = 0;
    string current;

    // Split the line on '|' into at most 5 fields.
    for (size_t i = 0; i < line.size(); i++) {
        char c = line[i];
        if (c == '|') {
            if (fieldCount < 5) field[fieldCount] = current;
            fieldCount++;
            current.clear();
        } else if (c != '\r') {       // ignore Windows carriage returns
            current += c;
        }
    }
    if (fieldCount < 5) field[fieldCount] = current;
    fieldCount++;

    if (fieldCount != 5) return false;               // wrong number of fields
    if (field[2].empty()) return false;              // description required

    // Convert the numeric fields, rejecting anything that is not a number.
    int id = 0;
    int qty = 0;
    double price = 0.0;
    istringstream idStream(field[0]);
    istringstream qtyStream(field[3]);
    istringstream priceStream(field[4]);
    if (!(idStream >> id)) return false;
    if (!(qtyStream >> qty)) return false;
    if (!(priceStream >> price)) return false;
    if (id <= 0 || qty < 0 || price < 0.0) return false;

    result = Product(id, field[1], field[2], qty, price);
    return true;
}
