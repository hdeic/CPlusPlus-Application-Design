#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "Product.h"

int binarySearch(const Product data[], int size, int targetId, int &comparisons, bool showSteps);

class Inventory {
private:
    std::vector<Product> records;

public:
    int addSorted(const Product &product);
    bool removeById(int productId);
    const Product *findById(int productId, int &comparisons, bool showSteps) const;
    void displayAll() const;
    int size() const;
    double totalStockValue() const;
};

#endif
