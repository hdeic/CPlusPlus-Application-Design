#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "RecordTools.h"

using namespace std;

static vector<string> splitCsvLine(const string &line) {
    vector<string> fields;
    string current;
    bool insideQuotes = false;

    for (size_t i = 0; i < line.size(); i++) {
        char c = line[i];
        if (c == '"') {
            if (insideQuotes && i + 1 < line.size() && line[i + 1] == '"') {
                current += '"';
                i++;
            } else {
                insideQuotes = !insideQuotes;
            }
        } else if (c == ',' && !insideQuotes) {
            fields.push_back(current);
            current.clear();
        } else if (c != '\r') {
            current += c;
        }
    }
    fields.push_back(current);
    return fields;
}

static bool isNumber(const string &text) {
    if (text.empty()) return false;
    bool digitSeen = false;
    for (size_t i = 0; i < text.size(); i++) {
        char c = text[i];
        if (c == '+' || c == '-') {
            if (i != 0) return false;
        } else if (c == '.') {
            continue;
        } else if (c < '0' || c > '9') {
            return false;
        } else {
            digitSeen = true;
        }
    }
    return digitSeen;
}

void showMessage() {
    cout << "==========================================================================================================\n";
    cout << "                        Record Management System Ready! (Module 5)                                         \n";
    cout << "==========================================================================================================\n";
}

long long reportFileSize(const string &path) {
    fstream dataFile(path, fstream::in);
    if (!dataFile.is_open()) {
        return -1;
    }

    dataFile.seekg(0, fstream::end);
    long long byteCount = static_cast<long long>(dataFile.tellg());
    dataFile.seekg(0, fstream::beg);
    dataFile.close();

    return byteCount;
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

int loadRecordsFromFile(const string &path, ProductRecord records[],
                        int &currentCount, int maxCapacity) {
    fstream dataFile(path, fstream::in);
    if (!dataFile.is_open()) {
        return -1;
    }

    string line;
    getline(dataFile, line);

    int added = 0;
    while (currentCount < maxCapacity && getline(dataFile, line)) {
        if (line.empty()) continue;

        vector<string> fields = splitCsvLine(line);
        if (fields.size() < 8) continue;
        if (!isNumber(fields[3]) || !isNumber(fields[5])) continue;

        bool inserted = addRecord(records, currentCount, maxCapacity,
                                  fields[0], fields[1], fields[2],
                                  stoi(fields[3]), fields[4], stod(fields[5]),
                                  fields[6], fields[7]);
        if (inserted) added++;
    }

    dataFile.close();
    return added;
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
