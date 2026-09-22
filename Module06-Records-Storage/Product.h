#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    std::string stockCode;
    std::string description;
    int quantity;
    double unitPrice;

public:
    Product(const std::string &code, const std::string &desc, int qty, double price);

    void displayProduct() const;
    double calculateStockValue() const;
    bool restock(int units);
    bool sell(int units);

    std::string getStockCode() const;
    std::string getDescription() const;
    int getQuantity() const;
    double getUnitPrice() const;

    bool setUnitPrice(double newPrice);
};

#endif
