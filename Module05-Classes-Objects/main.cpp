#include <iostream>
#include <iomanip>
#include "RecordTools.h"

using namespace std;

const int MAX_CAPACITY = 10;

int main() {
    ProductRecord inventory[MAX_CAPACITY];
    int recordCount = 0;

    showMessage();

    cout << "\n[Action] Inserting product records into the inventory system...\n";
    addRecord(inventory, recordCount, MAX_CAPACITY, "536365", "85123A", "WHITE HANGING HEART T-LIGHT HOLDER", 6, "12/1/2010 8:26", 2.55, "17850", "United Kingdom");
    addRecord(inventory, recordCount, MAX_CAPACITY, "536365", "71053", "WHITE METAL LANTERN", 6, "12/1/2010 8:26", 3.39, "17850", "United Kingdom");
    addRecord(inventory, recordCount, MAX_CAPACITY, "536365", "84406B", "CREAM CUPID HEARTS COAT HANGER", 8, "12/1/2010 8:26", 2.75, "17850", "United Kingdom");
    addRecord(inventory, recordCount, MAX_CAPACITY, "536365", "84029G", "KNITTED UNION FLAG HOT WATER BOTTLE", 6, "12/1/2010 8:26", 3.39, "17850", "United Kingdom");
    addRecord(inventory, recordCount, MAX_CAPACITY, "536365", "84029E", "RED WOOLLY HOTTIE WHITE HEART.", 6, "12/1/2010 8:26", 3.39, "17850", "United Kingdom");
    addRecord(inventory, recordCount, MAX_CAPACITY, "536365", "22752", "SET 7 BABUSHKA NESTING BOXES", 2, "12/1/2010 8:26", 7.65, "17850", "United Kingdom");
    addRecord(inventory, recordCount, MAX_CAPACITY, "536365", "21730", "GLASS STAR FROSTED T-LIGHT HOLDER", 6, "12/1/2010 8:26", 4.25, "17850", "United Kingdom");
    addRecord(inventory, recordCount, MAX_CAPACITY, "536366", "22633", "HAND WARMER UNION JACK", 6, "12/1/2010 8:28", 1.85, "17850", "United Kingdom");
    addRecord(inventory, recordCount, MAX_CAPACITY, "536366", "22632", "HAND WARMER RED POLKA DOT", 6, "12/1/2010 8:28", 1.85, "17850", "United Kingdom");
    addRecord(inventory, recordCount, MAX_CAPACITY, "536367", "84879", "ASSORTED COLOUR BIRD ORNAMENT", 32, "12/1/2010 8:34", 1.69, "13047", "United Kingdom");

    cout << "[Status] Successfully loaded " << recordCount << " product records.\n";

    cout << "\n[Display] Current Product Inventory Records:";
    displayRecords(inventory, recordCount);

    double totalValuation = calculateTotalValue(inventory, recordCount);
    double averagePrice = calculateAveragePrice(inventory, recordCount);

    cout << "\n====================================================================================\n";
    cout << "                             INVENTORY METRICS SUMMARY                              \n";
    cout << "====================================================================================\n";
    cout << fixed << setprecision(2) << right;
    cout << "  - Total Catalog Items:        " << recordCount << " products\n";
    cout << "  - Average Unit Price:         $" << setw(10) << averagePrice << "\n";
    cout << "  - Total Inventory Valuation:  $" << setw(10) << totalValuation << "\n";
    cout << "====================================================================================\n";

    return 0;
}
