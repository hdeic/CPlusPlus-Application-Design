#include <iostream>
#include <iomanip>
#include "RecordTools.h"

using namespace std;

void showMessage() {
    cout << "==========================================================================================================\n";
    cout << "                        Record Management System Ready! (Module 5)                                         \n";
    cout << "==========================================================================================================\n";
}

bool addRecord(ProductRecord records[], int &currentCount, int maxCapacity,
               const string &invoiceNo, const string &stockCode,
               const string &description, int quantity,
               const string &invoiceDate, double unitPrice,
               const string &customerId, const string &country) {
    if (currentCount >= maxCapacity) {
        cout << "[Error] Cannot add record '" << description << "': maximum capacity reached!\n";
        return false;
    }

    records[currentCount].invoiceNo = invoiceNo;
    records[currentCount].stockCode = stockCode;
    records[currentCount].description = description;
    records[currentCount].quantity = quantity;
    records[currentCount].invoiceDate = invoiceDate;
    records[currentCount].unitPrice = unitPrice;
    records[currentCount].customerId = customerId;
    records[currentCount].country = country;
    currentCount++;
    return true;
}

void displayRecords(const ProductRecord records[], int count) {
    cout << "\n----------------------------------------------------------------------------------------------------------\n";
    cout << left
         << setw(10) << "INVOICE"
         << setw(10) << "STOCK"
         << setw(38) << "DESCRIPTION"
         << right
         << setw(6)  << "QTY"
         << setw(11) << "UNIT ($)"
         << setw(14) << "LINE ($)"
         << "  " << left << setw(16) << "COUNTRY" << "\n";
    cout << "----------------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < count; i++) {
        double lineTotal = records[i].unitPrice * records[i].quantity;
        cout << left
             << setw(10) << records[i].invoiceNo
             << setw(10) << records[i].stockCode
             << setw(38) << records[i].description
             << right << fixed << setprecision(2)
             << setw(6)  << records[i].quantity
             << setw(11) << records[i].unitPrice
             << setw(14) << lineTotal
             << "  " << left << setw(16) << records[i].country << "\n";
    }
    cout << "----------------------------------------------------------------------------------------------------------\n";
}

double calculateTotalValue(const ProductRecord records[], int count) {
    double total = 0.0;
    for (int i = 0; i < count; i++) {
        total += (records[i].unitPrice * records[i].quantity);
    }
    return total;
}

double calculateAveragePrice(const ProductRecord records[], int count) {
    if (count == 0) return 0.0;
    double sum = 0.0;
    for (int i = 0; i < count; i++) {
        sum += records[i].unitPrice;
    }
    return sum / count;
}
