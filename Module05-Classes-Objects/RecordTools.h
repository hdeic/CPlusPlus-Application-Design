#ifndef RECORDTOOLS_H
#define RECORDTOOLS_H

#include <string>

struct ProductRecord {
    std::string invoiceNo;
    std::string stockCode;
    std::string description;
    int quantity;
    std::string invoiceDate;
    double unitPrice;
    std::string customerId;
    std::string country;
};

void showMessage();

bool addRecord(ProductRecord records[], int &currentCount, int maxCapacity,
               const std::string &invoiceNo, const std::string &stockCode,
               const std::string &description, int quantity,
               const std::string &invoiceDate, double unitPrice,
               const std::string &customerId, const std::string &country);

void displayRecords(const ProductRecord records[], int count);

double calculateTotalValue(const ProductRecord records[], int count);
double calculateAveragePrice(const ProductRecord records[], int count);

#endif
