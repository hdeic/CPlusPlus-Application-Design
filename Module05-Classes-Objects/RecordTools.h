#ifndef RECORDTOOLS_H
#define RECORDTOOLS_H

#include <string>

const std::string DATASET_PATH = "data/online-retail-10.csv";

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

long long reportFileSize(const std::string &path);

bool addRecord(ProductRecord records[], int &currentCount, int maxCapacity,
               const std::string &invoiceNo, const std::string &stockCode,
               const std::string &description, int quantity,
               const std::string &invoiceDate, double unitPrice,
               const std::string &customerId, const std::string &country);

int loadRecordsFromFile(const std::string &path, ProductRecord records[],
                        int &currentCount, int maxCapacity);

void displayRecords(const ProductRecord records[], int count);

double calculateTotalValue(const ProductRecord records[], int count);
double calculateAveragePrice(const ProductRecord records[], int count);

#endif
