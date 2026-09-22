#include <iostream>
#include <iomanip>
#include "Product.h"

using namespace std;

Product::Product(int id, const string &code, const string &desc, int qty, double price)
    : productId(id), stockCode(code), description(desc), quantity(0), unitPrice(0.0) {
    if (qty > 0) quantity = qty;
    if (price > 0.0) unitPrice = price;
}

void Product::displayRow() const {
    cout << left
         << setw(6)  << productId
         << setw(9)  << stockCode
         << setw(38) << description
         << right << fixed << setprecision(2)
         << setw(5)  << quantity
         << setw(10) << unitPrice
         << setw(11) << calculateStockValue() << "\n";
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

double Product::calculateStockValue() const {
    return quantity * unitPrice;
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
