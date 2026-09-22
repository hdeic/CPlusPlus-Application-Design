#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    int productId;
    std::string stockCode;
    std::string description;
    int quantity;
    double unitPrice;

public:
    Product(int id, const std::string &code, const std::string &desc, int qty, double price);

    void displayRow() const;
    void displayDetails() const;
    double calculateStockValue() const;

    int getProductId() const;
    std::string getStockCode() const;
    std::string getDescription() const;
    int getQuantity() const;
    double getUnitPrice() const;
};

#endif
