#ifndef RECORDTOOLS_H
#define RECORDTOOLS_H

#include <string>

// Record structure representing an eCommerce inventory item
struct ProductRecord {
    int id;
    std::string name;
    std::string category;
    double price;
    int quantity;
};

// Starter code function
void showMessage();

// Assignment Functions:
// 1. Function to add a record
bool addRecord(ProductRecord records[], int &currentCount, int maxCapacity,
               int id, const std::string &name, const std::string &category, double price, int quantity);

// 2. Function to display records
void displayRecords(const ProductRecord records[], int count);

// 3. Functions to calculate simple results
double calculateTotalValue(const ProductRecord records[], int count);
double calculateAveragePrice(const ProductRecord records[], int count);

#endif // RECORDTOOLS_H
