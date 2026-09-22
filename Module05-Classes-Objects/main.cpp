#include <iostream>
#include <iomanip>
#include "RecordTools.h"

using namespace std;

const int MAX_CAPACITY = 10;

int main() {
    ProductRecord inventory[MAX_CAPACITY];
    int recordCount = 0;

    showMessage();

    long long fileBytes = reportFileSize(DATASET_PATH);
    if (fileBytes < 0) {
        cerr << "ERROR: could not open \"" << DATASET_PATH << "\".\n"
             << "Run this program from the Module05-Classes-Objects folder so the\n"
             << "relative path to the record data file resolves correctly.\n";
        return 1;
    }

    cout << "\n[Source] Record data file: " << DATASET_PATH << "\n";
    cout << "[Source] Size measured with fstream seekg/tellg: " << fileBytes << " bytes\n";

    cout << "\n[Action] Importing product records with the fstream class...\n";
    int loaded = loadRecordsFromFile(DATASET_PATH, inventory, recordCount, MAX_CAPACITY);
    if (loaded <= 0) {
        cerr << "ERROR: no usable records were read from \"" << DATASET_PATH << "\".\n";
        return 1;
    }

    cout << "[Status] Successfully imported " << recordCount << " product records.\n";

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
