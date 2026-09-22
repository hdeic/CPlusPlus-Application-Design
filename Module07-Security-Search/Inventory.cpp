#include <iostream>
#include <iomanip>
#include "Inventory.h"

using namespace std;

int binarySearch(const Product data[], int size, int targetId, int &comparisons, bool showSteps) {
    int left = 0;
    int right = size - 1;
    comparisons = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int midId = data[mid].getProductId();
        comparisons++;

        if (showSteps) {
            cout << "      step " << comparisons << ": left=" << left << " right=" << right
                 << " mid=" << mid << " (ID " << midId << ")";
        }

        if (midId == targetId) {
            if (showSteps) cout << " -> match\n";
            return mid;
        }
        if (midId < targetId) {
            if (showSteps) cout << " -> " << midId << " < " << targetId << ", search right half\n";
            left = mid + 1;
        } else {
            if (showSteps) cout << " -> " << midId << " > " << targetId << ", search left half\n";
            right = mid - 1;
        }
    }
    return -1;
}

int Inventory::addSorted(const Product &product) {
    int comparisons = 0;
    if (binarySearch(records.data(), size(), product.getProductId(), comparisons, false) != -1) {
        return -1;
    }

    int position = 0;
    while (position < size() && records[position].getProductId() < product.getProductId()) {
        position++;
    }
    records.insert(records.begin() + position, product);
    return position;
}

bool Inventory::removeById(int productId) {
    int comparisons = 0;
    int index = binarySearch(records.data(), size(), productId, comparisons, false);
    if (index == -1) return false;
    records.erase(records.begin() + index);
    return true;
}

const Product *Inventory::findById(int productId, int &comparisons, bool showSteps) const {
    int index = binarySearch(records.data(), size(), productId, comparisons, showSteps);
    if (index == -1) return nullptr;
    return &records[index];
}

void Inventory::displayAll() const {
    cout << "    -------------------------------------------------------------------------------\n";
    cout << "    " << left
         << setw(6)  << "ID"
         << setw(9)  << "STOCK"
         << setw(38) << "DESCRIPTION"
         << right
         << setw(5)  << "QTY"
         << setw(10) << "UNIT ($)"
         << setw(11) << "VALUE ($)" << "\n";
    cout << "    -------------------------------------------------------------------------------\n";
    for (const Product &product : records) {
        cout << "    ";
        product.displayRow();
    }
    cout << "    -------------------------------------------------------------------------------\n";
    cout << "    " << size() << " records, sorted by product ID\n";
}

int Inventory::size() const {
    return static_cast<int>(records.size());
}

double Inventory::totalStockValue() const {
    double total = 0.0;
    for (const Product &product : records) {
        total += product.calculateStockValue();
    }
    return total;
}
