#include <iostream>
#include <iomanip>
#include "RecordTools.h"

using namespace std;

// Original starter function implementation
void showMessage() {
    cout << "========================================================================================\n";
    cout << "                     Record Management System Ready! (Module 5)                         \n";
    cout << "========================================================================================\n";
}

// Function 1: Add a record to the inventory array
bool addRecord(ProductRecord records[], int &currentCount, int maxCapacity,
               int id, const string &name, const string &category, double price, int quantity) {
    if (currentCount >= maxCapacity) {
        cout << "[Error] Cannot add record '" << name << "': Maximum capacity reached!\n";
        return false;
    }

    records[currentCount].id = id;
    records[currentCount].name = name;
    records[currentCount].category = category;
    records[currentCount].price = price;
    records[currentCount].quantity = quantity;
    currentCount++;
    return true;
}

// Function 2: Display all records in a formatted table
void displayRecords(const ProductRecord records[], int count) {
    cout << "\n----------------------------------------------------------------------------------------\n";
    cout << left 
         << setw(6)  << "ID"
         << setw(35) << "Product Name"
         << setw(16) << "Category"
         << right
         << setw(12) << "Price ($)"
         << setw(8)  << "Qty"
         << setw(15) << "Subtotal ($)" << "\n";
    cout << "----------------------------------------------------------------------------------------\n";

    for (int i = 0; i < count; i++) {
        double subtotal = records[i].price * records[i].quantity;
        cout << left
             << setw(6)  << records[i].id
             << setw(35) << records[i].name
             << setw(16) << records[i].category
             << right << fixed << setprecision(2)
             << setw(12) << records[i].price
             << setw(8)  << records[i].quantity
             << setw(15) << subtotal << "\n";
    }
    cout << "----------------------------------------------------------------------------------------\n";
}

// Function 3a: Calculate total valuation across all records
double calculateTotalValue(const ProductRecord records[], int count) {
    double total = 0.0;
    for (int i = 0; i < count; i++) {
        total += (records[i].price * records[i].quantity);
    }
    return total;
}

// Function 3b: Calculate average unit price
double calculateAveragePrice(const ProductRecord records[], int count) {
    if (count == 0) return 0.0;
    double sum = 0.0;
    for (int i = 0; i < count; i++) {
        sum += records[i].price;
    }
    return sum / count;
}
