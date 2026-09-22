#include <iostream>
#include <iomanip>
#include "Product.h"

using namespace std;

Product::Product(const string &code, const string &desc, int qty, double price)
    : stockCode(code), description(desc), quantity(0), unitPrice(0.0) {
    if (qty > 0) quantity = qty;
    if (price > 0.0) unitPrice = price;
}

void Product::displayProduct() const {
    cout << fixed << setprecision(2);
    cout << "  Stock Code:   " << stockCode << "\n";
    cout << "  Description:  " << description << "\n";
    cout << "  Quantity:     " << quantity << "\n";
    cout << "  Unit Price:   $" << unitPrice << "\n";
    cout << "  Stock Value:  $" << calculateStockValue() << "\n";
}

double Product::calculateStockValue() const {
    return quantity * unitPrice;
}

bool Product::restock(int units) {
    if (units <= 0) return false;
    quantity += units;
    return true;
}

bool Product::sell(int units) {
    if (units <= 0 || units > quantity) return false;
    quantity -= units;
    return true;
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

bool Product::setUnitPrice(double newPrice) {
    if (newPrice <= 0.0) return false;
    unitPrice = newPrice;
    return true;
}
