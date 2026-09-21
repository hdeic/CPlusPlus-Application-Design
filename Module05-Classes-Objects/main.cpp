/*
 * Course: CIS-25 - Programming Using C++
 * Student: H Cheng
 * Module: Module 5 - Records, Headers & Functions
 *
 * Description:
 * Demonstrates modular C++ application design by separating declarations into a custom
 * header file (RecordTools.h) and definitions into an implementation file (RecordTools.cpp).
 * Includes functions to add records, display records, and calculate total and average values.
 */

#include <iostream>
#include <iomanip>
#include "RecordTools.h"

using namespace std;

// Maximum storage capacity for this record array demonstration
const int MAX_CAPACITY = 10;

int main() {
    ProductRecord inventory[MAX_CAPACITY];
    int recordCount = 0;

    // 1. Starter code function call from RecordTools.h
    showMessage();

    // 2. Add records (Assignment Requirement: function to add a record)
    cout << "\n[Action] Inserting product records into the inventory system...\n";
    addRecord(inventory, recordCount, MAX_CAPACITY, 101, "Wireless Mechanical Keyboard", "Peripherals", 89.99, 15);
    addRecord(inventory, recordCount, MAX_CAPACITY, 102, "Ergonomic Optical Mouse", "Peripherals", 49.50, 25);
    addRecord(inventory, recordCount, MAX_CAPACITY, 103, "UltraWide 34-inch Monitor", "Displays", 459.00, 8);
    addRecord(inventory, recordCount, MAX_CAPACITY, 104, "USB-C Multiport Docking Station", "Accessories", 65.00, 18);
    addRecord(inventory, recordCount, MAX_CAPACITY, 105, "Noise-Cancelling Headphones", "Audio", 179.99, 12);
    addRecord(inventory, recordCount, MAX_CAPACITY, 106, "Adjustable Aluminum Laptop Stand", "Accessories", 39.99, 30);

    cout << "[Status] Successfully loaded " << recordCount << " product records.\n";

    // 3. Display records (Assignment Requirement: function to display records)
    cout << "\n[Display] Current Product Inventory Records:";
    displayRecords(inventory, recordCount);

    // 4. Calculate simple results (Assignment Requirement: function to calculate a simple result)
    double totalValuation = calculateTotalValue(inventory, recordCount);
    double averagePrice = calculateAveragePrice(inventory, recordCount);

    cout << "\n====================================================================================\n";
    cout << "                             INVENTORY METRICS SUMMARY                              \n";
    cout << "====================================================================================\n";
    cout << fixed << setprecision(2);
    cout << "  - Total Catalog Items:        " << recordCount << " products\n";
    cout << "  - Average Unit Price:         $" << setw(10) << averagePrice << "\n";
    cout << "  - Total Inventory Valuation:  $" << setw(10) << totalValuation << "\n";
    cout << "====================================================================================\n";

    return 0;
}
